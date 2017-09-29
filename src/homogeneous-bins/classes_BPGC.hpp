//
//  classes_BPGC.h
//  NFP
//
//  Created by Marta Cabo Nodar on 16/10/14.
//  Copyright (c) 2014 Marta Cabo. All rights reserved.
//
#ifndef CLASSES_BPGC_HPP_
#define CLASSES_BPGC_HPP_

//##############################################
//########## DEFINICION DE CLASES ##############
//##########     Y ESTRUCTURAS    ##############
//##############################################

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // supress warnings in MVS
#endif

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <math.h>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <string.h>
using namespace std;

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

// To compare in the global eval
//
class GE_COMP
{
public:
  double fractional_n_bins;
  double fractional_util;
  double prop_used_current_bin;
};

class PUNTO
{
public:
  double coordx;
  double coordy;
};

class EDGES
{
public:
  PUNTO ini;
  PUNTO fin;
  double mod; //Stores the lenght of the edge.
  void
  set_mod ();
};

class NUMERO
{
public:
  int parte_entera;
  int decimal_1; // digito del 0 al 9
  int decimal_2; // digito del 0 al 9
};

class PIEZA
{
private:
  // ID de la pieza
  //
  int ID;

  // numero de bin al que pertenece
  //
  int bin;

  // área de la pieza
  //
  double area;

  // True if piece is placed in a bin, false if not.
  //
  bool placed;

  // puntos del polígono inicial
  //
  std::vector<PUNTO> puntos_angulo_inicial;

  // puntos del polígono rotado. Van cambiando a medida que hacemos las
  // diferentes rotaciones
  //
  vector<PUNTO> puntos_angulo_usado;

  // puntos del polígono para que la diagonal más larga (puede ser un lado)
  // esté en la base del bin.
  //
  vector<PUNTO> puntos_diagonal_base;

  // aristas de la pieza
  //
  vector<EDGES> aristas;

  // Contiene los ángulos de la pieza en sentido antihorario
  //
  vector<double> angulos_pieza;

  // lenght of the longest edge of the piece.
  //
  double base;

  // ancho de la pieza
  //
  double ancho;

  // largo de la pieza
  //
  double largo;

  // numero de vertices de la pieza
  //
  int no_vertices;

  // Coordenadas del punto de referencia de la pieza. Inicialmente será el
  // (0,0) en todas, luego depende de la posición de la pieza en el bin.
  //
  PUNTO Coord;

  // True si la pieza es simétrica (no hay necesidad de hacer una reflexión),
  // false si no lo es. Inicializa a False
  //
  bool mirror;

  // guarda el ángulo que se utilizó en la rotación
  //
  double angulo_usado;

public:

  void
  setID (int id);
  int
  getID ();

  // asigna el id del bin en el que está la pieza
  //
  void
  setbin (int i);
  // Obtiene el ID del bin en el que está la pieza
  //
  int
  getBIN ();

  // añade los puntos de la pieza
  //
  void
  add_point (PUNTO p);
  // Gets the number of vertices of the piece.
  //
  int
  get_noVert ();

  void
  setCoord (PUNTO p);
  PUNTO
  getCoord ();

  double
  getl ();
  double
  getw ();
  double
  getArea ();
  double
  get_angulo_usado ();
  vector<double>
  get_angles ();

  vector<EDGES> *
  getEdges ();
  void
  ini_edges ();

  // Borra todos los puntos de la pieza para poder iniciar otra.
  //
  void
  clear_points ();

  // Inicializa una pieza
  //
  void
  initialize_piece ();

  vector<PUNTO> *
  obtener_puntos ();
  void
  set_ptos_diag_rot ();
  vector<PUNTO>
  get_ptos_diag_rot ();

  // devuelve la rotación (devuelve el vector de vértices rotados de la pieza)
  // y false si coinciden con los originales (rotación no hace nada)
  //
  bool
  obtener_rotacion (double angulo_a_rotar);

  // This function translate the piece (x,y) units.
  //
  void
  translate (double x, double y);

  void
  write_coords ();

  // Obiene el valor de mirror.
  //
  bool
  get_mirror ();
  bool

