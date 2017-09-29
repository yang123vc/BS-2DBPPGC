/*
 * main.cpp
 *
 *  Created on: May 27, 2017
 *      Author: calegria
 */

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
namespace po = boost::program_options;
namespace fs = boost::filesystem;

#include <cstdlib>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include "entry_point.hpp"

// the help command-line option
//
#define OP_HELP  "help"
#define OPS_HELP "h"

// the bin length and width command-line option, length >= width
//
#define OP_BINS  "bins"
#define OPS_BINS "s"

// the filter width and beam width parameters for the beam search algorithm
//
#define OP_FILTER_WIDTH  "filter-width"
#define OPS_FILTER_WIDTH "f"
#define OPD_FILTER_WIDTH 2
#define OP_BEAM_WIDTH    "beam-width"
#define OPS_BEAM_WIDTH   "b"
#define OPD_BEAM_WIDTH   3

// the name of the file containing the pieces information
//
#define OP_DATA "data"
#define OPS_DATA "d"

// the *.tex output filename
//
#define OP_OUTPUT  "output"
#define OPS_OUTPUT "o"

// flag indicating whether to print verbose messages or not
//
#define OP_VERBOSE  "verbose"
#define OPS_VERBOSE "v"

// the text width when writing text to console
//
#define TEXT_WIDTH 80

