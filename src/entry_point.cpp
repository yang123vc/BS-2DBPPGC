/*
 * entry_point.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: Carlos Alegría Galicia
 */

#include "entry_point.hpp"

#include "homogeneous-bins/PIEZA.hpp"
#include "homogeneous-bins/help_functions.hpp"
#include "heterogeneous-bins/classes_BPGC_HetBins.hpp"

#include <algorithm>
using namespace std;

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
    double Residual = HBS_GRANDE;
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

namespace heterogeneous_bs
{

  const result
  beam_search (const string &data_file_name, const stock_spec &stock,
	       TREE &bs_sol)
  {
    result bs_result;

    //
    // reading pieces
    //

    vector<PIEZA> item;
    item = read_pieces (data_file_name);

    //
    // ordering pieces by area
    //

    sort (item.begin (), item.end (), orden_area);
    double AreaPz = 0;
    for (int i = 0; i < item.size (); i++)
      {
	AreaPz = AreaPz + item[i].getArea ();
      }

    //
    // computing solution (with time measure)
    //

    high_resolution_clock::time_point time = high_resolution_clock::now ();
    bs_sol.build_solution (stock, item);
    bs_result.runtime = chrono::duration_cast<chrono::seconds> (
	high_resolution_clock::now () - time).count ();

    //
    // extracting best global evaluation information
    //

    const std::tuple<vector<NODE> &, double &, int &> &best_solution =
	bs_sol.getBestSolution ();

    bs_result.bge_level = std::get<2> (best_solution);
    bs_result.bge_bins_no = get<0> (best_solution).size ();
    bs_result.bge_utilization = get<1> (best_solution);

//    get<BGE_SOL_BRANCH>(*bs_result) = get<0> (best_solution);

    //
    // extracting solution information (identifying solution node)
    //

    int best_level = -1;
    double best_use = -GRANDE;
    double residual = 0;
      {
	list<NODE> tree = bs_sol.get_tree ();
	list<NODE>::iterator it_child = tree.end ();
	it_child--;
	int bestID = -1;

	while (it_child != tree.begin ())
	  {
	    if (it_child->get_IDdisp ().empty ())
	      {
		//Find %Utilization on that branch
		NODE branch;
		branch = *it_child;
		double AreaB = 0;
		int level = 0;
		double res = branch.getPropUtil ();
		while (branch.get_Pred () != NULL)
		  {
		    // OF Multi Bin Instances:
		    // %Utilization = Area Pzas /(Area Bins)
		    AreaB = AreaB + branch.getL () * branch.getW ();
		    // ============================================
		    branch = *branch.get_Pred ();
		    level++;
		  }
		double Util = AreaPz / AreaB;
		if (best_use < Util)
		  {
		    //Keep the info for the branch with best OF
		    best_use = Util;
		    residual = res;
		    best_level = level;
		    bestID = it_child->getID ();
		  }
	      }
	    it_child--;
	  }
      }

      bs_result.sol_level = best_level;

    get<SOL_BINS_FRAC> (bs_result) = best_level - 1 + residual;
    get<SOL_UTILIZATION> (bs_result) = best_use;
//    get<SOL_BRANCH> (*bs_result) = bs_sol.get_tree ();
    get<SOL_AREA_PZ> (bs_result) = AreaPz;

    return bs_result;
  }

} /* namespace heterogeneous_bs */
