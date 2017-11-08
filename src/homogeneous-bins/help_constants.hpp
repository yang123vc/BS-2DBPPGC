/*
 * constants.hpp
 *
 *  Created on: Sep 30, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BS_HELP_CONSTANTS_HPP_
#define HOMOGENEOUS_BS_HELP_CONSTANTS_HPP_

#define HBS_GRANDE 999999
#define HBS_PI 3.14159265358979323846

// tolerancia para evitar errores numéricos
//
#define HBS_TOL  0.000001

// 0.005 para albano // 0.00001 para dados_t2
//
#define HBS_TOL2 0.0001

// umbral para definir angulos rectos [87.5, 92.5]
//
#define HBS_ALPHA 2.5

// This is the acceptance threshold for a good match. If both edges of pieces
// match in length in more than 50% we accept the match. (This will be
// reviewed)
//
#define HBS_THRES 0.5

// This is the acceptance threshold for placing a piece in the candidate list.
// We have different thresholds, because the final acceptance criterion is
// based in convex hull utilization, and maybe by matching a "not so good" edge
// gives better utilization. In any case it will always try the edge with the
// max matching distance, so wer are only allowing for more tests to be made.
//
#define HBS_THRES2 0.8

// This value we will have to explore as I don't have a clue on how much to
// slide a piece along other piece...
//
#define slide_ep 10

// We will try with 0.2, 0.1, 0.05 y 0.01
//
#define HBS_PARAM_LAST_BIN 0.05


#endif /* HOMOGENEOUS_BINS_HELP_CONSTANTS_HPP_ */
