/*
 * entry_point_2.hpp
 *
 *  Created on: Sep 19, 2017
 *      Author: calegria
 */

#ifndef HOMOGENEOUS_BINS_ENTRY_POINT_HPP_
#define HOMOGENEOUS_BINS_ENTRY_POINT_HPP_

#include "help_functions.hpp"
#include "PIEZA.hpp"
#include "TREE.hpp"
using namespace homogeneous_bs;

#include <string>
#include <vector>
#include <numeric>
using namespace std;

#include <chrono>
using chrono::high_resolution_clock;

void
beam_search (const string &data_file_name, double stock_length,
	     double stock_width)
{
  //
  // reading pieces
  //

  vector<PIEZA> pieces;
  read_pieces (data_file_name, pieces);

  // sort by area
  //
  sort (pieces.begin (), pieces.end (), [] (PIEZA &a, PIEZA &b)
    {
      return (a.getArea() > b.getArea());
    });


  //
  // constructing solution
  //

  TREE bs_sol;

  high_resolution_clock::time_point time = high_resolution_clock::now ();
  bs_sol.build_solution (stock_length, stock_width, pieces);
  auto runtime = chrono::duration_cast<chrono::seconds> (
      high_resolution_clock::now () - time).count ();


  //
  // identifying solution node
  //

  list<NODE>::iterator last_node;
  list<NODE> tree = bs_sol.get_tree ();
  last_node = tree.end ();
  last_node--;
  //Calculate area of the bin
  double AreaBin = last_node->getL () * last_node->getW ();
  int last_level = last_node->get_level ();
  double Residual = GRANDE;

  // When OF is Fractional Number of bins, we want the branch with less
  // utilization on the last bin.
  //
  int bestID = -1;
  while (last_node->get_level () == last_level)
    {
      if (last_node->get_IDdisp ().empty ())
	{
	  if (Residual > last_node->getPropUtil ())
	    {
	      Residual = last_node->getPropUtil ();
	      bestID = last_node->getID ();
	    }
	}
      last_node--;
    }

  // Retrieve best solution
  //
  last_node = tree.end ();
  last_node--;
  while (last_node->get_level () == last_level)
    {
      if (last_node->get_IDdisp ().empty () && last_node->getID () == bestID)
	{
	  Residual = last_node->getPropUtil ();
	}
      last_node--;
    }

  // Total % Utilization: Calculated as in the Omega Paper:
  //
  double utilization = accumulate (pieces.begin (), pieces.end (), 0,
				   [](double a, PIEZA &b)
				     { return a + b.getArea();});
  utilization /= ((last_level - 1 + Residual) * AreaBin);
  double Frac_N_Bins = last_level - 1 + Residual;


  //
  // printing results
  //

  cout << "Results " << string(80, '=') << endl;
  cout << "Number of bins: " << last_level << endl;
  cout << "Number of Bins (fractional): " << Frac_N_Bins << endl;
  cout << "Utilization (%): " << utilization << endl;
  cout << "Running time (miliseconds): " << runtime << endl;
}

#endif /* HOMOGENEOUS_BINS_ENTRY_POINT_HPP_ */
