//
//  ConsHeur_v2.cpp
//  GuillotineCuts
//
//  Created by Marta Cabo Nodar on 10/03/15.
//  Copyright (c) 2015 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"
void
OpenBin (BIN &bin, PIEZA &item);
IRR_BIN
ConvertToIRRBIN (BIN &bin);
PIEZA
create_convexhull_in_section (IRR_BIN &sect);
PIEZA
create_rectencl_in_section (IRR_BIN &sect);
vector<PIEZA*>
CreateList (vector<PIEZA> &item, IRR_BIN &sect);
double
SelectBestMatch (IRR_BIN &bin, vector<PIEZA*> list, PIEZA convex_hull,
		 int &best_e1, int &best_e2, double &best_d, int &best_p,
		 int &best_m);
double
GuillotineCutWaste (PIEZA ch, IRR_BIN current_sect, EDGES &best_gc);
bool
FillBin (vector<PIEZA> &item, IRR_BIN &c_sect, EDGES &best_gc, int i);
void
Attach (PIEZA item1, PIEZA &item2, int v1, int v2);
bool
Feasible_Slide_InSect (IRR_BIN bin, PIEZA item1, PIEZA &item2, int v1, int v2,
		       double dis);
bool
Place_in_NewSection (IRR_BIN &current_sect, vector<PIEZA*> &candidates,
		     EDGES &best_gc, int id);
vector<PUNTO>
Redefine_IrrBin_withPieces (vector<PUNTO> &rbin, EDGES gc);

//=========================================================
//Constructive Heuristic that places pieces based on the best of two criteria:
//Max Convex Hull Utilization, or Min Guillotine Cut Waste.
//If pieces from a candidate list do not fit in any open bin, it opens a new bin.
//See ConsHeur_v2.tex for more detail.
//=========================================================
void
LastBinRefinementGE (vector<PIEZA> &pzas, BIN &sol);
void
dibujar_bins (vector<BIN> &bins, char *instance, char *name, double t, double L,
	      double W, int escalado);

