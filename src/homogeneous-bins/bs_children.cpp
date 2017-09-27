//
//  bs_children.cpp
//  BS_Ideas
//
//  Created by Marta Cabo Nodar on 27/05/15.
//  Copyright (c) 2015 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"

IRR_BIN
ConvertToIRRBIN (NODE &bin);
PIEZA
create_convexhull_in_section (IRR_BIN &sect);
PIEZA
create_rectencl_in_section (IRR_BIN &sect);
vector<PIEZA*>
CreateList (vector<PIEZA> &item, IRR_BIN &sect, int LIST_SIZE, double thres,
	    vector<int> ID_disp);
double
GuillotineCutWaste (PIEZA ch, IRR_BIN current_sect, EDGES &best_gc);
vector<PUNTO>
Redefine_IrrBin_withPieces (vector<PUNTO> &rbin, EDGES gc);
bool
FillBin (vector<PIEZA> &item, IRR_BIN &csect, EDGES &gc, int sectID,
	 vector<int> ID_disp);
bool
Place_Candidates (NODE &node, IRR_BIN &sect, vector<PIEZA*> &list,
		  bool &CH_crit, bool &bestCG_crit, bool &NextCG_crit,
		  EDGES &gc, int &sec_mod_id);
bool
edge_of_section (EDGES ed, IRR_BIN ib);
EDGES
IntersectBin (EDGES gc, vector<PUNTO> rbin);
vector<double>
calculate_rotations_FitNode (NODE &b, PIEZA &p, int num_rot, double epsilon);

// Function that creates the children of a node.
void
TREE::create_child (double stock_length, double stock_width, int No_Childs,
		    int No_Rots, NODE &father, vector<PIEZA> &pzas_disp)
{
  NODE current_node;
  vector<NODE> children;
  int bin = (father.get_level () + 1) * 100;
  current_node.initialize_node (stock_length, stock_width, ++bin);
  current_node.set_pred (father);
  vector<double> try_rots;
  //LEVEL 0
  //==========================================================
  //Add info to current_node.
  current_node.set_ID_pzas_disp (pzas_disp);
  for (int i = 0; i < No_Childs; i++)	//For each piece
    {
      vector<PIEZA> pzas_c = pzas_disp;	//Copia de las piezas
      bool is_symetric = false;
//		for (int m = 0; m <=0; m++) //No mirror for rectangles.

      for (int m = 0; m <= 1; m++) //For every  mirror
	{
	  if (m == 1)
	    {
	      is_symetric = pzas_c[i].set_mirror (true);
	      try_rots.clear ();
	    }
	  if (m == 1 && is_symetric)
	    continue;
	  try_rots = calculate_rotations_FitNode (current_node, pzas_c[i],
						  No_Rots, ALPHA);
	  for (int r = 0; r < try_rots.size (); r++) //For each rotation
	    {
	      is_symetric = pzas_c[i].obtener_rotacion (try_rots[r]);
	      if (is_symetric && try_rots[r] != 0)
		continue; //Rotation does nothing, no point on trying to place it again.
	      if (pzas_c[i].Fits_Bin (current_node.getL (),
				      current_node.getW ()))
		{
		  PIEZA p = pzas_c[i];
		  current_node.include_piece (p); //Includes copy of pza[i] in node and eliminates its ID from the vector of available ID's.
//					printf("\nNODE %d:\n Piece %d, \n",current_node.getID(), p.getID());
		  fill_node (current_node, pzas_c);
		  bool is_node_child = false;
		  //Local evaluation
		  //=========================================================
		  is_node_child = local_eval (children, current_node);
		  //Check that accepted node does not share any first piece with the existing nodes.
		  for (int i = 0; i < children.size (); i++)
		    {
		      PIEZA pza_node = *(current_node.getPI ())[0];
		      PIEZA pza_child = *(children[i].getPI ())[0];
		      if (pza_child.getID () == pza_node.getID ())
			{
			  //If current node has better utilization, delete child
			  if (current_node.getPropUtil ()
			      > children[i].getPropUtil ())
			    {
			      //Delete child (same first piece as current node and worst utilization
			      vector<NODE>::iterator it_ch;
			      it_ch = children.begin ();
			      it_ch = it_ch + i;
			      children.erase (children.begin () + i);
			    }
			  else
			    {
			      is_node_child = false;
			      break;			//Skip to next node
			    }
			}
		    }
		  //========================================================================================
		  if (is_node_child)
		    {
		      if (children.empty ())
			{
			  current_node.set_level (father.get_level () + 1);
			  children.push_back (current_node);
			}
		      else
			{
			  //Accept child and include it in descending order of their utilization
			  int pos = 0;
			  double node_util = current_node.getPropUtil ();
			  while (pos < children.size ()
			      && node_util <= children[pos].getPropUtil ())
			    pos++;
			  current_node.set_level (father.get_level () + 1);
			  children.insert (children.begin () + pos,
					   current_node);
			  if (children.size () > alpha)
			    children.pop_back ();
			}

		    }
		  //==========================================================
		  //Empty node
		  current_node.empty_bin ();
		  //Create a new one.
		  current_node.setID (++bin);
		  current_node.set_ID_pzas_disp (pzas_c);
		  current_node.set_pred (father);
		}
	    }
	}
    }
  for (int i = 0; i < children.size (); i++)
    {
      BS_tree.push_back (children[i]);
    }
}

