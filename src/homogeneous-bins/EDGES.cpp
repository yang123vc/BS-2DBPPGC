/*
 * EDGES.cpp
 *
 *  See helpers.hpp for contents description.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#include "EDGES.hpp"
#include <math.h>

namespace homogeneous_bs
{

  void
  EDGES::set_mod ()
  {
    mod = sqrt (
	pow (ini.coordx - fin.coordx, 2) + pow (ini.coordy - fin.coordy, 2));
  }

} /* namespace homogeneous_bs */
