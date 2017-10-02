/*
 * NODE.hpp
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BS_NODE_HPP_
#define HOMOGENEOUS_BS_NODE_HPP_

#include "PIEZA.hpp"
#include "EDGES.hpp"
#include "IRR_BIN.hpp"

#include <string>
using namespace std;

namespace homogeneous_bs
{

  class NODE
  {
  private:

    int ID;
    int level;
    NODE *predecessor;
    int num_piezas;
    double global_eval;

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

    // piezas incluidas en el bin.
    //
    PIEZA piezas_incluidas[100];

    vector<EDGES> GC;
    vector<IRR_BIN> section;

    // Piezas disponibles para colocar en ese nodo.
    //
    vector<int> ID_pzas_disp;

  public:
    void
    initialize_node (double stock_length, double stock_width, int ID);

    // crea el ID del bin
    //
    void
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

    void
    setDim (const string &name); //Asigna largo y ancho del bin

    double
    getL ()
    {
      return this->L;
    }
    double
    getW ()
    {
      return this->W;
    }

    // calcula el area libre
    //
    void
    setWaste (PIEZA &p)
    {
      waste = waste - p.getArea ();
    }
    double
    get_waste ()
    {
      return waste;
    }

    void
    setOpen (bool op)
    {
      bin_open = op;
    }
    bool
    getOpen ()
    {
      return bin_open;
    }

    // Calcula la proporción utilizada
    //
    void
    setPropUtil ()
    {
      prop_utilizada = 1 - waste / (L * W);
    }
    double
    getPropUtil ()
    {
      return prop_utilizada;
    }

    int
    getNumPiezas ()
    {
      return num_piezas;
    }
    // Incluye una copia de la pieza, pues la misma pieza se va a incluir en
    // varios nodos.
    //
    void
    include_piece (PIEZA p);

    void
    add_GC (EDGES e)
    {
      e.mod = -1;
      GC.insert (GC.begin (), e);
    }
    vector<EDGES> *
    getGC ()
    {
      return (&GC);
    }

    vector<PIEZA*>
    getPI ()
    {
      vector<PIEZA*> p;
      for (int i = 0; i < num_piezas; i++)
	p.push_back (&piezas_incluidas[i]);
      return (p); //Raro que funcione según Toni.. Veremos que hace.
    }

    void
    empty_bin ();

    void
    add_IB (IRR_BIN &ib)
    {
      num_sect++;
      section.push_back (ib);
    }

    int
    getNumSect ()
    {
      return num_sect;
    }
    IRR_BIN
    get_ib (int IDib)
    {
      int i = 0;
      while (section[i].getID () != IDib)
	i++;
      return section[i];
    }
    // Updates the pieces of section(ib) already  in  the bin.
    //
    void
    update_section (IRR_BIN &ib);

    // update the points of sectino ib already in the bin.
    //
    void
    update_ptos_sect (IRR_BIN &ib);

    // Adds a piece from a given section (ib) to the bin
    //
    void
    add_piece_SectToBin (IRR_BIN &ib);

    //=========================
    //Functions related to NODE as a node in a tree, not as a bin object
    inline void
    set_pred (NODE &pred)
    {
      predecessor = &pred;
    }
    NODE *
    get_Pred ()
    {
      return predecessor;
    }

    void
    set_ID_pzas_disp (vector<PIEZA> &pz)
    {
      for (int i = 0; i < pz.size (); i++)
	{
	  if (!pz[i].is_placed ())
	    ID_pzas_disp.push_back (pz[i].getID ());
	}
    }

    void
    update_pzas_disp (int ID)
    {
      int pos = 0;
      while (pos < ID_pzas_disp.size () && ID_pzas_disp[pos] != ID)
	pos++;
      ID_pzas_disp.erase (ID_pzas_disp.begin () + pos);
    }
    vector<int>
    get_IDdisp ()
    {
      return ID_pzas_disp;
    }

    void
    set_level (int level)
    {
      this->level = level;
    }
    int
    get_level ()
    {
      return this->level;
    }

    void
    set_globaleval (double of)
    {
      this->global_eval = of;
    }
    double
    get_globaleval ()
    {
      return this->global_eval;
    }

    // parte del refinement del último bin
    // (porque no sabemos si el corte es horizontal o vertical)?
    //
    void
    FixUtil (double util)
    {
      this->prop_utilizada = util;
    }

    void
    CopyPiecesInSect ();
  };

} /* namespace homogeneous_bs */

#endif /* HOMOGENEOUS_BS_NODE_HPP_ */
