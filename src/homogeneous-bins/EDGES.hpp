/*
 * EDGES.hpp
 *
 *  Class EDGES from classes_BPGC.hpp (BS-4-2DBPPGC, commit: a1cab62) file,
 *  created by Marta Cabo Nodar on 16/10/14.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BINS_EDGES_HPP_
#define HOMOGENEOUS_BINS_EDGES_HPP_

#include "PUNTO.hpp"

namespace homogeneous_bs
{

  class EDGES
  {
  public:
    PUNTO ini;
    PUNTO fin;
    double mod; //Stores the lenght of the edge.

    void
    set_mod ();
  };

} /* namespace homogeneous_bs */

#endif /* HOMOGENEOUS_BINS_EDGES_HPP_ */
