/*
 * entry_point.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: Carlos Alegría Galicia
 */

#include "entry_point.hpp"


namespace homogeneous_bs
{
  result &
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

    result *bs_result = new result;

    high_resolution_clock::time_point time = high_resolution_clock::now ();
    bs_result->solution.build_solution (stock_length, stock_width, pieces);
    bs_result->runtime = chrono::duration_cast<chrono::seconds> (
	high_resolution_clock::now () - time).count ();

    //
    // identifying solution node
    //

    list<NODE>::iterator last_node;
    list<NODE> tree = bs_result->solution.get_tree ();
    last_node = tree.end ();
    last_node--;
    //Calculate area of the bin
    double AreaBin = last_node->getL () * last_node->getW ();
    double Residual = GRANDE;
    bs_result->bins = last_node->get_level ();

    // When OF is Fractional Number of bins, we want the branch with less
    // utilization on the last bin.
    //
    int bestID = -1;
    while (last_node->get_level () == bs_result->bins)
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
    while (last_node->get_level () == bs_result->bins)
      {
	if (last_node->get_IDdisp ().empty () && last_node->getID () == bestID)
	  {
	    Residual = last_node->getPropUtil ();
	  }
	last_node--;
      }

    // Total % Utilization: Calculated as in the Omega Paper:
    //
    bs_result->utilization = accumulate (pieces.begin (), pieces.end (), 0,
					 [](double a, PIEZA &b)
					   { return a + b.getArea();});
    bs_result->utilization /= ((bs_result->bins - 1 + Residual) * AreaBin);
    bs_result->frac_bins = bs_result->bins - 1 + Residual;

    return *bs_result;
  }

} /* namespace homogeneous_bs */
