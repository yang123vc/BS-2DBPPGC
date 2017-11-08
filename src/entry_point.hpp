/*
 * entry_point_2.hpp
 *
 *  Created on: Sep 19, 2017
 *      Author: calegria
 */

#ifndef HOMOGENEOUS_BINS_ENTRY_POINT_HPP_
#define HOMOGENEOUS_BINS_ENTRY_POINT_HPP_

#include "homogeneous-bins/TREE.hpp"
#include "heterogeneous-bins/classes_BPGC_HetBins.hpp"

#include <string>
#include <vector>
#include <numeric>
#include <utility>
#include <map>
using namespace std;

#include <chrono>
using chrono::high_resolution_clock;

namespace homogeneous_bs
{

  typedef struct
  {
    int bins;
    double frac_bins;
    double utilization;
    chrono::seconds::rep runtime;
    TREE solution;
  } result;

  result &
  beam_search (const string &data_file_name, double stock_length,
	       double stock_width);

} /* namespace homogeneous_bs */

namespace heterogeneous_bs
{
  // pair.first := bin length
  // pair.second := bin width
  //
  typedef pair<double, double> bin_size;

  typedef vector<string> stock_names;
  typedef map<string, bin_size> stock_sizes;

  // const stock_names & := a vector of bin ids in reading order from command line
  // const stock_sizes & := a map of bin sizes indexed by bin ids
  //
  typedef pair<const stock_names &, const stock_sizes &> stock_spec;

  typedef struct
  {
    //
    // best global evaluation
    //

    // level
    //
    int bge_level;

    // number of bins
    //
    int bge_bins_no;

    // utilization
    //
    double bge_utilization;

    //
    // solution
    //

    // level
    //
    int sol_level;

    // fractional number of bins
    //
    double sol_bins_frac;

    // utilization
    //
    double sol_utilization;

    // the sum of the areas
    //
    double sol_area_pz;

    // runtime
    //
    chrono::seconds::rep runtime;
  } result;

  const result
  beam_search (const string &data_file_name, const stock_spec &stock,
	       TREE &bs_sol);

} /* namespace heterogeneous_bs */

#endif /* HOMOGENEOUS_BINS_ENTRY_POINT_HPP_ */