//========================================================================
//Function that fills a node of the tree.
//Fill node (child) with pzas (copy of pza) having the first piece placed.
//Use critera as in constructive heuristic.
//========================================================================
void
TREE::fill_node (NODE &current_bin, vector<PIEZA> &pzas)
{
  IRR_BIN current_sect;
  current_sect = ConvertToIRRBIN (current_bin);
  current_bin.add_IB (current_sect);
  PIEZA convex_hull;
  vector<PIEZA> pza_c = pzas;				//Copia de las piezas,
  while (current_bin.getOpen () && !current_bin.get_IDdisp ().empty ())
    {
      vector<PIEZA*> candidates;
      EDGES best_gc;
      bool placed = false;//indicates if at any iteration the piece was placed or not.
      bool CH_crit = false; //indicates if the piece has been placed with the ch_crit.
      bool bestCG_crit = false;
      bool NextCG_crit = false;
      double bin_used = current_bin.getPropUtil ();
      //BIN usage greater than 80%
      if (bin_used > 0.80) //Fill bin.
	{
	  int last = pza_c.size () - 1;
	  int old_i = current_bin.getNumSect () - 1;
	  while (current_bin.getOpen ())
	    {
	      placed = false;
	      int i = current_bin.getNumSect () - 1;
	      while (old_i >= 0 && i >= 0)
		{
		  current_sect = current_bin.get_ib (i);
		  convex_hull = create_convexhull_in_section (current_sect);
//					convex_hull = create_rectencl_in_section(current_sect); //Rectangle enclosure for the rectangle instances.
		  //==============================================
		  //Select an appropriate section that may allocate more pieces.
		  if (equal_double (convex_hull.getArea (),
				    current_sect.getArea (), TOL)
		      || current_sect.get_waste () < pza_c[last].getArea ())//Current section filled up, useless to try it.
		    {
		      i--;			//Move to previous section
		      if (i == old_i)
			old_i--;
		      continue;
		    }
		  vector<EDGES> gc = *convex_hull.getEdges ();//gc vector with all possible guillotine cuts that can be performed.
		  vector<PUNTO> ptos_sect = *current_sect.get_ptos ();
		  for (int j = 0; j < gc.size (); j++)
		    {
		      if (edge_of_section (gc[j], current_sect))
			continue;
		      gc[j] = IntersectBin (gc[j], ptos_sect);
		      placed = FillBin (pza_c, current_sect, gc[j],
					current_bin.getNumSect (),
					current_bin.get_IDdisp ());
		      if (placed)
			{
			  //Redefine previous section since its limits have changed.
			  vector<PUNTO> *ptos_sec;
			  IRR_BIN sect = current_bin.get_ib (i);
			  ptos_sec = sect.get_ptos ();
			  *ptos_sec = Redefine_IrrBin_withPieces (*ptos_sec,
								  gc[j]);
			  current_bin.update_ptos_sect (sect);
			  //Add the new section to the bin, and update this section
			  current_bin.add_IB (current_sect);
			  current_bin.add_piece_SectToBin (current_sect);
			  current_bin.add_GC (gc[j]);//Add the guillotine cut to the bin.
			  break;
			}
		    }
		  if (!placed)
		    {
		      i--;	//Move to previous section
		      if (i == old_i)
			old_i--;
		      continue;
		    }
		  else
		    break; //Piece placed,
		}
	      if (!placed)
		{
		  current_bin.setOpen (false); //No more fits. Close bin.
		  //current_bin.CopyPiecesInSect();
		  return;
		}
	    }
	}
      //Create candidate list (5 candidates).
      candidates = CreateList (pza_c, current_sect, 5, .8,
			       current_bin.get_IDdisp ());
      if (candidates.empty ())
	{
	  int i = 0;
	  //Check if it is possible to have candidates in any of the other sections.
	  while (candidates.empty () && i < current_bin.getNumSect ())
	    {
	      current_sect = current_bin.get_ib (i);
	      candidates = CreateList (pza_c, current_sect, 5, .8,
				       current_bin.get_IDdisp ());
	      i++;
	    }
	  if (candidates.empty ())
	    {
	      current_bin.setOpen (false);//No more candidates for this bin, bin closed.
	      //current_bin.CopyPiecesInSect();
	      return;
	    }
	}
      //Candidate list not empty
      //=========================
      //Place candidates
      int sec_mod_id = -1;
      placed = Place_Candidates (current_bin, current_sect, candidates, CH_crit,
				 bestCG_crit, NextCG_crit, best_gc, sec_mod_id);
      //==================================
      if (!placed)
	{
	  //Place any other piece
	  candidates.clear ();
	  candidates = CreateList (pza_c, current_sect, pzas.size (), 0,
				   current_bin.get_IDdisp ());
	  placed = Place_Candidates (current_bin, current_sect, candidates,
				     CH_crit, bestCG_crit, NextCG_crit, best_gc,
				     sec_mod_id); //Candidate placed in current_sec.

	}
      //==================================
      //No pieces could be placed
      if (!placed)
	{
	  current_bin.setOpen (false);
	  //current_bin.CopyPiecesInSect();
	  return;
	}
      //============================
      //Place is True.
      else
	{
	  //Find piece that has been placed
	  PIEZA last;
	  vector<PIEZA*> pi = *current_sect.get_pzas ();
	  last = *pi.back ();	//last is the last piece inserted in current sec
	  //Piece placed with Convex Hull Criteria
	  if (CH_crit)
	    {
	      //Include piece
	      current_bin.include_piece (last);
	      current_bin.update_section (current_sect);
	      //Include new guillotine cut.
	      EDGES last_gc = (current_sect.get_ibGC ())->back ();
	      current_bin.add_GC (last_gc);
	    }
	  //========================================
	  //Piece placed with Best Guillotine Criteria
	  else if (bestCG_crit)
	    {
	      //Redefine previous section since its limits have changed.
	      vector<PUNTO> *ptos_sec;
	      IRR_BIN sect = current_bin.get_ib (sec_mod_id);
	      ptos_sec = sect.get_ptos ();
	      *ptos_sec = Redefine_IrrBin_withPieces (*ptos_sec, best_gc);
	      current_bin.update_ptos_sect (sect);
	      //Add the new section to the bin, and update this section
	      current_sect.set_ID (current_bin.getNumSect ());
	      current_bin.add_IB (current_sect);
	      current_bin.add_piece_SectToBin (current_sect);
	      current_bin.add_GC (best_gc);//Add the guillotine cut to the bin.
	    }
	  //========================================
	  //Piece placed with the Next Best Guillotine Criteria
	  else if (NextCG_crit)
	    {
	      //Redefine previous section since its limits have changed.
	      vector<PUNTO> *ptos_sec;
	      IRR_BIN sect = current_bin.get_ib (sec_mod_id);
	      ptos_sec = sect.get_ptos ();
	      *ptos_sec = Redefine_IrrBin_withPieces (*ptos_sec, best_gc);
	      current_bin.update_ptos_sect (sect);
	      //Add the new section to the bin, and update this section
	      current_bin.add_IB (current_sect);
	      current_bin.add_piece_SectToBin (current_sect);
	      current_bin.add_GC (best_gc);//Add the guillotine cut to the bin.

	    }
	}
    }
}
//=======================================================================