double
ConsHeur (double stock_length, double stock_width, vector<PIEZA> item, double p_of, int level, int id)
{

  BIN current_bin;
  IRR_BIN current_sect;
  PIEZA ch;
  vector<PIEZA*> candidates;
  vector<BIN> bin_sol;
  current_bin.initialize_bin (stock_length, stock_width, 1);
  int no_bins = 0;
  long problem_size = item.size ();
  int last = problem_size - 1;
  int pieces_placed = 0;
  double best_of = 0;
  while (pieces_placed < problem_size) //While not all the pieces have been placed
    {
      double ch_util = -1; //best utilization of the convex hull when the next piece is attached.
      int best_i = -1; //Best edge of the ch
      int best_j = -1; //Best edge of the piece
      int best_p = -1; //Best piece from list
      int best_m = -1; // =0 piece not mirrored
      double best_d = -1; // best slide distance.
      int bin_count = 0;
      double gc_waste = -1; //best utilization of the bin, when the guillotine cut is performed.
      EDGES best_gc;
      int no_sects = -1; //number of sections of current bin;
      bool placed = false; // placed = true if any piece from the list is placed in the current bin.
      while (bin_count < bin_sol.size ())
	{
	  //Move to first open bin
	  while (bin_count < bin_sol.size () && !bin_sol[bin_count].getOpen ())
	    bin_count++;
	  if (bin_count >= bin_sol.size ())
	    break; //NO more bins to try, open new bin
	  current_bin = bin_sol[bin_count];
	  no_sects = current_bin.getNumSect ();
	  current_sect = current_bin.get_ib (no_sects - 1); //Always start from the last section created.
	  //We need to eplore one section at a time. Not starting from the last section created.
	  ch = create_convexhull_in_section (current_sect);
	  //ch = create_rectencl_in_section(current_sect); //Rectangle enclosure for the rectangle instances.

	  //Create a list of next pieces to be placed.
	  candidates = CreateList (item, current_sect);
	  if (candidates.empty ())//No unplaced piece fits in the last section created.
	    {
	      int i = 0;
	      //Check if it is possible to have candidates to any of the other sections.
	      while (candidates.empty () && i < current_bin.getNumSect ())
		{
		  current_sect = current_bin.get_ib (i);
		  candidates = CreateList (item, current_sect);
		  i++;
		}
	      if (candidates.empty ())
		{
		  current_bin.setOpen (false);//No more candidates for this bin, bin closed.
		  bin_sol[bin_count].setOpen (false);
//					printf("BIN %d Closed (no more candidates)\n", current_bin.getID());
		  bin_count++;			//move to next bin
		  continue;
		}
	      else//We have changed the section so we need to recalculate the convex hull.
		{
		  ch = create_convexhull_in_section (current_sect);
		  //ch = create_rectencl_in_section(current_sect); //Rectangle enclosure for the rectangle instances.

		}
	    }
	  //Check CH util
	  //=================================
	  ch_util = SelectBestMatch (current_sect, candidates, ch, best_i,
				     best_j, best_d, best_p, best_m);
	  gc_waste = GuillotineCutWaste (ch, current_sect, best_gc);//Calculates the proportion wasted
	  double gc_used = 1 - gc_waste;
	  double bin_used = current_bin.getPropUtil ();
	  //First criteria:
	  //If the bin is already more than 80% used: Fill the bin and close it
	  if (bin_used > 0.80)//Place pieces in remaining space according to best guillotine cut.
	    {
	      while (current_bin.getOpen ())
		{
		  int i = current_bin.getNumSect () - 1;
		  while (i >= 0)
		    {
		      current_sect = current_bin.get_ib (i);
		      ch = create_convexhull_in_section (current_sect);
		      //ch = create_rectencl_in_section(current_sect); //Rectangle enclosure for the rectangle instances.
		      //==============================================
		      //Select an appropriate section that may allocate more pieces.
		      if (equal_double (ch.getArea (), current_sect.getArea (),
		      TOL) || current_sect.get_waste () < item[last].getArea ())//Current section filled up, useless to try it.
			{
			  i--;			//Move to previous section
			  placed = false;
			  continue;
			}
		      GuillotineCutWaste (ch, current_sect, best_gc);
		      PUNTO gc_empty;
		      gc_empty.coordx = -1;
		      gc_empty.coordy = -1;
		      if (equal_pto (best_gc.ini, gc_empty)
			  && equal_pto (best_gc.fin, gc_empty))	//No more gc possible in current section, move to next
			{
			  i--;			//Move to previous section
			  placed = false;
			  continue;
			}
		      //===========================================
		      placed = FillBin (item, current_sect, best_gc,
					current_bin.getNumSect ());
		      if (!placed)
			{
			  i--;			//Move to previous section
			  continue;
			}
		      else
			break; //Piece placed,
		    }
		  if (!placed)
		    {
		      current_bin.setOpen (false); //No more fits. Close bin.
		      bin_sol[bin_count].setOpen (false);
//						printf("BIN %d Closed (+80%)\n", current_bin.getID());
		    }
		  else //place piece
		    {
		      //Redefine previous section since its limits have changed.
		      vector<PUNTO> *ptos_sec;
		      IRR_BIN sect = current_bin.get_ib (i);
		      ptos_sec = sect.get_ptos ();
		      *ptos_sec = Redefine_IrrBin_withPieces (*ptos_sec,
							      best_gc);
		      current_sect.set_ID (current_bin.getNumSect ());
		      current_bin.update_ptos_sect (sect);
		      //Add the new section to the bin, and update this section
		      current_sect.add_GC (best_gc); //Add the guillotine cut to the section
		      current_bin.add_IB (current_sect);
		      current_bin.add_piece_SectToBin (current_sect);
		      current_bin.add_GC (best_gc); //Add the guillotine cut to the bin.
		      bin_sol[bin_count] = current_bin; //Add the new bin to the solution
		      pieces_placed++;
//						vector<PIEZA*> pi = *current_bin.getPI();
//						PIEZA *last = pi.back();
//						printf("Piece %d placed: %d\n",pieces_placed,last->getID());
		    }

		}
	      break; //Out of this loop and onto the next piece.
	    }
	  //Second Criteria: Convex Hull Criteria
	  if (ch_util != -1 && ch_util > gc_used && !placed)
	    {
	      //Use CH criteria to match the pieces
	      if (best_m == 1) //mirror piece
		candidates[best_p]->set_mirror (true);
	      Attach (ch, *candidates[best_p], best_i, best_j); //Attach best values of edge i from convex hull and edge j from piece
	      Feasible_Slide_InSect (current_sect, ch, *candidates[best_p],
				     best_i, best_j, best_d); //Slide edges along best distance
	      //Get the edges of the convex hull to include the guillotine cut.
	      vector<EDGES> ed_ch = *ch.getEdges ();
	      current_sect.add_GC (ed_ch[best_i]);//Include the guillotine cut in the section
	      current_sect.add_piece (*candidates[best_p]);//Include the new piece in the current sect
	      current_bin.include_piece (*candidates[best_p]);//Include piece in the bin
	      current_bin.update_section (current_sect);
	      current_bin.add_GC (ed_ch[best_i]);//add the guillotine cut in the bin.
	      bin_sol[bin_count] = current_bin;
	      candidates.clear ();
	      placed = true;
	      pieces_placed++;
	      break;//Out of this loop and onto the next piece.
	    }
	  //Third Criteria: Make a Guillotine cut on current section and place piece in the new defined section.
	  else if (!placed)//place any of the candidates in the best section defined by best_gc.
	    {
	      placed = Place_in_NewSection (current_sect, candidates, best_gc,
					    current_bin.getNumSect ());
	      if (placed)
		{
		  //Redefine previous section since its limits have changed.
		  vector<PUNTO> *ptos_sec;
		  IRR_BIN sect = current_bin.get_ib (current_sect.getID () - 1);
		  ptos_sec = sect.get_ptos ();
		  *ptos_sec = Redefine_IrrBin_withPieces (*ptos_sec, best_gc);
		  current_bin.update_ptos_sect (sect);
		  //Add the new section to the bin, and update this section
		  current_sect.add_GC (best_gc);//Add the guillotine cut to the section
		  current_bin.add_IB (current_sect);
		  current_bin.add_piece_SectToBin (current_sect);
		  current_bin.add_GC (best_gc);	//Add the guillotine cut to the bin.
		  bin_sol[bin_count] = current_bin;
		  pieces_placed++;
//					vector<PIEZA*> pi = *current_bin.getPI();
//					PIEZA *last = pi.back();
//					printf("Piece %d placed: %d\n",pieces_placed,last->getID());
		  candidates.clear ();
		  break;	//Out of this loop and onto the next piece.
		}
	      else
		{
		  //Fourth criteria: Create new guillotine cuts in the created sections, and fill the new section with one piece, then continue placing pieces.
		  PUNTO gc_empty;
		  gc_empty.coordx = -1;
		  gc_empty.coordy = -1;
		  //========================================
		  if (!placed && current_bin.getNumSect () > 1)
		    {
		      for (int i = 0; i < current_bin.getNumSect (); i++)
			{
			  current_sect = current_bin.get_ib (i);
			  ch = create_convexhull_in_section (current_sect);//Creates the convex hull of pieces in the section
//							ch = create_rectencl_in_section(current_sect); //Rectangle enclosure for the rectangle instances.

			  GuillotineCutWaste (ch, current_sect, best_gc);//Calculates the proportion wasted
			  if (equal_pto (best_gc.ini, gc_empty)
			      && equal_pto (best_gc.fin, gc_empty))//No more gc possible in current section, move to next
			    continue;
			  placed = FillBin (item, current_sect, best_gc,
					    current_bin.getNumSect ());
			  if (placed)
			    {
			      //Redefine previous section since its limits have changed.
			      vector<PUNTO> *ptos_sec;
			      IRR_BIN sect = current_bin.get_ib (i);
			      current_sect.set_ID (current_bin.getNumSect ());
			      ptos_sec = sect.get_ptos ();
			      *ptos_sec = Redefine_IrrBin_withPieces (*ptos_sec,
								      best_gc);
			      current_bin.update_ptos_sect (sect);
			      //Add the new section to the bin, and update this section
			      current_sect.add_GC (best_gc);//Add the guillotine cut to the section
			      current_bin.add_IB (current_sect);
			      current_bin.add_piece_SectToBin (current_sect);
			      current_bin.add_GC (best_gc);//Add the guillotine cut to the bin.
			      bin_sol[bin_count] = current_bin;
			      pieces_placed++;
//								vector<PIEZA*> pi = *current_bin.getPI();
//								PIEZA *last = pi.back();
//								printf("Piece %d placed: %d\n",pieces_placed,last->getID());
			      candidates.clear ();
			      break; //Out of the for loop
			    }
			}
		      if (!placed)
			{ //After analysing all sections, no piece can be added to any new gc.
			  current_bin.setOpen (false);
			  bin_sol[bin_count].setOpen (false);
			}
		    }
		  if (!placed)
		    {
		      bin_count++;
		    }
		  else
		    break; //Piece placed and move to next piece.
		}
	    }
	}
      //CH_IRR_BIN  & Both GC_criteria fail. None of the pieces selected can fit in any of the open bins. We need to open a new bin.
      if ((current_bin.getOpen () && !placed)
	  || (bin_count == bin_sol.size () && !placed)) //If current bin is still open and there is no way of placing the piece with all criteria, or we have closed all existing bins. We need to open a new bin
	{
	  int p = 0;
	  //Open new bin.
	  current_bin.empty_bin ();
	  current_sect.empty_irrbin ();
	  no_bins++;
	  current_bin.initialize_bin (stock_length, stock_width, no_bins); //Initialise new bin.
	  while (item[p].is_placed ())
	    p++; //Move to the first non place piece.
	  OpenBin (current_bin, item[p]); //Place first piece on the candidate list in bin.
	  current_sect = ConvertToIRRBIN (current_bin); //Define the new bin as a first irregular bin.
	  current_bin.add_IB (current_sect);
	  bin_sol.push_back (current_bin);
	  candidates.clear ();
	  placed = true;
	  pieces_placed++;
	}
    }

  vector<PIEZA> pzas;
  for (int i = 0; i < bin_sol[bin_sol.size () - 1].getPI ()->size (); i++)
    {
      PIEZA p = *(*bin_sol[bin_sol.size () - 1].getPI ())[i];
      pzas.push_back (p);
    }

  LastBinRefinementGE (pzas, bin_sol[bin_sol.size () - 1]);
  //Include pieces in the last bin as they have been repacked
  //This part will not be needed for a normal run of the program. However, it is useful to have all information well updated.
  //=================================================================
  double prop_repack = (bin_sol.back ()).getPropUtil ();
  int id_b = (bin_sol.back ()).getID ();
  (bin_sol.back ()).empty_bin ();
  (bin_sol.back ()).setID (id_b);
  for (int i = 0; i < pzas.size (); i++)
    {
      (bin_sol.back ()).include_piece (pzas[i]);
    }
  (bin_sol.back ()).FixUtil (prop_repack);
  //=================================================================
  if (bin_sol.empty ())
    best_of = 0;
  else
    //Objective function Fractional Number of Bins.
    best_of = bin_sol.size () - 1 + (bin_sol.back ()).getPropUtil ();
  //============================================
  //Objective function %Utilization
//    else
//    {
//        level = level + bin_sol.size();
//        best_of = p_of/level;
//    }

//    //Prints the solution obtained with the global evaluation function
//    char ge_inst[200];
//    char instance_name[200];
//    sprintf(ge_inst, "GEnode%d_", id);
//    strcpy(instance_name,"j40");
//    dibujar_bins(bin_sol, instance_name, ge_inst, 0, bin_sol[0].getL(), bin_sol[0].getW(), 1);
  return best_of;
}

