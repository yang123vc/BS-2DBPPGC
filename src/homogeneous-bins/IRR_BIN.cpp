/*
 * IRR_BIN.cpp
 *
 *  See IRR_BIN.hpp for contents description.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#include "IRR_BIN.hpp"
#include <vector>
#include <iostream>

#include "help_functions.hpp"
using namespace std;

namespace homogeneous_bs
{

  void
  IRR_BIN::empty_irrbin ()
  {
    ID = -1;
    binID = -1;
    prop_used = 0;
    ib_pzas.clear ();
    ib_ptos.clear ();
    ib_angles.clear ();
    ib_GC.clear ();
  }

  vector<double>
  IRR_BIN::get_angles ()
  {
    vector<EDGES> ar;
    EDGES aux;
    int last = ib_ptos.size ();
    //Create edges of IRRBIN
    for (int i = 0; i < last; i++)
      {
	aux.ini = ib_ptos[i];
	if (i + 1 != last)
	  aux.fin = ib_ptos[i + 1];
	else
	  aux.fin = ib_ptos[0];
	aux.set_mod ();
	ar.push_back (aux);
      }
    ib_angles = calculateInnerAngles (ar);
    return ib_angles;
  }
} /* namespace homogeneous_bs */
