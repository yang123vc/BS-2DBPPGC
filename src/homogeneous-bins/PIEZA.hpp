/*
 * PIEZA.hpp
 *
 *  Class PIEZA from classes_BPGC.hpp (BS-4-2DBPPGC, commit: a1cab62) file,
 *  created by Marta Cabo Nodar on 16/10/14.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#ifndef HOMOGENEOUS_BS_PIEZA_HPP_
#define HOMOGENEOUS_BS_PIEZA_HPP_

#include "PUNTO.hpp"
#include "EDGES.hpp"
#include "help_constants.hpp"

#include <iostream>
#include <vector>
using namespace std;


namespace homogeneous_bs
{

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
    vector<PUNTO> puntos_angulo_inicial;

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
    PUNTO coord;

    // True si la pieza es simétrica (no hay necesidad de hacer una reflexión),
    // false si no lo es. Inicializa a False
    //
    bool mirror;

    // guarda el ángulo que se utilizó en la rotación
    //
    double angulo_usado;

  public:

    void
    setID (int id)
    {
      this->ID = id;
    }
    int
    getID ()
    {
      return this->ID;
    }

    // asigna el id del bin en el que está la pieza
    //
    void
    setbin (int bin_id)
    {
      this->bin = bin_id;
    }

    // Obtiene el ID del bin en el que está la pieza
    //
    int
    getBIN ()
    {
      return this->bin;
    }

    // añade los puntos de la pieza
    //
    void
    add_point (PUNTO p)
    {
      this->puntos_angulo_inicial.push_back (p);
    }

    // Gets the number of vertices of the piece.
    //
    int
    get_noVert ()
    {
      return no_vertices;
    }

    void
    setCoord (PUNTO p)
    {
      this->coord = p;
    }
    PUNTO
    getCoord ()
    {
      return this->coord;
    }

    double
    getl ()
    {
      return this->largo;
    }
    double
    getw ()
    {
      return this->ancho;
    }
    double
    getArea ()
    {
      return this->area;
    }
    double
    get_angulo_usado ()
    {
      return this->angulo_usado;
    }
    vector<double>
    get_angles ()
    {
      return this->angulos_pieza;
    }
    vector<EDGES> *
    getEdges ()
    {
      return (&aristas);
    }

    void
    ini_edges ();

    // Borra todos los puntos de la pieza para poder iniciar otra.
    //
    void
    clear_points ()
    {
      this->puntos_angulo_inicial.clear ();
    }

    // Inicializa una pieza
    //
    void
    initialize_piece ();

    vector<PUNTO> *
    obtener_puntos ()
    {
      return &puntos_angulo_usado;
    }
    void
    set_ptos_diag_rot ()
    {
      this->puntos_diagonal_base = this->puntos_angulo_usado;
    }
    vector<PUNTO>
    get_ptos_diag_rot ()
    {
      return this->puntos_diagonal_base;
    }

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
    get_mirror ()
    {
      return this->mirror;
    }

    // Realiza la reflexión. Devuelve false si el mirror no cambia la
    // orientación de la pieza.
    //
    bool
    set_mirror (bool v);

    // Checa si la pieza entra en el rectángulo del bin.
    //
    bool
    Fits_Bin (double L, double W)
    {
      if (largo < L + HBS_TOL && ancho < W + HBS_TOL)
	return true;
      else
	return false;
    }

    // Set the longest edge as base.
    //
    void
    setbase (vector<EDGES> aristas);
    double
    getbase ()
    {
      return this->base;
    }

    void
    set_placed (int b)
    {
      if (b < 0)
	placed = false;
      else
	placed = true;
    }
    bool
    is_placed ()
    {
      return this->placed;
    }
  };

} /* namespace homogeneous_bs */

#endif /* HOMOGENEOUS_BS_PIEZA_HPP_ */
