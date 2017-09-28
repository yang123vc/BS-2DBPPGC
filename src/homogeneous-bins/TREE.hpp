/*
 * TREE.hpp
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BINS_TREE_HPP_
#define HOMOGENEOUS_BINS_TREE_HPP_

#include "NODE.hpp"

#include <list>
#include <vector>
using namespace std;

namespace homogeneous_bs
{

  class TREE
  {
  private:

    list<NODE> BS_tree;
    int alpha;
    int beta;
    double
    Local_of (NODE &node);

  public:
    void
    create_child (double stock_length, double stock_width, int NoChild,
		  int Rots, NODE &current_node, vector<PIEZA> &pzas);
    void
    fill_node (NODE &c_node, vector<PIEZA> &pza);
    inline void
    del_node (list<NODE>::iterator &node)
    {
      BS_tree.erase (nodo);
    }
    bool
    local_eval (vector<NODE> &c, NODE &c_node);	//
    void
    global_eval (double stock_length, double stock_width, vector<PIEZA> &p);
    void
    build_solution (double stock_length, double stock_width, vector<PIEZA> &p);
    list<NODE>
    get_tree ();
  };

} /* namespace homogeneous_bs */

#endif /* HOMOGENEOUS_BINS_TREE_HPP_ */
