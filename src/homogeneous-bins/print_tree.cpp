//
//  PrintSolution.cpp
//  BS_Ideas
//
//  Created by Marta Cabo Nodar on 05/06/15.
//  Copyright (c) 2015 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"

void
print_solution (const string &data_file_name, const string &output_file_name,
		double runtime, TREE &bs_sol)
{
  list<NODE>::iterator it_child;
  list<NODE> tree;
  tree = bs_sol.get_tree ();
  int last_level;
  it_child = tree.end ();
  it_child--;
  last_level = it_child->get_level ();
  //Identify solution node
  int bestID = -1;
  double bestUtil = GRANDE;
  while (it_child->get_level () == last_level)
    {
      if (it_child->get_IDdisp ().empty ())
	{
	  if (bestUtil > it_child->getPropUtil ())
	    {
	      bestUtil = it_child->getPropUtil ();
	      bestID = it_child->getID ();
	    }
	}
      it_child--;
    }

  //======================
  it_child = tree.end ();
  it_child--;
  while (it_child->get_level () == last_level)
    {
      vector<NODE> branch_sol;
      if (it_child->get_IDdisp ().empty () && it_child->getID () == bestID)
	{
	  NODE child;
	  child = *it_child;
	  while (child.get_Pred () != NULL) //While not at FATHER level
	    {
	      branch_sol.push_back (child);
	      child = *child.get_Pred ();
	    }
	  reverse (branch_sol.begin (), branch_sol.end ());
	  char name[200];
	  sprintf (name, "SOL");
//	  dibujar_nodes (branch_sol, instance_name, name, runtime,
//			 branch_sol[0].getL (), branch_sol[0].getW (), 1);

	  dibujar_nodes (data_file_name, output_file_name, branch_sol, runtime,
			 branch_sol[0].getL (), branch_sol[0].getW (), 1);
	}
      it_child--;
    }
}

void
PrintTree (const char *argv, char *instance_name, TREE &bs_sol, double runtime)
{
  int ins = 0;

  //Print tree
  list<NODE> tree;
  tree = bs_sol.get_tree ();
  list<NODE>::iterator it_child;
  it_child = tree.end ();
  it_child--; //Child points to the last element of the tree
  while (it_child->getID () != 0)
    {
      vector<NODE> branch_sol;
      NODE child;
      child = *it_child;
      while (child.get_Pred () != NULL) //While not at FATHER level
	{
	  branch_sol.push_back (child);
	  child = *child.get_Pred ();
	}
      ins++;
      reverse (branch_sol.begin (), branch_sol.end ());
      char name[200];
      sprintf (name, "TREE(%d)", ins);
//      dibujar_nodes (branch_sol, instance_name, name, runtime,
//		     branch_sol[0].getL (), branch_sol[0].getW (), 1);
      it_child--;

    }
  printf ("\n");
  //============
}
