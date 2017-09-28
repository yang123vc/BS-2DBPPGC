/*
 * BIN.hpp
 *
 *  Class BIN from classes_BPGC.hpp (BS-4-2DBPPGC, commit: a1cab62) file,
 *  created by Marta Cabo Nodar on 16/10/14.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BINS_BIN_HPP_
#define HOMOGENEOUS_BINS_BIN_HPP_

#include "PIEZA.hpp"
#include "EDGES.hpp"
#include "IRR_BIN.hpp"

#include <vector>
using namespace std;

namespace homogeneous_bs
{

  class BIN
  {
  private:
    int ID;
    int num_piezas;

    // largo del bin. Se asume L>W.
    //
    double L;

    // Ancho del bin
    //
    double W;

    // area libre
    //
    double waste;

    // proporción del bin utilizada
    //
    double prop_utilizada;

    // True if there is the possibility of placing more items in this bin.
    // False otherwise.
    //
    bool bin_open;

    // number of sections in which the bin is being divided (0 = no divisions)
    //
    int num_sect;

    // Puntero a las piezas incluidas en el bin.
    //
    vector<PIEZA*> piezas_incluidas;

    vector<EDGES> GC;
    vector<IRR_BIN> section;

  public:

    void
    initialize_bin (double stock_length, double stock_width, int i);

    // crea el ID del bin
    //
    inline void
    setID (int id)
    {
      this->ID = id;
    }

    // recupera el ID del bin
    //
    int
    getID ()
    {
      return this->ID;
    }

    // Asigna largo y ancho del bin
    //
    void
    setDim (const string &file_name);

    inline double
    getL ()
    {
      return this->L;
    }
    inline double
    getW ()
    {
      return this->W;
    }
    inline double
    get_waste ()
    {
      return this->waste;
    }
    void
    setOpen (bool open)
    {
      this->bin_open = open;
    }
    bool
    getOpen ()
    {
      return this->bin_open;
    }

    // calcula el area libre
    //
    inline void
    setWaste (PIEZA &p)
    {
      waste = waste - p.getArea ();
    }
    // Calcula la proporción utilizada
    //
    inline void
    setPropUtil ()
    {
      prop_utilizada = 1 - waste / (L * W);
    }
    inline double
    getPropUtil ()
    {
      return prop_utilizada;
    }
    inline int
    getNumPiezas ()
    {
      return num_piezas;
    }
    void
    include_piece (PIEZA &p);

    inline void
    add_GC (EDGES e)
    {
      e.mod = -1;
      GC.insert (GC.begin (), e);
    }

    inline vector<EDGES> *
    getGC ()
    {
      return (&GC);
    }

    inline vector<PIEZA*> *
    getPI ()
    {
      return (&piezas_incluidas);
    }

    void
    empty_bin ();

    inline void
    add_IB (IRR_BIN &ib)
    {
      num_sect++;
      section.push_back (ib);
    }

    inline int
    getNumSect ()
    {
      return num_sect;
    }

    inline IRR_BIN
    get_ib (int id_ib)
    {
      int i = 0;
      while (section[i].getID () != id_ib)
	i++;
      return section[i];
    }

    // Updates the pieces of section(ib) already  in  the bin.
    //
    void
    update_section (IRR_BIN ib);

    // update the points of sectino ib already in the bin.
    //
    void
    update_ptos_sect (IRR_BIN ib);

    // Adds a piece from a given section (ib) to the bin
    //
    void
    add_piece_SectToBin (IRR_BIN ib);

    inline void
    FixUtil (double util)
    {
      prop_utilizada = util;
    }
  };

} /* namespace homogeneous_bs */

#endif /* HOMOGENEOUS_BINS_BIN_HPP_ */
