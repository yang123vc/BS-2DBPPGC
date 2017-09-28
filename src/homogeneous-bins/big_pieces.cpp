//
//  Big Pieces.cpp
//  BS_Ideas
//
//  Created by Marta Cabo Nodar on 27/06/16.
//  Copyright © 2016 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"
using namespace homogeneous;

double
calculate_rotation_match (EDGES &e1, EDGES &e2);
vector<PUNTO>
rotation_puntos (vector<PUNTO> &pp, double alpha);

bool
PlaceBigPieces (PIEZA &item, BIN bin)
{
  bool placed = false;
  vector<PUNTO> p_item = *item.obtener_puntos ();
  double Mdist = -GRANDE;
  EDGES diag_max;
  EDGES diag_bin;
  EDGES base_bin;
  base_bin.fin.coordx = 0.0;
  base_bin.fin.coordy = 0.0;
  base_bin.ini.coordx = bin.getL ();
  base_bin.ini.coordy = 0.0;

  diag_bin.fin.coordx = 0.0;
  diag_bin.fin.coordy = 0.0;
  diag_bin.ini.coordx = bin.getL ();
  diag_bin.ini.coordy = bin.getW ();
  double dist;
  //Calcular la distancia más larga entre dos vértices de la pza.
  for (int i = 0; i < p_item.size (); i++)
    {
      for (int j = 0; j < p_item.size (); j++)
	{
	  dist = distancia (p_item[i], p_item[j]);
	  if (dist > Mdist)
	    {
	      diag_max.ini.coordx = p_item[i].coordx;
	      diag_max.ini.coordy = p_item[i].coordy;
	      diag_max.fin.coordx = p_item[j].coordx;
	      diag_max.fin.coordy = p_item[j].coordy;
	      Mdist = dist;
	    }
	}
    }
  if (diag_max.mod > diag_bin.mod + TOL)
    {
      placed = false;
      cout << "Piece is bigger than bin\n";
      exit (1);
    }
  //============================================================
  double ang = calculate_rotation_match (diag_max, base_bin);
  item.obtener_rotacion (ang);
  item.set_ptos_diag_rot ();
  vector<PUNTO> ptos_diag_base = item.get_ptos_diag_rot (); //Guarda la rotación que "pega" la diagonal más larga a la base del bin.
  ang = calculate_rotation_match (diag_max, diag_bin);
  item.obtener_rotacion (ang);
  //Calculate ang_max (beta), ang_min(alpha), and sets S,T,B.
  double y, x;
  y = sqrt (pow (diag_max.mod, 2) - pow (bin.getL (), 2));
  double alpha = asin (y / diag_max.mod) * 180 / PI;
  x = sqrt (pow (diag_max.mod, 2) - pow (bin.getW (), 2));
  double beta = acos (x / diag_max.mod) * 180 / PI;
  vector<PUNTO> S, T, B;
  //Set of points outside the bin.
  for (int i = 0; i < p_item.size (); i++)
    {
      if (p_item[i].coordx < 0 - TOL && p_item[i].coordy < bin.getW ())
	S.push_back (p_item[i]);
      if (p_item[i].coordx > 0 + TOL && p_item[i].coordy > bin.getW () + TOL)
	T.push_back (p_item[i]);
      if (p_item[i].coordx < 0 - TOL && p_item[i].coordy < 0 - TOL)
	B.push_back (p_item[i]);
    }
  if (S.empty () && B.empty () && T.empty ())
    placed = true;
  //Rotate pts_diag_base angle beta
  vector<PUNTO> p_aux;
  p_aux = rotation_puntos (ptos_diag_base, beta);
  for (int i = 0; i < p_aux.size (); i++)
    {
      if (p_aux[i].coordy > bin.getW () + TOL)
	T.push_back (p_aux[i]);
      if (!T.empty ())
	{
	  //Encontrar el ángulo que hay que girar los ptos T para que queden dentro del bin.
	  for (int j = 0; j < T.size (); j++)
	    {

	    }
	}
    }

  return false;
}

vector<PUNTO>
rotation_puntos (vector<PUNTO> &pp, double alpha)
{
  vector<PUNTO>::iterator it;
  vector<PUNTO> ppp;

  double angulo_aux = 2 * PI * alpha / 360;

  for (it = pp.begin (); it != pp.end (); it++)
    {
      double modulo = sqrt (
	  (*it).coordx * (*it).coordx + (*it).coordy * (*it).coordy);
      double tita = PI / 2; // SI x=0 :: y>0
      if (modulo < TOL && modulo > -TOL)
	tita = 0;
      else
	{
	  if ((*it).coordx < TOL && (*it).coordx > -TOL && (*it).coordy < -TOL) // SI x>0 :: y>=0
	    {
	      tita = 3 * PI / 2;
	    }
	  if ((*it).coordx > TOL && (*it).coordy >= 0) // SI x>0 :: y>=0
	    {
	      tita = atan ((*it).coordy / (*it).coordx);
	    }
	  if ((*it).coordx > TOL && (*it).coordy < -TOL) // SI x>0 :: y<0
	    {
	      tita = atan ((*it).coordy / (*it).coordx) + 2 * PI;
	    }
	  if ((*it).coordx < -TOL) // SI x<0
	    {
	      tita = atan ((*it).coordy / (*it).coordx) + PI;
	    }
	}

      PUNTO p_aux;
      p_aux.coordx = modulo * cos (angulo_aux + tita);
      p_aux.coordy = modulo * sin (angulo_aux + tita);
      ppp.push_back (p_aux);
    }
//    for (int i=0;i<ppp.size();i++)
//    {
//        EDGES e_aux;
//        e_aux.ini=ppp[i];
//        if (i<ppp.size()-1)
//            e_aux.fin=ppp[i+1];
//        else
//            e_aux.fin=ppp[0];
//        sol.push_back(e_aux);
//    }
  return ppp;
}
