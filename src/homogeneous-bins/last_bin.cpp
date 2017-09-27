//
//  LastBin.cpp
//  BS_Ideas
//
//  Created by Marta Cabo Nodar on 17/07/15.
//  Copyright (c) 2015 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"

double
ArrangeHor (vector<PIEZA> &pzas, NODE &node);
double
ArrangeVert (vector<PIEZA> &pzas, NODE &node);
bool
orden_area (PIEZA i, PIEZA j);
PIEZA
create_convexhull_in_section (IRR_BIN &sect);
PIEZA
create_rectencl_in_section (IRR_BIN &s);
bool
MoveDownInSect (PIEZA &ch, IRR_BIN &sec, double slide);
bool
MoveLeftInSect (PIEZA &ch, IRR_BIN &sec, double slide);
void
LastBinRefinement (list<NODE> &tree)
{
  list<NODE>::iterator it_node;
  it_node = tree.end ();
  it_node--;
  double hor_util = (-1) * GRANDE;
  double ver_util = (-1) * GRANDE;
  int last_level = it_node->get_level ();
  while (it_node->get_level () == last_level) //At last level
    {
      if ((it_node->get_IDdisp ()).empty ()) //If node is the last bin on a solution
	{
	  NODE lastbin = *it_node; //Copy of last node
	  it_node->CopyPiecesInSect ();
	  //get pieces from last node
	  vector<PIEZA> pzas;
	  for (int i = 0; i < it_node->getPI ().size (); i++)
	    {
	      PIEZA p = *(it_node->getPI ())[i];
	      pzas.push_back (p);
	    }
	  //========================
	  sort (pzas.begin (), pzas.end (), orden_area);
	  hor_util = ArrangeHor (pzas, *it_node);
	  if (hor_util == (-1) * GRANDE)
	    {
	      it_node->CopyPiecesInSect ();
	      double maxheight = -1;
	      for (int id = 0; id < it_node->getNumSect (); id++)
		{
		  bool is_feasible = true;
		  IRR_BIN sec = it_node->get_ib (id);
		  PIEZA ch = create_convexhull_in_section (sec);
//					PIEZA ch = create_rectencl_in_section(sec); //Rectangle enclosure for the rectangle instances.

		  double slide = 0;
		  while (is_feasible)
		    {
		      is_feasible = MoveDownInSect (ch, sec, slide);
		      slide = 5;
		    }
		  for (int i = 0; i < (*ch.obtener_puntos ()).size (); i++)
		    {
		      double p = (*ch.obtener_puntos ())[i].coordy;
		      if (maxheight < p)
			maxheight = (*ch.obtener_puntos ())[i].coordy;
		    }
		  if (equal_double (maxheight, it_node->getW (), TOL))
		    break;
		}
	      hor_util = maxheight / it_node->getW ();
	      if (hor_util < 0)
		hor_util = 1.0;
	    }
	  NODE lastbin_hor = *it_node;
	  *it_node = lastbin;
	  ver_util = ArrangeVert (pzas, *it_node);
	  if (ver_util == (-1) * GRANDE)
	    {
	      it_node->CopyPiecesInSect ();
	      double maxlength = -1;
	      for (int id = 0; id < it_node->getNumSect (); id++)
		{
		  bool is_feasible = true;
		  IRR_BIN sec = it_node->get_ib (id);
		  PIEZA ch = create_convexhull_in_section (sec);
//					PIEZA ch = create_rectencl_in_section(sec); //Rectangle enclosure for the rectangle instances.

		  double slide = 0;
		  while (is_feasible)
		    {
		      is_feasible = MoveLeftInSect (ch, sec, slide);
		      slide = 5;
		    }
		  for (int i = 0; i < (*ch.obtener_puntos ()).size (); i++)
		    {
		      double p = (*ch.obtener_puntos ())[i].coordx;
		      if (maxlength < p)
			maxlength = (*ch.obtener_puntos ())[i].coordx;
		    }
		  if (equal_double (maxlength, it_node->getL (), TOL))
		    break;
		}
	      ver_util = maxlength / it_node->getL ();
	      if (ver_util < 0)
		ver_util = 1.0;
	    }
	  NODE lastbin_vert = *it_node;
	  if (ver_util > 0 && ver_util < hor_util + TOL)
	    {
	      *it_node = lastbin_vert;
	      it_node->FixUtil (ver_util);

	    }
	  if (hor_util > 0 && hor_util < ver_util + TOL)
	    {
	      *it_node = lastbin_hor;
	      it_node->FixUtil (hor_util);
	    }
	}
      it_node--;
    }

}