  // Realiza la reflexión. Devuelve false si el mirror no cambia la orientación
  // de la pieza.
  //
  set_mirror (bool v);
  bool

  // Checa si la pieza entra en el rectángulo del bin.
  //
  Fits_Bin (double L, double W);
  void

  // Set the longest edge as base.
  //
  setbase (vector<EDGES> aristas);
  double
  getbase ();

  void
  set_placed (int b);
  bool
  is_placed ();
};

class IRR_BIN
{
private:
  int ID; //Independent identifier for the irregular bin
  int binID; //Bin ID to which the irregular bin is associated.
  double area_ib; //Total area of the irregular bin.
  double waste_ib; //free area
  double prop_used; //proportion of the bin used.
  vector<PUNTO> ib_ptos; //vertices of the bin in clockwise order.
  vector<double> ib_angles;
  vector<PIEZA*> ib_pzas; //Pieces that are included in the irr_bin
  vector<EDGES> ib_GC; //Guillotine cuts inside the irregular bin
public:
  void
  set_ID (int i);
  int
  getID ();
  void
  setBin (int b);
  void
  setArea ();
  double
  getArea ();
  int
  getBin (); //Returns the value of binID;
  void
  set_prop_used ();
  double
  get_prop_used ();
  void
  set_waste (PIEZA &p);
  void
  empty_irrbin ();
  double
  get_waste ();
  void
  add_piece (PIEZA &p);
  void
  add_points (PUNTO &pto);
  void
  add_GC (EDGES &e);
  vector<double>
  get_angles ();
  vector<PUNTO> *
  get_ptos ();
  vector<PIEZA*> *
  get_pzas ();
  vector<EDGES> *
  get_ibGC ();
};

class BIN
{
private:
  int ID;
  int num_piezas;
  double L; //largo del bin. Se asume L>W.
  double W; //Ancho del bin
  double waste; // area libre
  double prop_utilizada; //proporción del bin utilizada
  bool bin_open; //True if there is the possibility of placing more items in this bin. False otherwise.
  int num_sect; //number of sections in which the bin is being divided (0 = no divisions)
  vector<PIEZA*> piezas_incluidas; //Puntero a las piezas incluidas en el bin.
  vector<EDGES> GC;
  vector<IRR_BIN> section;
public:
  void
  initialize_bin (double stock_length, double stock_width, int i);
  void
  setID (int i); //crea el ID del bin
  int
  getID (); //recupera el ID del bin
  void
  setDim (const string &name); //Asigna largo y ancho del bin
  double
  getL ();
  double
  getW ();
  double
  get_waste ();
  void
  setOpen (bool op);
  bool
  getOpen ();
  double
  getL_used (); //recupera la longitud utilizada
  double
  getW_used (); //recupera el ancho utilizado
  void
  setWaste (PIEZA &p); //calcula el area libre
  void
  setPropUtil (); //Calcula la proporción utilizada
  double
  getPropUtil ();
  int
  getNumPiezas ();
  void
  include_piece (PIEZA &p);
  void
  add_GC (EDGES e);
  vector<EDGES> *
  getGC ();
  vector<PIEZA*> *
  getPI ();
  void
  empty_bin ();
  void
  add_IB (IRR_BIN &ib);
  int
  getNumSect ();
  IRR_BIN
  get_ib (int i);
  void
  update_section (IRR_BIN ib); //Updates the pieces of section(ib) already  in  the bin.
  void
  update_ptos_sect (IRR_BIN ib); //update the points of sectino ib already in the bin.
  void
  add_piece_SectToBin (IRR_BIN ib); //Adds a piece from a given section (ib) to the bin
  void
  FixUtil (double util);
};

