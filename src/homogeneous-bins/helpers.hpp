/*
 * helpers.hpp
 *
 *  Constants and global functions from classes_BPGC.hpp (BS-4-2DBPPGC, commit:
 *  a1cab62) file, created by Marta Cabo Nodar on 16/10/14.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BINS_HELPERS_HPP_
#define HOMOGENEOUS_BINS_HELPERS_HPP_

#define GRANDE 999999
#define PI 3.14159265358979323846

// tolerancia para evitar errores numéricos
//
#define TOL  0.000001

// 0.005 para albano // 0.00001 para dados_t2
//
#define TOL2 0.0001

// umbral para definir angulos rectos [87.5, 92.5]
//
#define ALPHA 2.5

// This is the acceptance threshold for a good match. If both edges of pieces
// match in length in more than 50% we accept the match. (This will be
// reviewed)
//
#define THRES 0.5

// This is the acceptance threshold for placing a piece in the candidate list.
// We have different thresholds, because the final acceptance criterion is
// based in convex hull utilization, and maybe by matching a "not so good" edge
// gives better utilization. In any case it will always try the edge with the
// max matching distance, so wer are only allowing for more tests to be made.
//
#define THRES2 0.8

// This value we will have to explore as I don't have a clue on how much to
// slide a piece along other piece...
//
#define slide_ep 10

// We will try with 0.2, 0.1, 0.05 y 0.01
//
#define PARAM_LAST_BIN 0.05

#include <vector>
using namespace std;

#include "IRR_BIN.hpp"
#include "EDGES.hpp"
#include "PUNTO.hpp"
#include "PIEZA.hpp"

namespace homogeneous_bs
{
  vector<double>
  calculateInnerAngles (vector<EDGES> &);

  double
  calcular_area_exacta (vector<PUNTO> &poligono);

  PIEZA
  create_convexhull_in_section (IRR_BIN &sect);

  vector<PUNTO>
  convex_hull (vector<PUNTO> P);

  bool
  equal_double (double a, double b, double prec);

} /* namespace homogeneous_bs */

#endif /* HOMOGENEOUS_BINS_HELPERS_HPP_ */
