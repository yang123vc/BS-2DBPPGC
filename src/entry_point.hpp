/*
 * entry_point_2.hpp
 *
 *  Created on: Sep 19, 2017
 *      Author: calegria
 */

#ifndef HOMOGENEOUS_BINS_ENTRY_POINT_HPP_
#define HOMOGENEOUS_BINS_ENTRY_POINT_HPP_

#include <string>
#include <vector>
#include <numeric>
using namespace std;

#include <chrono>
using chrono::high_resolution_clock;

#include "homogeneous-bins/classes_BPGC.hpp"

typedef struct {
  int bins;
  double frac_bins;
  double utilization;
  chrono::seconds::rep runtime;
  TREE solution;
} result;

result &
beam_search (const string &data_file_name, double stock_length,
	     double stock_width);


#endif /* HOMOGENEOUS_BINS_ENTRY_POINT_HPP_ */
