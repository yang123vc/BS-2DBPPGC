/*
 * helpers.hpp
 *
 *  Constants and global functions from classes_BPGC.hpp (BS-4-2DBPPGC, commit:
 *  a1cab62) file, created by Marta Cabo Nodar on 16/10/14.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BS_HELPERS_HPP_
#define HOMOGENEOUS_BS_HELPERS_HPP_

#include <list>
#include <vector>
#include <string>
using namespace std;

namespace homogeneous_bs
{
  class PIEZA;
  class NODE;
  class PUNTO;
  class EDGES;
  class IRR_BIN;
  class BIN;
  class TREE;
  class NUMERO;

  //
  // print
  //

  void
  print_solution (const string &data_file_name, const string &output_file_name,
  		double runtime, TREE &bs_sol);

  void
  dibujar_nodes (const string &data_file_name, const string &output_file_name,
  	       vector<NODE> &node, double runtime, double L, double W,
  	       int escalado);

  NUMERO
  redondear_numero_dos_cifras (double num);


  //
  // area
  //

  bool
  orden_area (PIEZA i, PIEZA j);


  //
  // angles
  //

  vector<double>
  calculateInnerAngles (vector<EDGES> &);

  vector<double>
  calculate_rotations_FitNode (NODE &n, PIEZA &p, int num_rot, double epsilon);

  double
  calculate_rotation_match (EDGES &e1, EDGES &e2);

  // Calcula la rotación de una pieza por un ángulo alpha, pero solo guarda las
  // aristas, no rota toda la pieza
  //
  vector<EDGES>
  rotation_piece (PIEZA &p, double alpha);

  // Calcula un vector de posibles rotaciones para que coincida con los lados de
  // un bin.
  //
  vector<double>
  calculate_rotations_FitSection_Mirror (vector<EDGES> &ed_irrbin, PIEZA &p,
					 int num_rot, double epsilon);

  // Calcula un vector de posibles rotaciones para que coincida con los lados de
  // un bin.
  //
  vector<double>
  calculate_rotations_FitBin_Mirror (BIN &b, PIEZA &p, int num_rot,
				     double epsilon);


  //
  // convex hull
  //

  double
  calcular_area_exacta (vector<PUNTO> &poligono);

  PIEZA
  create_convexhull_in_section (IRR_BIN &sect);

  vector<PUNTO>
  convex_hull (vector<PUNTO> P);

  // 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross
  // product. Returns a positive value, if OAB makes a counter-clockwise turn,
  // negative for clockwise turn, and zero if the points are collinear.
  //
  double
  cross (PUNTO &O, PUNTO &A, PUNTO &B);

  double
  convexhull_Utilization (PIEZA P1, PIEZA P2);

  double
  convexhull_Length (PIEZA P1, PIEZA P2);

  double
  convexhull_Height (PIEZA P1, PIEZA P2);

  //
  // basic functions
  //

  void
  read_pieces (const string &data_file_name, vector<PIEZA> &pieces);

  bool
  equal_double (double a, double b, double prec);

  bool
  equal_pto (PUNTO a, PUNTO b);

  bool
  lexicographic (PUNTO P1, PUNTO P2);

  int
  position (PUNTO A, PUNTO B, PUNTO C);

  double
  distancia (PUNTO p1, PUNTO p2);

  int
  argmax_mod (vector<EDGES> &a);


  //
  // move in section
  //

  bool
  edge_of_section (EDGES ed, IRR_BIN ib);

  void
  trans_piece_ini_fin (PIEZA &item2, EDGES e1, EDGES e2);

  void
  trans_piece_fin_ini (PIEZA &item2, EDGES e1, EDGES e2);

  void
  trans_piece_fin_ini (PIEZA &item2, EDGES e1, EDGES e2);

  double
  match_dist (EDGES e1, EDGES e2);

  bool
  Feasible_Slide_InSect (IRR_BIN bin, PIEZA item1, PIEZA &item2, int v1, int v2,
			 double dis);

  void
  Attach (PIEZA item1, PIEZA &item2, int v1, int v2);


  //
  // guillotine cuts
  //

  EDGES
  IntersectBin (EDGES gc, vector<PUNTO> rbin);


  // Función que devuelve el punto de intersección entre dos líneas, si es que
  // existe. (-1,-1) si las líneas son paralelas.
  //
  PUNTO
  IntersectTwoLines (PUNTO ini_l1, PUNTO fin_l1, PUNTO ini_l2, PUNTO fin_l2);

  vector<PUNTO>
  Redefine_IrrBin_withPieces (vector<PUNTO> &rbin, EDGES gc);

  double
  GuillotineCutWaste (PIEZA ch, IRR_BIN current_sect, EDGES &best_gc);

  double
  CalculatePropWasteCut (vector<PUNTO> ib_ptos, EDGES gc, double area_used);


  //
  // construct solution
  //

  bool
  FillBin (vector<PIEZA> &item, IRR_BIN &csect, EDGES &gc, int id);


  //
  // sections in node
  //

  IRR_BIN
  Redefine_NewSection (vector<PUNTO> &rbin, EDGES gc);

  // This function returns a bool that is TRUE if the edges are all inside the
  // section and FALSE if there is any edge outside the section.
  //
  bool
  FitInSect_IniPcFinSec (vector<EDGES> e_pza, vector<PUNTO> ptos_Sec,
			 EDGES esec_match, EDGES epza_match);

  bool
  FitInSect_FinPcIniSec (vector<EDGES> e_pza, vector<PUNTO> ptos_Sec,
			 EDGES esec_match, EDGES epza_match);

  int
  BreakTie (vector<EDGES> e_pza, vector<PUNTO> ptos_sect, EDGES esec,
	    EDGES epza);


  //
  // open bin
  //

  bool
  PieceInSect (PIEZA &piece, IRR_BIN &current_sect);

  bool
  FillBin (vector<PIEZA> &item, IRR_BIN &csect, EDGES &gc, int id,
	   vector<int> ID_disp);

  bool
  Place_in_NewSection (IRR_BIN &current_sect, vector<PIEZA*> &candidates,
		       EDGES &best_gc, int id);

  bool
  NextBestCG_candidates (vector<PIEZA*> &item, IRR_BIN &csect, EDGES &gc);

  void
  OpenBin (BIN &bin, PIEZA &item);


  //
  // candidates
  //

  vector<PIEZA*>
  CreateList (vector<PIEZA> &item, IRR_BIN &sect, int LIST_SIZE, double thres,
	      vector<int> ID_disp);

  int
  pos_disp (vector<PIEZA> &item, vector<int> &ID);

  // Function that places candidates in a bin (section) based on three criteria
  //
  bool
  Place_Candidates (NODE &node, IRR_BIN &sect, vector<PIEZA*> &list,
		    bool &CH_crit, bool &bestGC_crit, bool &NextGC_crit,
		    EDGES &best_gc, int &sec_mod_id);


  //
  // global evaluation
  //

  vector<PIEZA*>
  CreateList (vector<PIEZA> &item, IRR_BIN &sect);


  //
  // match pieces
  //

  double
  SelectBestMatch (IRR_BIN &bin, vector<PIEZA*> list, PIEZA convex_hull,
		   int &best_e1, int &best_e2, double &best_d, int &best_p,
		   int &best_m);


  //
  // irregular bins
  //

  // Esta función crea un elemento de la clase IRR_BIN a partir de otro de la
  // clase NODE básicamente para tener un IRR BIN inicial y trabajar después
  // sólo con IRR BINs.
  //
  IRR_BIN
  ConvertToIRRBIN (NODE &bin);

  // Esta función crea un elemento de la clase IRR_BIN a partir de otro de la
  // clase BIN básicamente para tener un IRR BIN inicial y trabajar después
  // sólo con IRR BINs.
  //
  IRR_BIN
  ConvertToIRRBIN (BIN &bin);


  //
  // last bin
  //

  void
  LastBinRefinementGE (vector<PIEZA> &pzas, BIN &sol);

  void
  LastBinRefinement (list<NODE> &tree);


  //
  // horizontal placement
  //

  double
  ArrangeHorGE (vector<PIEZA> &pzas, BIN &node);

  double
  HorAligMatch (IRR_BIN &bin, vector<PIEZA*> list, PIEZA convex_hull,
		int &best_e1, int &best_e2, double &best_d, int &best_p,
		int &best_m);

  bool
  MoveDownInSect (PIEZA &ch, IRR_BIN &sec, double slide);

  double
  VertGuillCut (IRR_BIN &ib_node, vector<PIEZA*> list, PIEZA convex_hull,
		double node_w, double node_l, double &best_rot, int &best_p,
		int &best_i, EDGES &v_gc);

  double
  ArrangeVert (vector<PIEZA> &pzas, NODE &node);

  double
  ArrangeHor (vector<PIEZA> &pzas, NODE &node);

  // Function that similar to Best Match, places pieces together, this time, the
  // matching criteria is that the total height of the resulting convex hull is
  // as low as possible.
  //
  double
  HorAligMatch (IRR_BIN &bin, vector<PIEZA*> list, PIEZA convex_hull,
		int &best_e1, int &best_e2, double &best_d, int &best_p,
		int &best_m);


  //
  // vertical placement
  //

  double
  ArrangeVertGE (vector<PIEZA> &pzas, BIN &node);

  bool
  MoveLeftInSect (PIEZA &ch, IRR_BIN &sec, double slide);

  // Function that similar to Best Match, places pieces together, this time,
  // the matching criteria is that the total height of the resulting convex hull
  // is as low as possible.
  //
  double
  VertAligMatch (IRR_BIN &bin, vector<PIEZA*> list, PIEZA convex_hull,
		 int &best_e1, int &best_e2, double &best_d, int &best_p,
		 int &best_m);

  double
  HorGuillCut (IRR_BIN &ib_node, vector<PIEZA*> list, PIEZA convex_hull,
	       double node_w, double node_l, double &best_rot, int &best_p,
	       int &best_i, EDGES &h_gc);

} /* namespace homogeneous_bs */

#endif /* HOMOGENEOUS_BS_HELPERS_HPP_ */