IRR_BIN
Redefine_NewSection (vector<PUNTO> &rbin, EDGES gc);
bool
PieceInSect (PIEZA &candidate, IRR_BIN &current_sect);

//Function FillBin (ConsHeur before). Not worth changing the new FillBin function in Open Bin
bool
FillBin (vector<PIEZA> &item, IRR_BIN &csect, EDGES &gc, int id)
{
  bool placed = false;
  IRR_BIN old_sec = csect; //Copy of the section in case no candidates fit in the new section
  vector<PUNTO> sect_points = *csect.get_ptos ();
  //Define the new section we are going to place pieces in
  int bin = csect.getBin ();
  csect = Redefine_NewSection (sect_points, gc);
  csect.set_ID (id);
  csect.setBin (bin);
  sect_points = *csect.get_ptos ();
  //Check wich of the items may fit in the new section in terms of area.
  int count = 0;
  while (count < item.size () && item[count].getArea () > csect.getArea ())
    count++; //Find first piece that may fit in terms of area.
  while (!placed && count < item.size ())
    {
      if (!item[count].is_placed ())
	{
	  placed = PieceInSect (item[count], csect); //Place piece
	  count++;
	}
      else
	count++;
    }
  if (!placed)
    csect = old_sec;
  return placed;
}

//Fucntion that creates the candidate list. 
bool
edge_of_section (EDGES ed, IRR_BIN ib);
double
match_dist (EDGES e1, EDGES e2);