// NODOS
// de aquí sólo se utiliza:
// NODE *predecessor;
// double global_eval;
// vector<int> ID_pzas_disp;
//
class NODE
{
private:
  int ID;
  int level;
  NODE *predecessor;
  int num_piezas;
  double global_eval;
  double L; //largo del bin. Se asume L>W.
  double W; //Ancho del bin
  double waste; // area libre
  double prop_utilizada; //proporción del bin utilizada
  bool bin_open; //True if there is the possibility of placing more items in this bin. False otherwise.
  int num_sect; //number of sections in which the bin is being divided (0 = no divisions)
  PIEZA piezas_incluidas[100]; //piezas incluidas en el bin.
  vector<EDGES> GC;
  vector<IRR_BIN> section;
  vector<int> ID_pzas_disp; //Piezas disponibles para colocar en ese nodo.

public:
  void
  initialize_node (double stock_length, double stock_width, int ID);
  void
  setID (int i); //crea el ID del bin
  int
  getID (); //recupera el ID del bin
  void
  setDim (const string &name); //Asigna largo y ancho del bin
  double
  getL ();
  double
  getW ();
  double
  get_waste ();
  void
  setOpen (bool op);
  bool
  getOpen ();
  double
  getL_used (); //recupera la longitud utilizada
  double
  getW_used (); //recupera el ancho utilizado
  void
  setWaste (PIEZA &p); //calcula el area libre
  void
  setPropUtil (); //Calcula la proporción utilizada
  double
  getPropUtil ();
  int
  getNumPiezas ();
  void
  include_piece (PIEZA p); //Incluye una copia de la pieza, pues la misma pieza se va a incluir en varios nodos.
  void
  add_GC (EDGES e);
  vector<EDGES> *
  getGC ();
  vector<PIEZA*>
  getPI ();
  void
  empty_bin ();
  void
  add_IB (IRR_BIN &ib);
  int
  getNumSect ();
  IRR_BIN
  get_ib (int i);
  void
  update_section (IRR_BIN &ib); //Updates the pieces of section(ib) already  in  the bin.
  void
  update_ptos_sect (IRR_BIN &ib); //update the points of sectino ib already in the bin.
  void
  add_piece_SectToBin (IRR_BIN &ib); //Adds a piece from a given section (ib) to the bin
  //=========================
  //Functions related to NODE as a node in a tree, not as a bin object
  void
  set_pred (NODE &pred);
  void
  set_ID_pzas_disp (vector<PIEZA> &pz);
  void
  update_pzas_disp (int ID);
  vector<int>
  get_IDdisp ();
  NODE *
  get_Pred ();
  void
  set_level (int i);
  int
  get_level ();
  void
  set_globaleval (double of);
  double
  get_globaleval ();

  // parte del refinement del último bin
  // (porque no sabemos si el corte es horizontal o vertical)?
  //
  void
  FixUtil (double d);
  void
  CopyPiecesInSect ();
};

class TREE
{
private:
  list<NODE> BS_tree;
  int alpha;
  int beta;
public:
  void
  create_child (double stock_length, double stock_width, int NoChild, int Rots,
		NODE &current_node, vector<PIEZA> &pzas);
  void
  fill_node (NODE &c_node, vector<PIEZA> &pza);
  void
  del_node (list<NODE>::iterator &node);
  bool
  local_eval (vector<NODE> &c, NODE &c_node);	//
  void
  global_eval (double stock_length, double stock_width, vector<PIEZA> &p);
  void
  build_solution (double stock_length, double stock_width, vector<PIEZA> &p);
  list<NODE>
  get_tree ();
};

// read pieces from file
//
void
read_pieces (const string &data_file_name, vector<PIEZA> &pieces);

void
print_solution (const string &data_file_name, const string &output_file_name,
		double runtime, TREE &bs_sol);

void
dibujar_nodes (const string &data_file_name, const string &output_file_name,
	       vector<NODE> &node, double runtime, double L, double W,
	       int escalado);

extern int
argmax_mod (vector<EDGES> &a);
extern bool
equal_double (double a, double b, double prec);
extern double
distancia (PUNTO p1, PUNTO p2);
extern bool
equal_pto (PUNTO p1, PUNTO p2);
extern double
calcular_area_exacta (vector<PUNTO> &poligono);
extern int
Position (PUNTO A, PUNTO B, PUNTO C);
extern vector<double>
calculateInnerAngles (vector<EDGES> &ar);

#endif /* CLASSES_BPGC_HPP_ */
