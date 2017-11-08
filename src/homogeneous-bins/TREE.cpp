/*
 * TREE.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#include "TREE.hpp"
#include "BIN.hpp"

#include "help_functions.hpp"

#include <cmath>

namespace homogeneous_bs
{
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
						    No_Rots, HBS_ALPHA);
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
				      current_sect.getArea (), HBS_TOL)
			|| current_sect.get_waste () < pza_c[last].getArea ()) //Current section filled up, useless to try it.
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
			    current_bin.add_GC (gc[j]);	//Add the guillotine cut to the bin.
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
		current_bin.setOpen (false); //No more candidates for this bin, bin closed.
		//current_bin.CopyPiecesInSect();
		return;
	      }
	  }
	//Candidate list not empty
	//=========================
	//Place candidates
	int sec_mod_id = -1;
	placed = Place_Candidates (current_bin, current_sect, candidates,
				   CH_crit, bestCG_crit, NextCG_crit, best_gc,
				   sec_mod_id);
	//==================================
	if (!placed)
	  {
	    //Place any other piece
	    candidates.clear ();
	    candidates = CreateList (pza_c, current_sect, pzas.size (), 0,
				     current_bin.get_IDdisp ());
	    placed = Place_Candidates (current_bin, current_sect, candidates,
				       CH_crit, bestCG_crit, NextCG_crit,
				       best_gc, sec_mod_id); //Candidate placed in current_sec.

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
		current_bin.add_GC (best_gc); //Add the guillotine cut to the bin.
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
		current_bin.add_GC (best_gc); //Add the guillotine cut to the bin.

	      }
	  }
      }
  }

  bool
  TREE::local_eval (vector<NODE> &children, NODE &node)
  {
    bool is_accepted = false;

    if (children.empty ())
      return true;

    if (children.size () < alpha)
      {
	is_accepted = true;
      }
    //Children vector is ordered in descending order of its local evaluation objective function
    double node_util = Local_of (node);
    double worst_util = Local_of (children[children.size () - 1]);
    if (node_util > worst_util)
      is_accepted = true;
    //Last check: node is not repeated in any of the previous children entries:
    if (is_accepted)
      for (int i = 0; i < children.size (); i++)
	{
	  double of_i = Local_of (children[i]);

	  if (equal_double (node_util, of_i, HBS_TOL)) //In case there are nodes with same utilization, break ties with similar number of pieces.
	    {
	      int node_pieces = node.getNumPiezas ();
	      int c_pzs = children[i].getNumPiezas ();
	      if (node_pieces <= c_pzs) //Keep node with more pieces in it.
		is_accepted = false;

	    }
	}
    return is_accepted;
  }

  void
  TREE::global_eval (double stock_length, double stock_width,
		     vector<PIEZA> &item)
  {
    vector<double> all_of; //vector of best values of the objective function after global eval.

    list<NODE>::iterator node_eval; //node_eval: pointer to the node we are evaluating
    list<NODE>::iterator ini_level; //ini_level: pointer to initial node on level, to know the limits to which make comparisons.
    node_eval = BS_tree.end ();
    ini_level = BS_tree.end ();
    --ini_level; //ini_level points to the last element on the tree (that corresponds to a limit on the level).
    --node_eval; //node_eval points to the last element on the tree.
    int last_level = node_eval->get_level ();
    double of; //Virtual objective function when following that branch.
    //vector<double> best_of;//vector of best values of the objective function after global eval.
    vector<GE_COMP> best_of; //vector of best values of the objective function after global eval. -> TONI
    vector<int> keep_id;	//node id's that stay after global evaluation
    vector<int> no_pzas_disp;
    while (node_eval->get_level () == last_level)//Global evaluation done through all elements in a level.
      {
	vector<PIEZA> pzas_avail;
	pzas_avail = set_available_pzas (*node_eval, item);
	NODE node;
	node = *node_eval;
	//Find value of the objective function up to that point.
	double level = 0;
	double partial_of = 0;
	while (node.get_Pred () != NULL)
	  {
	    //===========================================
	    //Objective Function: Material Usage
	    //===========================================
	    partial_of = partial_of + node.getPropUtil ();
	    level++;
	    //============================================
	    node = *node.get_Pred ();
	  }
	of = ConsHeur (stock_length, stock_width, pzas_avail, partial_of, level,
		       node_eval->getID ());
	node_eval->set_globaleval (of);

	// Modify best_of and keep_id so it stores the id's of the nodes to keep.
	//
	KeepBestNodes (*node_eval, best_of, keep_id, no_pzas_disp, beta, alpha);
	--node_eval;      //Next node to perform global eval. (previous in tree)
      }
    //Delete nodes with id not in Keep_id
    while (ini_level->getID () != node_eval->getID ())
      {
	if (find (keep_id.begin (), keep_id.end (), ini_level->getID ())
	    == keep_id.end ())
	  {
	    //ini_level points to a node that needs to be eliminated.
	    del_node (ini_level);
	    ini_level = BS_tree.end ();
	  }
	ini_level--;
      }
  }

  // Function gives the value of the local evaluation
  //
  double
  TREE::Local_of (NODE &node)
  {
    double of;
    int np = node.getNumPiezas ();
    vector<PIEZA*> pz = node.getPI ();
    of = 0;
    double bin_area = node.getL () * node.getW ();
    for (int i = 0; i < np; i++)
      {
	double sum = 0;
	sum = pz[i]->getArea () / bin_area;
	of += sum;
      }
    //of = node.getPropUtil(); //In this case, the local evaluation equals the utilization of the bin
    return of;
  }

  void
  TREE::KeepBestNodes (NODE &node_eval, vector<GE_COMP> &best_of,
		       vector<int> &keep_id, vector<int>&no_pzas, int b, int a)
  {
    if (best_of.empty ())
      {
	GE_COMP gg;
	gg.fractional_n_bins = node_eval.get_globaleval ();
	gg.prop_used_current_bin = node_eval.getPropUtil ();
	keep_id.push_back (node_eval.getID ());
	no_pzas.push_back ((node_eval.get_IDdisp ()).size ());
	best_of.push_back (gg);

	//best_of.push_back(node_eval.get_globaleval());
	//keep_id.push_back(node_eval.getID());
	//no_pzas.push_back((node_eval.get_IDdisp()).size());

	return;
      }
    bool is_accepted = false;
    if (best_of.size () < b)
      {
	is_accepted = true;
      }
    //best_of vector is ordered in descending order of its utilization
    GE_COMP node_of;
    node_of.fractional_n_bins = node_eval.get_globaleval ();
    node_of.prop_used_current_bin = node_eval.getPropUtil ();
    int pzas_disp_node = node_eval.get_IDdisp ().size ();
    //Acceptance criterion if we want the branch with higher percentage of utilization
    //    double highest_of = best_of[best_of.size()-1];
    //	if(node_of >= highest_of)
    //		is_accepted = true;
    //==================================================================================
    //Acceptance criterion if we want the branch with smaller fractional number of bins.
    double lowest_of = best_of[best_of.size () - 1].fractional_n_bins;
    if (node_of.fractional_n_bins <= lowest_of - HBS_PARAM_LAST_BIN)
      {
	is_accepted = true;
      }
    else
      {
	if (node_of.fractional_n_bins <= lowest_of + HBS_PARAM_LAST_BIN
	    && node_of.prop_used_current_bin
		> best_of[best_of.size () - 1].prop_used_current_bin + HBS_TOL2)
	  {
	    is_accepted = true;
	  }
	//else
	//{
	//	int stop = 0;
	//}
      }

    //Deleting non accepted nodes.

    if (is_accepted)
      {
	int pos = 0;
	// cambiar a pos < best_of.size () - 1 en el futuro
	//
	while ((pos < best_of.size () - 1
	    && (node_of.fractional_n_bins
		>= best_of[pos].fractional_n_bins - HBS_PARAM_LAST_BIN))
	    || (node_of.fractional_n_bins
		>= best_of[pos].fractional_n_bins + HBS_PARAM_LAST_BIN
		&& node_of.prop_used_current_bin
		    < best_of[pos].prop_used_current_bin
		&& pos < best_of.size () - 1))
	  pos++;
	best_of.insert (best_of.begin () + pos, node_of);
	keep_id.insert (keep_id.begin () + pos, node_eval.getID ());
	no_pzas.insert (no_pzas.begin () + pos, pzas_disp_node);

	if (best_of.size () > b)
	  {
	    best_of.pop_back ();
	    keep_id.pop_back ();
	    no_pzas.pop_back ();
	  }
      }

  }

  vector<PIEZA>
  TREE::set_available_pzas (NODE &father, vector<PIEZA> &all_pzas)
  {
    vector<PIEZA> avail_pzas;
    vector<int> avail_id = father.get_IDdisp ();
    for (int i = 0; i < avail_id.size (); i++)
      {
	int id = avail_id[i];
	int p = 0;
	while (all_pzas[p].getID () != id)
	  p++;
	avail_pzas.push_back (all_pzas[p]);
      }

    return avail_pzas;
  }

  double
  TREE::ConsHeur (double stock_length, double stock_width, vector<PIEZA> item,
		  double p_of, int level, int id)
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

    // While not all the pieces have been placed
    //
    while (pieces_placed < problem_size)
      {
	// best utilization of the convex hull when the next piece is attached.
	//
	double ch_util = -1;
	int best_i = -1; //Best edge of the ch
	int best_j = -1; //Best edge of the piece
	int best_p = -1; //Best piece from list
	int best_m = -1; // =0 piece not mirrored
	double best_d = -1; // best slide distance.
	int bin_count = 0;

	// best utilization of the bin, when the guillotine cut is performed.
	//
	double gc_waste = -1;
	EDGES best_gc;
	int no_sects = -1; //number of sections of current bin;

	// placed = true if any piece from the list is placed in the current
	// bin.
	//
	bool placed = false;
	while (bin_count < bin_sol.size ())
	  {
	    //Move to first open bin
	    while (bin_count < bin_sol.size () && !bin_sol[bin_count].getOpen ())
	      bin_count++;
	    if (bin_count >= bin_sol.size ())
	      break; //NO more bins to try, open new bin
	    current_bin = bin_sol[bin_count];
	    no_sects = current_bin.getNumSect ();

	    // Always start from the last section created.
	    //
	    current_sect = current_bin.get_ib (no_sects - 1);

	    // We need to eplore one section at a time. Not starting from the
	    // last section created.
	    ch = create_convexhull_in_section (current_sect);
	    //ch = create_rectencl_in_section(current_sect); //Rectangle enclosure for the rectangle instances.

	    //Create a list of next pieces to be placed.
	    //
	    candidates = CreateList (item, current_sect);

	    // No unplaced piece fits in the last section created.
	    //
	    if (candidates.empty ())
	      {
		int i = 0;

		// Check if it is possible to have candidates to any of the
		// other sections.
		//
		while (candidates.empty () && i < current_bin.getNumSect ())
		  {
		    current_sect = current_bin.get_ib (i);
		    candidates = CreateList (item, current_sect);
		    i++;
		  }
		if (candidates.empty ())
		  {
		    // No more candidates for this bin, bin closed.
		    //
		    current_bin.setOpen (false);
		    bin_sol[bin_count].setOpen (false);
//		    printf ("BIN %d Closed (no more candidates)\n", current_bin.getID ());
		    bin_count++;			//move to next bin
		    continue;
		  }
		else // We have changed the section so we need to recalculate the convex hull.
		  {
		    ch = create_convexhull_in_section (current_sect);
		    //ch = create_rectencl_in_section(current_sect); //Rectangle enclosure for the rectangle instances.
		  }
	      }

	    //Check CH util
	    //=================================
	    ch_util = SelectBestMatch (current_sect, candidates, ch, best_i,
				       best_j, best_d, best_p, best_m);
	    // Calculates the proportion wasted
	    //
	    gc_waste = GuillotineCutWaste (ch, current_sect, best_gc);

	    double gc_used = 1 - gc_waste;
	    double bin_used = current_bin.getPropUtil ();

	    // First criteria:
	    // If the bin is already more than 80% used: Fill the bin and close
	    // it
	    //
	    if (bin_used > 0.80) //Place pieces in remaining space according to best guillotine cut.
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
			if (equal_double (ch.getArea (),
					  current_sect.getArea (),
					  HBS_TOL)
			    || current_sect.get_waste ()
				< item[last].getArea ()) //Current section filled up, useless to try it.
			  {
			    i--;		//Move to previous section
			    placed = false;
			    continue;
			  }
			GuillotineCutWaste (ch, current_sect, best_gc);
			PUNTO gc_empty;
			gc_empty.coordx = -1;
			gc_empty.coordy = -1;
			if (equal_pto (best_gc.ini, gc_empty)
			    && equal_pto (best_gc.fin, gc_empty))//No more gc possible in current section, move to next
			  {
			    i--;		//Move to previous section
			    placed = false;
			    continue;
			  }
			//===========================================
			placed = FillBin (item, current_sect, best_gc,
					  current_bin.getNumSect ());
			if (!placed)
			  {
			    i--;		//Move to previous section
			    continue;
			  }
			else
			  break; //Piece placed,
		      }
		    if (!placed)
		      {
			current_bin.setOpen (false); //No more fits. Close bin.
			bin_sol[bin_count].setOpen (false);
//			printf ("BIN %d Closed (+80%)\n", current_bin.getID ());
		      }
		    else //place piece
		      {
			// Redefine previous section since its limits have
			// changed.
			//
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
//			vector<PIEZA*> pi = *current_bin.getPI ();
//			PIEZA *last = pi.back ();
//			printf ("Piece %d placed: %d\n", pieces_placed,
//				last->getID ());
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

		// Attach best values of edge i from convex hull and edge j from
		// piece
		//
		Attach (ch, *candidates[best_p], best_i, best_j);

		// Slide edges along best distance
		//
		Feasible_Slide_InSect (current_sect, ch, *candidates[best_p],
				       best_i, best_j, best_d);

		// Get the edges of the convex hull to include the guillotine
		// cut
		//
		vector<EDGES> ed_ch = *ch.getEdges ();
		// Include the guillotine cut in the section
		//
		current_sect.add_GC (ed_ch[best_i]);
		// Include the new piece in the current sect
		//
		current_sect.add_piece (*candidates[best_p]);
		// Include piece in the bin
		//
		current_bin.include_piece (*candidates[best_p]);
		current_bin.update_section (current_sect);
		// add the guillotine cut in the bin.
		//
		current_bin.add_GC (ed_ch[best_i]);
		bin_sol[bin_count] = current_bin;
		candidates.clear ();
		placed = true;
		pieces_placed++;
//		printf ("Piece %d placed: %d\n", pieces_placed,
//			candidates[best_p]->getID ());
		break; // Out of this loop and onto the next piece.
	      }
	    // Third Criteria: Make a Guillotine cut on current section and
	    // place piece in the new defined section.
	    //
	    else if (!placed) //place any of the candidates in the best section defined by best_gc.
	      {
		placed = Place_in_NewSection (current_sect, candidates, best_gc,
					      current_bin.getNumSect ());
		if (placed)
		  {
		    //Redefine previous section since its limits have changed.
		    vector<PUNTO> *ptos_sec;
		    IRR_BIN sect = current_bin.get_ib (
			current_sect.getID () - 1);
		    ptos_sec = sect.get_ptos ();
		    *ptos_sec = Redefine_IrrBin_withPieces (*ptos_sec, best_gc);
		    current_bin.update_ptos_sect (sect);
		    //Add the new section to the bin, and update this section
		    current_sect.add_GC (best_gc); //Add the guillotine cut to the section
		    current_bin.add_IB (current_sect);
		    current_bin.add_piece_SectToBin (current_sect);
		    current_bin.add_GC (best_gc);//Add the guillotine cut to the bin.
		    bin_sol[bin_count] = current_bin;
		    pieces_placed++;
//		    vector<PIEZA*> pi = *current_bin.getPI ();
//		    PIEZA *last = pi.back ();
//		    printf ("Piece %d placed: %d\n", pieces_placed,
//			    last->getID ());
		    candidates.clear ();
		    break;	//Out of this loop and onto the next piece.
		  }
		// Fourth criteria: Create new guillotine cuts in the created
		// sections, and fill the new section with one piece, then
		// continue placing pieces.
		//
		else
		  {
		    PUNTO gc_empty;
		    gc_empty.coordx = -1;
		    gc_empty.coordy = -1;
		    //========================================
		    if (!placed && current_bin.getNumSect () > 1)
		      {
			for (int i = 0; i < current_bin.getNumSect (); i++)
			  {
			    current_sect = current_bin.get_ib (i);

			    // Creates the convex hull of pieces in the section
			    //
			    ch = create_convexhull_in_section (current_sect);
//			    ch = create_rectencl_in_section (current_sect); //Rectangle enclosure for the rectangle instances.

			    // Calculates the proportion wasted
			    //
			    GuillotineCutWaste (ch, current_sect, best_gc);
			    if (equal_pto (best_gc.ini, gc_empty)
				&& equal_pto (best_gc.fin, gc_empty)) //No more gc possible in current section, move to next
			      continue;
			    placed = FillBin (item, current_sect, best_gc,
					      current_bin.getNumSect ());
			    if (placed)
			      {
				// Redefine previous section since its limits
				// have changed
				//
				vector<PUNTO> *ptos_sec;
				IRR_BIN sect = current_bin.get_ib (i);
				current_sect.set_ID (current_bin.getNumSect ());
				ptos_sec = sect.get_ptos ();
				*ptos_sec = Redefine_IrrBin_withPieces (
				    *ptos_sec, best_gc);
				current_bin.update_ptos_sect (sect);
				// Add the new section to the bin, and update
				// this section
				current_sect.add_GC (best_gc); //Add the guillotine cut to the section
				current_bin.add_IB (current_sect);
				current_bin.add_piece_SectToBin (current_sect);
				current_bin.add_GC (best_gc); //Add the guillotine cut to the bin.
				bin_sol[bin_count] = current_bin;
				pieces_placed++;
//				vector<PIEZA*> pi = *current_bin.getPI ();
//				PIEZA *last = pi.back ();
//				printf ("Piece %d placed: %d\n", pieces_placed,
//					last->getID ());
				candidates.clear ();
				break; //Out of the for loop
			      }
			  }
			if (!placed)
			  { // After analysing all sections, no piece can be
			    // added to any new gc.
			    //
			    current_bin.setOpen (false);
			    bin_sol[bin_count].setOpen (false);
			    //printf("BIN %d Closed (No more pieces)\n", current_bin.getID());
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
	// CH_IRR_BIN  & Both GC_criteria fail. None of the pieces selected can
	// fit in any of the open bins. We need to open a new bin.
	//
	if ((current_bin.getOpen () && !placed)
	    || (bin_count == bin_sol.size () && !placed)) //If current bin is still open and there is no way of placing the piece with all criteria, or we have closed all existing bins. We need to open a new bin
	  {
	    int p = 0;
	    // Open new bin.
	    current_bin.empty_bin ();
	    current_sect.empty_irrbin ();
	    no_bins++;
	    current_bin.initialize_bin (stock_length, stock_width, no_bins); //Initialise new bin.
	    while (item[p].is_placed ())
	      p++; //Move to the first non place piece.
	    // Place first piece on the candidate list in bin.
	    //
	    OpenBin (current_bin, item[p]);
	    // Define the new bin as a first irregular bin.
	    //
	    current_sect = ConvertToIRRBIN (current_bin);
	    current_bin.add_IB (current_sect);
	    bin_sol.push_back (current_bin);
	    candidates.clear ();
	    placed = true;
	    pieces_placed++;
	    //printf("Piece %d placed: %d\n",pieces_placed, item[p].getID());
	  }
      }

//    for (int i = 0; i < bin_sol.size (); i++)
//      {
//	BIN b = bin_sol[i];
//	p_of = p_of + bin_sol[i].getPropUtil ();
//	cout << "Bin:" << b.getID () << " Pieces: ";
//	for (int j = 0; j < b.getPI ()->size (); j++)
//	  {
//	    PIEZA p = *(*b.getPI ())[j];
//	    int IDpza = p.getID ();
//	    cout << IDpza << " ";
//	  }
//
//	cout << "\n";
//      }

    vector<PIEZA> pzas;
    for (int i = 0; i < bin_sol[bin_sol.size () - 1].getPI ()->size (); i++)
      {
	PIEZA p = *(*bin_sol[bin_sol.size () - 1].getPI ())[i];
	pzas.push_back (p);
      }

    LastBinRefinementGE (pzas, bin_sol[bin_sol.size () - 1]);
    // Include pieces in the last bin as they have been repacked
    // This part will not be needed for a normal run of the program. However, it
    // is useful to have all information well updated.
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

  bool
  TREE::StoppingCriteria (list<NODE>::iterator &node, list<NODE> &tree)
  {
    bool stop = false;
    list<NODE>::iterator it_n;
    it_n = node;
    while (it_n != tree.end ())
      {
	if (it_n->get_IDdisp ().empty ()) // current node has no more pieces to place.
	  {
	    return true;
	  }
	it_n++;
      }

    return stop;
  }

  void
  TREE::build_solution (double stock_length, double stock_width,
			vector<PIEZA> &pieces)
  {
    alpha = 2;
    beta = 3;

    int No_Childs = 10; //10 (diff first piece)
    int No_Rots = 3; // (2 rotations for rectangle instances) 3 (rotations of first piece) * 2 (Mirror(Yes / No))
    list<NODE>::iterator father;
    NODE InitialNode;
    NODE *aaa = NULL;
    InitialNode.initialize_node (stock_length, stock_width, 0);
    InitialNode.set_ID_pzas_disp (pieces);
    InitialNode.set_level (0);
    InitialNode.set_pred (*aaa);
    vector<PIEZA> pzas_avail;
    pzas_avail = set_available_pzas (InitialNode, pieces);
    BS_tree.push_back (InitialNode);
    father = BS_tree.begin ();
    bool stop = false;
    int count = 1;
    while (!stop)
      {
	//Find available pieces for child nodes.
	pzas_avail = set_available_pzas (*father, pieces);
	if (pzas_avail.empty ())
	  {
	    break;
	  }
	if (pzas_avail.size () < No_Childs)
	  No_Childs = pzas_avail.size (); // If less than NoChilds available pieces, recalculate.
	//=====================================
	//Create NoChilds*NoRots*2 children and keep alpha best.
	create_child (stock_length, stock_width, No_Childs, No_Rots, *father,
		      pzas_avail);
	//=====================================
	int nodestot = 0;
	int l = 0;
	while (nodestot < beta)
	  {
	    l++;
	    nodestot = pow (alpha, l);
	  }
	if (BS_tree.back ().get_level () < l)
	  {
	    ++father; //No global evaluation for the first level children.
	    continue;
	  }
	//Global evaluation at the end of each level.
	list<NODE>::iterator next_father;
	next_father = father;
	++next_father; //next father should now point to the next element in the tree after father.
	if (next_father->get_level () != father->get_level ()) //We are at the end of a level.
	  {
	    //Renumber nodes ID so we have no duplicates when deleting nodes in global evaluation
	    int level = next_father->get_level ();
	    list<NODE>::iterator node_level;
	    node_level = next_father;
	    int id = level * 100;
	    for (node_level = next_father; node_level != BS_tree.end ();
		node_level++)
	      node_level->setID (++id);
	    //==============================
	    stop = StoppingCriteria (next_father, BS_tree);
	    if (!stop)
	      {
		global_eval (stock_length, stock_width, pieces);
		count++;
	      }
	    else
	      break;
	  }
	//===========================================
	++father;
      }
    LastBinRefinement (BS_tree);
  }

} /* namespace homogeneous_bs */