vector<PIEZA*>
CreateList (vector<PIEZA> &item, IRR_BIN &sect)
{
  int LIST_SIZE = 5;
  vector<PIEZA*> list;
  PIEZA convexhull;
  convexhull = create_convexhull_in_section (sect);
  //convexhull = create_rectencl_in_section(sect); //Rectangle enclosure for the rectangle instances.

  vector<EDGES> *e_ch = convexhull.getEdges (); //Edges of the convex hull.
  vector<EDGES> *e_item;
  double area_ch = convexhull.getArea ();
  double area_sect = sect.getArea ();
  int p = 0;
  bool is_ed_sect = false;

  while (item[p].is_placed ())
    {
      p++; //move to the first non placed piece
    }
  while (list.size () < LIST_SIZE && p < item.size ())
    {
      bool is_item_list = false;
      if (item[p].getArea () + area_ch < area_sect && !item[p].is_placed ()) //piece is candidate in terms of area, not being the list and not previusly placed.
	{
	  e_item = item[p].getEdges ();
	  //Compare each edge of the convex hull with each edge of the piece to see if there is a possible match and include the piece in the list.
	  for (int i = 0; i < (*e_ch).size () && !is_item_list; i++) //For each edge of the convex hull
	    {
	      is_ed_sect = edge_of_section ((*e_ch)[i], sect);
	      if (!is_ed_sect) //The edge to match is not in the edge of the bin.
		{
		  for (int j = 0; j < (*e_item).size () && !is_item_list; j++) //For each edge of the piece
		    {
		      double md = match_dist ((*e_ch)[i], (*e_item)[j]); //Calculate md
		      if (md > 0.8) //if edges of convex hull and edges of piece are likely in lenght
			{
			  list.push_back (&item[p]); //include piece in the list.
			  is_item_list = true;
			  p++;
			  break;
			}
		    }
		}
	    }
	  if (!is_item_list) //Item did not make it to the list, because edges are not of matching distance
	    p++; //try next piece.

	}
      else
	p++; //piece does not fit in terms of area, go to next piece.
    }
  return list;
}