//
//
int
main (int argc, const char **argv)
{
  //
  // setup command line options
  //

  int filter_width;
  int beam_width;
  string data_file_name;
  string output_file_name;
  unordered_map<string, pair<double, double>> stock;

  po::options_description options ("Available options");
  options.add_options ()
      (OP_HELP "," OPS_HELP, "Print this help message")
      (OP_FILTER_WIDTH "," OPS_FILTER_WIDTH,
	  po::value<int>(&filter_width)->default_value(OPD_FILTER_WIDTH),
	  "The filter width of the beam search algorithm")
      (OP_BEAM_WIDTH "," OPS_BEAM_WIDTH,
	  po::value<int>(&beam_width)->default_value(OPD_BEAM_WIDTH),
	  "The beam width of the beam search algorithm")
      (OP_DATA "," OPS_DATA, po::value<string> (&data_file_name),
	  "The *.dat name of the file containing the input pieces information")
      (OP_OUTPUT "," OPS_OUTPUT, po::value<string> (&output_file_name),
	  "The *.tex name of the file where the resulting packing will be drawn")
      (OP_VERBOSE "," OPS_VERBOSE, "Print verbose messages")
      (OP_BINS, po::value<vector<string>>(),
	  "The length and width of the stock bins. If there are two strings "
	  "'<L> <W>' they are considered to be numeric values, and then the "
	  "homogeneous beam search algorithm will be used using stock bins "
	  "with length L and width W. If there are n > 2 strings, then they "
	  "are considered to be of the form '<N_1> <L_1> <W_1> ...', and then "
	  "the heterogeneous beam search algorithm will be used using n stock "
	  "bins. The ith stock bin will have name N_i, length L_i, and width "
	  "W_i.");

  po::positional_options_description p_options;
  p_options.add (OP_BINS, -1);

  //
  // process options
  //

  try
    {
      //
      // error lambda
      //

      auto error = [&](const string &msg)
	{
	  cout << msg << endl;
	  cout << options << endl;
	  exit (EXIT_SUCCESS);
	};


      //
      // reading options
      //

      po::variables_map vm;
      po::store (
	  po::command_line_parser (argc, argv).options (options).positional (
	      p_options).run (),
	  vm);
      po::notify (vm);

      // help option prints options documentation
      //
      if (vm.count (OP_HELP))
	{
	  cout << options << endl;
	  exit (EXIT_SUCCESS);
	}


      //
      // check data option (required, string should be path pointing to a file)
      //

      if (!vm.count (OP_DATA))
	{
	  error ("missing required option --" OP_DATA);
	}

      if (!fs::exists(data_file_name) || !fs::is_regular(data_file_name))
	{
	  error ("option --" OP_DATA
		 " should point to an existing regular file");
	}


      //
      // check data option (optional, string should be path pointing to a file)
      //

      if (vm.count (OP_OUTPUT))
	{
	  if (fs::native (output_file_name))
	    {
	      error ("option --" OP_OUTPUT " should be a valid file name");
	    }
	}


      //
      // check bins stock specification (required, correct number of items)
      //

      // exist in command line?
      //
      if (!vm.count(OP_BINS))
	{
	  error ("missing required option " OP_BINS);
	}

      const std::vector<string> &bins = vm[OP_BINS].as<vector<string>> ();

      // has at least two items?
      //
      if (bins.size() < 2)
	{
	  error ("the number of bin parameters is not correct (n < 2)");
	}

      // has the correct number of items?
      //
      if (bins.size() > 2 && bins.size() % 3 != 0)
	{
	  error ("the number of bin parameters is not correct (n % 3 != 0)");
	}


      //
      // executing beam search
      //

      if (bins.size () == 2)
	{
	  //
	  // homogeneous case
	  //
	  // Stock bins of one type. Only length and width are needed.
	  //

	  double length = boost::lexical_cast<double> (bins[0]);
	  double width = boost::lexical_cast<double> (bins[1]);

	  if (vm.count (OP_VERBOSE))
	    {
	      cout << "calling homogeneous beam search:" << endl;

	      cout << left << setw(20) << "instance: ";
	      cout << "\"" << data_file_name << "\" " << endl;

	      cout << left << setw(20) << "stock bins length:";
	      cout << width << endl;

	      cout << left << setw(20) << "stock bins width:";
	      cout << length << endl << endl;
	    }

	  result &bs_result = beam_search (data_file_name, length, width);

	  //
	  // printing results to console
	  //

	  if (vm.count(OP_VERBOSE))
	    {
	      cout << "results:" << endl;

	      cout << left << setw(30) << "number of bins:";
	      cout << bs_result.bins << endl;

	      cout << left << setw(30) << "number of Bins (fractional):";
	      cout << bs_result.frac_bins << endl;

	      cout << left << setw(30) << "Utilization (%):";
	      cout << bs_result.utilization << endl;

	      cout << left << setw(30) << "Running time (seconds):";
	      cout << bs_result.runtime << endl;
	    }
	  else
	    {
	      streamsize p = cout.precision();
	      cout.precision(5);

	      cout << left << setw(15) << fs::path(data_file_name).filename().string();
	      cout << left << setw(10) << bs_result.bins;
	      cout << left << setw(10) << bs_result.frac_bins;
	      cout << left << setw(10) << bs_result.utilization;
	      cout << left << setw(10) << bs_result.runtime;
	      cout << endl;

	      cout.precision(p);
	    }

	  //
	  // printing results to *.tex
	  //

	  if (vm.count (OP_OUTPUT))
	    {
	      print_solution (data_file_name, output_file_name,
			      bs_result.runtime, bs_result.solution);
	    }
	}
      else
	{
	  //
	  // heterogeneous case
	  //
	  // Stock bins of several types. For each type we need name, length,
	  // and width.
	  //

	  // constructing stock specification map
	  //
	  for (std::vector<string>::const_iterator it = bins.begin ();
	      it != bins.end ();)
	    {
	      const string &name = *(it++);
	      if (stock.count (name) > 0)
		{
		  cout << "repeated bin name '" << name << "'" << endl;
		  cout << options << endl;
		  exit (EXIT_SUCCESS);
		}

	      double length = boost::lexical_cast<double> (*(it++));
	      double width = boost::lexical_cast<double> (*(it++));

	      stock[name] = std::make_pair (length, width);
	    }

	  if (vm.count (OP_VERBOSE))
	    {
	      cout << "calling heterogeneous beam search:" << endl;

	      cout << left << setw(12) << "instance: ";
	      cout << "\"" << data_file_name << "\" " << endl;

	      cout << "stock bins:" << endl;
	      for_each (stock.begin (), stock.end (), [](auto &el)
		{
		  cout << right << setw(19) << "label: "<< left << setw(10)
		      << el.first;
		  cout << "length: " << left << setw(15) << el.second.first;
		  cout << "width: " << left << setw(15) << el.second.second
		      << endl;
		});
	    }
	}
    }
  catch (std::exception& e)
    {
      cout << e.what () << endl;
    }

  return EXIT_SUCCESS;
}
