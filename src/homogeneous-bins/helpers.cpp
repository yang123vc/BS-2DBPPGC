/*
 * helpers.cpp
 *
 *  See helpers.hpp for contents description.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#include "helpers.hpp"

#include  <vector>
#include <algorithm>
using namespace std;

namespace homogeneous_bs
{
  vector<double>
  calculateInnerAngles (vector<EDGES> &ar)
  {
    vector<double> angles;
    double angle;
    double numer, denom;
    EDGES aux;
    //Obtain first angle
    long last = ar.size () - 1;
    //Set aux edge
    aux.ini = ar[last].ini;
    aux.fin = ar[0].fin;
    aux.set_mod ();
    //Cosine Law a^2 = b^2 + c^2 - 2bccos(angle(bc)).
    numer = pow (ar[last].mod, 2) + pow (ar[0].mod, 2) - pow (aux.mod, 2);
    denom = 2 * ar[last].mod * ar[0].mod;
    angle = acos (numer / denom) * 180.0 / PI;
    angles.push_back (angle);

    //Obtain remaining angles
    for (int i = 1; i < ar.size (); i++)
      {
	//Set aux edge
	aux.ini = ar[i - 1].ini;
	aux.fin = ar[i].fin;
	aux.set_mod ();
	//Cosine law for the remaining of the angles
	numer = pow (ar[i - 1].mod, 2) + pow (ar[i].mod, 2) - pow (aux.mod, 2);
	denom = 2 * ar[i - 1].mod * ar[i].mod;
	angle = acos (numer / denom) * 180.0 / PI;
	angles.push_back (angle);
      }
    return angles;
  }

  double
  calcular_area_exacta (vector<PUNTO> &poligono)
  {
    if (poligono.empty () == true)
      return -1;
    if (poligono.size () < 3)
      return -1;
    double suma = 0;
    //Calculo del área utilizando la fórmula A = 1/2(x(i)y(i+1) - x(i+1)y(i))
    for (int i = 0; i < poligono.size () - 1; i++) //Sentido antihorario
      {
	suma += poligono[i].coordx * poligono[i + 1].coordy
	    - poligono[i].coordy * poligono[i + 1].coordx;
      } //for
	//ahora el ultimo con el primero
    int i = poligono.size () - 1;
    suma += poligono[i].coordx * poligono[0].coordy
	- poligono[i].coordy * poligono[0].coordx;
    //Si la suma es negativa, entonces recorremos los vértices en sentido horario
    if (suma <= TOL)
      {
	std::reverse (poligono.begin (), poligono.end ());
      }
    return fabs (suma) / 2;
  }

  // This function returns the convex hull (as a piece) of all the pieces in one
  // section of the bin.
  //
  PIEZA
  create_convexhull_in_section (IRR_BIN &sect)
  {
    PIEZA convexhull;
    vector<PIEZA*> *pb = sect.get_pzas (); //pb pieces in bin.
    vector<PUNTO> ptos_sect; //vector que contiene todos los puntos de las piezas que están en la sección. Para construir el convex hull.
    vector<PUNTO> ptos_pza; //Puntos de cada pieza.
    vector<PUNTO> ch_sect;
    vector<PUNTO>::iterator it_pto;
    vector<PIEZA*>::iterator it_pza;
    //Create the convex hull of the pieces in the bin.
    //===============================================================
    convexhull.setID ((-1) * sect.getID ());	//convex hull ID = -ID sect.
    convexhull.setbin (sect.getID ());//Indicates the bin in which these pieces are placed.
    for (it_pza = pb->begin (); it_pza != pb->end (); it_pza++)
      {
	ptos_pza = *(*it_pza)->obtener_puntos ();
	for (it_pto = ptos_pza.begin (); it_pto != ptos_pza.end (); it_pto++)
	  {
	    ptos_sect.push_back (*it_pto);
	  }
      }
    ch_sect = convex_hull (ptos_sect);//Returns points in the convex hull counter clockwise. Last point equals to first.
    for (int i = 0; i < ch_sect.size () - 1; i++)//Delete all duplicates created by numerical errors with convexhull.
      {
	if (equal_pto (ch_sect[i], ch_sect[i + 1]))
	  {
	    ch_sect.erase (ch_sect.begin () + i);
	  }
      }
    ch_sect.back ();	//Move to last point in vector
    ch_sect.pop_back (); //Delete last entry

    for (int i = 0; i < ch_sect.size (); i++)
      convexhull.add_point (ch_sect[i]); //adds convexhull points to convexhull (piece).
    convexhull.initialize_piece ();
    //Redefine edges, since ptos iniciales are placed in origin.
    convexhull.ini_edges ();
    return convexhull;
  }

  // Returns a list of points on the convex hull in counter-clockwise order.
  // Note: the last point in the returned list is the same as the first one.
  vector<PUNTO>
  convex_hull (vector<PUNTO> P)
  {
    unsigned long n = P.size ();
    int k = 0;
    vector<PUNTO> H (2 * n);
    //Initialize vector H to (-100, -100)
    for (int i = 0; i < H.size (); i++)
      {
	H[i].coordx = -100;
	H[i].coordy = -100;
      }
    // Sort points lexicographically
    sort (P.begin (), P.end (), lexicographic);

    // Build lower hull
    for (int i = 0; i < n; ++i)
      {
	while (k >= 2 && cross (H[k - 2], H[k - 1], P[i]) <= 0)
	  k--;
	H[k++] = P[i];
      }

    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--)
      {
	while (k >= t && cross (H[k - 2], H[k - 1], P[i]) <= 0)
	  k--;
	H[k++] = P[i];
      }

    H.resize (k);
    return H;
  }

  bool
  equal_double (double a, double b, double prec)
  {
    if (a >= b - prec && a <= b + prec)
      return true;
    else
      return false;
  }

} /* namespace homogeneous_bs */