double
ArrangeHorGE (vector<PIEZA> &pzas, BIN &node);
double
ArrangeVertGE (vector<PIEZA> &pzas, BIN &node);

void
LastBinRefinementGE (vector<PIEZA> &pzas, BIN &sol)
{

  double hor_util = (-1) * GRANDE;
  double ver_util = (-1) * GRANDE;
  BIN lastbin = sol; //Copy of last node
  //Calculate the horizontal utilization with the pieces in the original position
  double orig_hor_util = (-1);
  double orig_vert_util = (-1);
  vector<PIEZA> pzas_orig = pzas;

  for (int p = 0; p < pzas.size (); p++)
    {
      vector<PUNTO> pto = *pzas[p].obtener_puntos ();
      for (int i = 0; i < pto.size (); i++)
	{
	  if (pto[i].coordy > orig_hor_util)
	    orig_hor_util = pto[i].coordy;
	  if (pto[i].coordx > orig_vert_util)
	    orig_vert_util = pto[i].coordx;
	}
    }
  orig_hor_util = orig_hor_util / sol.getW ();
  orig_vert_util = orig_vert_util / sol.getL ();
//    cout<<"\nRepacking bin: "<<sol.getID()<<"\n";

  vector<PIEZA> pzas_hor = pzas;
  sort (pzas_hor.begin (), pzas_hor.end (), orden_area);
  hor_util = ArrangeHorGE (pzas_hor, sol);
  if (hor_util == (-1) * GRANDE)
    {
      double maxheight = -1;
      for (int id = 0; id < sol.getNumSect (); id++)
	{
	  bool is_feasible = true;
	  IRR_BIN sec = sol.get_ib (id);
	  PIEZA ch = create_convexhull_in_section (sec);
	  //					PIEZA ch = create_rectencl_in_section(sec); //Rectangle enclosure for the rectangle instances.

	  double slide = 0;
	  while (is_feasible)
	    {
	      is_feasible = MoveDownInSect (ch, sec, slide);
	      slide = 5;
	    }
	  for (int i = 0; i < (*ch.obtener_puntos ()).size (); i++)
	    {
	      double p = (*ch.obtener_puntos ())[i].coordy;
	      if (maxheight < p)
		maxheight = (*ch.obtener_puntos ())[i].coordy;
	    }
	  if (equal_double (maxheight, sol.getW (), TOL))
	    break;
	}
      hor_util = maxheight / sol.getW ();
      if (hor_util < 0)
	hor_util = 1.0;
      if (hor_util > orig_hor_util)
	{
	  hor_util = orig_hor_util;
	  pzas_hor = pzas_orig;
	}
    }
//    BIN lastbin_hor = sol;
  sol = lastbin;
  vector<PIEZA> pzas_vert = pzas;
  sort (pzas_vert.begin (), pzas_vert.end (), orden_area);
  ver_util = ArrangeVertGE (pzas_vert, sol);
  if (ver_util == (-1) * GRANDE)
    {
      double maxlength = -1;
      for (int id = 0; id < sol.getNumSect (); id++)
	{
	  bool is_feasible = true;
	  IRR_BIN sec = sol.get_ib (id);
	  PIEZA ch = create_convexhull_in_section (sec);
//			PIEZA ch = create_rectencl_in_section(sec); //Rectangle enclosure for the rectangle instances.

	  double slide = 0;
	  while (is_feasible)
	    {
	      is_feasible = MoveLeftInSect (ch, sec, slide);
	      slide = 5;
	    }
	  for (int i = 0; i < (*ch.obtener_puntos ()).size (); i++)
	    {
	      double p = (*ch.obtener_puntos ())[i].coordx;
	      if (maxlength < p)
		maxlength = (*ch.obtener_puntos ())[i].coordx;
	    }
	  if (equal_double (maxlength, sol.getL (), TOL))
	    break;
	}
      ver_util = maxlength / sol.getL ();
      if (ver_util < 0)
	ver_util = 1.0;
      if (ver_util > orig_vert_util)
	{
	  ver_util = orig_vert_util;
	  pzas_vert = pzas_orig;
	}

    }
//    BIN lastbin_vert = sol;
  if (ver_util > 0 && ver_util < hor_util + TOL)
    {
      pzas = pzas_vert;
      //sol = lastbin_vert;
      sol.FixUtil (ver_util);

    }
  if (hor_util > 0 && hor_util < ver_util + TOL)
    {
      pzas = pzas_hor;
//        sol = lastbin_hor;
      sol.FixUtil (hor_util);
    }

}

