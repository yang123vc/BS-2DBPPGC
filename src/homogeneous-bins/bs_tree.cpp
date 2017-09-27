//
//  bs_tree.cpp
//  BS_Ideas
//
//  Created by Marta Cabo Nodar on 07/05/15.
//  Copyright (c) 2015 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"

vector<PIEZA>
set_available_pzas (NODE &father, vector<PIEZA> &all_pzas);
bool
StoppingCriteria (list<NODE>::iterator &father, list<NODE> &tree);
void
LastBinRefinement (list<NODE> &BS_tree);

//Main function. This Function creates the whole tree.

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

list<NODE>
TREE::get_tree ()
{
  return BS_tree;
}

void
TREE::del_node (list<NODE>::iterator &nodo)
{
  BS_tree.erase (nodo);
}

// Function that performs a local evaluation based on node utilization.
// It will return tue if the node is accepted as a child, and false if not
// accepted.
//
double
Local_of (NODE &node);

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

	if (equal_double (node_util, of_i, TOL)) //In case there are nodes with same utilization, break ties with similar number of pieces.
	  {
	    int node_pieces = node.getNumPiezas ();
	    int c_pzs = children[i].getNumPiezas ();
	    if (node_pieces <= c_pzs) //Keep node with more pieces in it.
	      is_accepted = false;

	  }
      }
  return is_accepted;
}

//Function gives the value of the local evaluation
double
Local_of (NODE &node)
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

// Function that decides if a node enters the tree or not based on global
// evaluation. It will keep the best beta in the BS_tree.
// double ConsHeur(const char *argv,vector<PIEZA> item);//item pass by copy since I don't want to modify its contents ( this heuristic will place items in bins, and I don't want the pieces to be modified )
double
ConsHeur (double stock_width, double stock_length, vector<PIEZA> item,
	  double p_of, int level, int i);

void
KeepBestNodes (NODE &node_eval, vector<GE_COMP> &best_of, vector<int> &keep_id,
	       vector<int> &no_pzas, int b, int a);

void
TREE::global_eval (double stock_length, double stock_width, vector<PIEZA> &item)
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
  while (node_eval->get_level () == last_level)	//Global evaluation done through all elements in a level.
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

//=====================================================================
//Funciones que ya no pertenecen a la clase pero las necesitamos.
//=====================================================================
vector<PIEZA>
set_available_pzas (NODE &father, vector<PIEZA> &all_pzas)
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

void
KeepBestNodes (NODE &node_eval, vector<GE_COMP> &best_of, vector<int> &keep_id,
	       vector<int>&no_pzas, int b, int a)
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
  if (node_of.fractional_n_bins <= lowest_of - PARAM_LAST_BIN)
    {
      is_accepted = true;
    }
  else
    {
      if (node_of.fractional_n_bins <= lowest_of + PARAM_LAST_BIN
	  && node_of.prop_used_current_bin
	      > best_of[best_of.size () - 1].prop_used_current_bin + TOL2)
	{
	  is_accepted = true;
	}
      //else
      //{
      //	int stop = 0;
      //}
    }
  //==================================================================================
  //  if(is_accepted)
  //{
  //for(int i = 0; i<best_of.size(); i++)
  //	{
  //	if(equal_double(node_of.fractional_n_bins, best_of[i].fractional_n_bins, TOL))
  //		{
  //		if(pzas_disp_node >= no_pzas[i])//Keep node with less pieces to place.
  //			is_accepted = false;
  //		}
  //	}
  //}

  //Deleting non accepted nodes.

  if (is_accepted)
    {
      int pos = 0;
      while ((pos < best_of.size () - 1
	  && (node_of.fractional_n_bins
	      >= best_of[pos].fractional_n_bins - PARAM_LAST_BIN))
	  || (node_of.fractional_n_bins
	      >= best_of[pos].fractional_n_bins + PARAM_LAST_BIN
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

//Stopping criteria: Stop when node has no more pieces to place. 
bool
StoppingCriteria (list<NODE>::iterator &node, list<NODE> &tree)
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
