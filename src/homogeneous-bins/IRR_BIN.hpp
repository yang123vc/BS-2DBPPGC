/*
 * IRR_BIN.hpp
 *
 *  Class IRR_BIN from classes_BPGC.hpp (BS-4-2DBPPGC, commit: a1cab62) file,
 *  created by Marta Cabo Nodar on 16/10/14.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BINS_IRR_BIN_HPP_
#define HOMOGENEOUS_BINS_IRR_BIN_HPP_

#include "PUNTO.hpp"
#include "PIEZA.hpp"
#include "EDGES.hpp"
#include "helpers.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace homogeneous_bs
{

  class IRR_BIN
  {
  private:
    // Independent identifier for the irregular bin
    //
    int ID;

    // Bin ID to which the irregular bin is associated.
    //
    int binID;

    // Total area of the irregular bin.
    //
    double area_ib;

    // free area
    //
    double waste_ib;

    // proportion of the bin used.
    //
    double prop_used;

    // vertices of the bin in clockwise order.
    //
    vector<PUNTO> ib_ptos;

    // Pieces that are included in the irr_bin
    //
    vector<PIEZA*> ib_pzas;

    // Guillotine cuts inside the irregular bin
    //
    vector<EDGES> ib_GC;

    vector<double> ib_angles;

  public:

    inline void
    set_ID (int id)
    {
      this->ID = id;
    }
    inline int
    getID ()
    {
      return this->ID;
    }

    inline void
    setBin (int bin_id)
    {
      this->binID = bin_id;
    }
    int
    getBin (); //Returns the value of binID;

    inline void
    setArea ()
    {
      area_ib = calcular_area_exacta (ib_ptos);
      // reverse ptos, dado que la función anterior está diseñada para polígonos en
      // sentido antihorario, por lo que en este caso hace un reverse de los ptos.
      reverse (ib_ptos.begin (), ib_ptos.end ());
    }
    inline double
    getArea ()
    {
      return this->area_ib;
    }

    inline void
    set_prop_used ()
    {
      prop_used = 1 - waste_ib / area_ib;
    }
    inline double
    get_prop_used ()
    {
      return prop_used;
    }

    inline void
    set_waste (PIEZA &p)
    {
      double area_p = p.getArea ();
      waste_ib = area_ib - area_p;
    }
    inline double
    get_waste ()
    {
      return this->waste_ib;
    }

    void
    empty_irrbin ();

    inline void
    add_piece (PIEZA &p)
    {
      // Incluimos pieza p en el bin (i.e. aumentamos en uno el número de piezas
      // e incluimos la pieza en el vector piezas_incluidas.
      ib_pzas.push_back (&pza);
      //Actualizar largo y ancho utilizado y waste;
      set_waste (pza);
      set_prop_used ();
    }
    inline void
    add_points (PUNTO &pto)
    {
      ib_ptos.push_back (pto);
    }
    inline void
    add_GC (EDGES &e)
    {
      ib_GC.push_back (e);
    }
    vector<double>
    get_angles ();

    inline vector<PUNTO> *
    get_ptos ()
    {
      return &ib_ptos;
    }
    inline vector<PIEZA*> *
    get_pzas ()
    {
      return (&ib_pzas);
    }
    inline vector<EDGES> *
    get_ibGC ()
    {
      return (&ib_GC);
    }
  };

} /* namespace homogeneous_bs */

#endif /* HOMOGENEOUS_BINS_IRR_BIN_HPP_ */
