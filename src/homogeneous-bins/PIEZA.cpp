/*
 * PIEZA.cpp
 *
 *  See helpers.hpp for contents description.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#include "PIEZA.hpp"
#include "helpers.hpp"

namespace homogeneous_bs
{

  void
  PIEZA::ini_edges ()
  {
    aristas.clear ();
    for (int i = 0; i < puntos_angulo_usado.size (); i++)
      {
	int j = i + 1;
	if (j == puntos_angulo_usado.size ())
	  j = 0;
	EDGES e;
	e.ini = puntos_angulo_usado[i];
	e.fin = puntos_angulo_usado[j];
	e.set_mod ();
	aristas.push_back (e);
      }
  }

  // Funciones asociadas a la clase pieza.
  //
  void
  PIEZA::initialize_piece ()
  {
    puntos_angulo_usado = puntos_angulo_inicial;
    bin = -1; //La pieza no ha sido asignada a ningun bin
    set_placed (bin);
    area = calcular_area_exacta (puntos_angulo_inicial);
    double maxX = -GRANDE, minX = GRANDE, maxY = -GRANDE, minY = GRANDE;
    //Calcula las coordenadas del menor rectángulo que contiene a la pieza
    for (int i = 0; i < puntos_angulo_usado.size (); i++)
      {
	if (puntos_angulo_usado[i].coordx > maxX)
	  maxX = puntos_angulo_usado[i].coordx;
	if (puntos_angulo_usado[i].coordx < minX)
	  minX = puntos_angulo_usado[i].coordx;
	if (puntos_angulo_usado[i].coordy > maxY)
	  maxY = puntos_angulo_usado[i].coordy;
	if (puntos_angulo_usado[i].coordy < minY)
	  minY = puntos_angulo_usado[i].coordy;
      }
    //===================================================================
    // Traslada los puntos del polígono, de modo que esté en el primer
    // cuadrante, así el punto de referencia siempre corresponde al vértice
    // inferior izqdo del rectángulo que lo contiene.
    for (int i = 0; i < puntos_angulo_inicial.size (); i++)
      {
	puntos_angulo_inicial[i].coordx -= minX;
	puntos_angulo_inicial[i].coordy -= minY;
      }
    Coord.coordx = 0.0;
    Coord.coordy = 0.0;

    // Calcula las aristas de las piezas como vectores dando el pto inicial y
    // el final. Las guarda en el vector aristas de la pieza en sentido
    // antihorario de este modo la pieza se encuentra a la izqda de la arista.
    aristas.clear ();
    for (int i = 0; i < puntos_angulo_inicial.size (); i++)
      {
	EDGES e_aux;
	e_aux.ini = puntos_angulo_inicial[i];
	if (i < puntos_angulo_inicial.size () - 1)
	  {
	    e_aux.fin = puntos_angulo_inicial[i + 1];
	  }
	else
	  e_aux.fin = puntos_angulo_inicial[0];
	e_aux.set_mod ();
	aristas.push_back (e_aux);
      }
    mirror = false;
    angulo_usado = 0;
    ancho = maxY - minY;
    largo = maxX - minX;
    //Calcula los ángulos internos de la pieza.
    //=========================================
    angulos_pieza = calculateInnerAngles (aristas);
    no_vertices = puntos_angulo_usado.size ();
    setbase (aristas); //define la base de la pieza como aquella con el lado más largo.
  }

  // Obtiene una rotación de angulo_a_rotar grados con respecto a la posición
  // inicial de la pieza.
  //
  bool
  PIEZA::obtener_rotacion (double angulo_a_rotar)
  {
    // CALCULAMOS COORDENADAS DE LA PIEZA EN LO DIFERENTES ANGULOS:
    double angulo_aux = 2 * PI * angulo_a_rotar / 360;	//Convertir a rads.
    double xmin = GRANDE, xmax = -GRANDE, ymin = GRANDE, ymax = -GRANDE;
    PUNTO p_aux;
    p_aux.coordx = -1;
    p_aux.coordy = -1;
    unsigned long n_p = puntos_angulo_inicial.size ();
    vector<PUNTO> v_anterior = puntos_angulo_usado;
    puntos_angulo_usado.assign (n_p, p_aux);
    int pos_min_X = -1;
    for (int i = 0; i < n_p; i++)//Bucle para cada uno de los puntos de la pieza.
      {
	//Escribe el punto en coordenadas polares:[0, 2PI]
	double modulo = sqrt (
	    puntos_angulo_inicial[i].coordx * puntos_angulo_inicial[i].coordx
		+ puntos_angulo_inicial[i].coordy
		    * puntos_angulo_inicial[i].coordy);
	double tita = PI / 2; // SI x=0 :: y>0
	if (modulo < TOL && modulo > -TOL)
	  tita = 0;
	else
	  {
	    if (puntos_angulo_inicial[i].coordx < TOL
		&& puntos_angulo_inicial[i].coordx > -TOL
		&& puntos_angulo_inicial[i].coordy < -TOL) // SI x=0 :: y<0
	      {
		tita = 3 * PI / 2;
	      }
	    if (puntos_angulo_inicial[i].coordx > TOL
		&& puntos_angulo_inicial[i].coordy >= 0) // SI x>0 :: y>=0
	      {
		tita = atan (
		    puntos_angulo_inicial[i].coordy
			/ puntos_angulo_inicial[i].coordx);
	      }
	    if (puntos_angulo_inicial[i].coordx > TOL
		&& puntos_angulo_inicial[i].coordy < -TOL) // SI x>0 :: y<0
	      {
		tita = atan (
		    puntos_angulo_inicial[i].coordy
			/ puntos_angulo_inicial[i].coordx) + 2 * PI;
	      }
	    if (puntos_angulo_inicial[i].coordx < -TOL) // SI x<0
	      {
		tita = atan (
		    puntos_angulo_inicial[i].coordy
			/ puntos_angulo_inicial[i].coordx) + PI;
	      }
	  }

	// Punto pp es el punto rotado.Lo convertimos de coordenadas polares a
	// coordenadas cartesianas.
	PUNTO pp;
	pp.coordx = modulo * cos (angulo_aux + tita);
	pp.coordy = modulo * sin (angulo_aux + tita);
	puntos_angulo_usado[i] = pp;

	if (xmin > pp.coordx)
	  {
	    xmin = pp.coordx;
	    pos_min_X = i;
	  }
	if (ymin > pp.coordy)
	  ymin = pp.coordy;
	if (xmax < pp.coordx)
	  xmax = pp.coordx;
	if (ymax < pp.coordy)
	  ymax = pp.coordy;
      }

    // Nuevas dimensiones:
    ancho = ymax - ymin;
    largo = xmax - xmin;

    // GUARDAMOS CORRECCIÓN DELTAS (no creo que lo necesitemos.
    //PUNTO correccion;
    //correccion.coordx=xmin;
    //correccion.coordy=ymin;

    // MOVEMOS LAS COORDENADAS PARA QUE LA PIEZA SE ENCUENTRE EN EL 1er CUADRANTE
    for (int i = 0; i < n_p; i++)
      {
	puntos_angulo_usado[i].coordx -= xmin;
	puntos_angulo_usado[i].coordy -= ymin;
      }
    // COMENZAMOS A ESCRIBIR CON EL VERTICE DE MENOR COORDENADA X:
    //============================================================
    vector<PUNTO> pppp;
    for (int ii = pos_min_X; ii < puntos_angulo_usado.size (); ii++)
      {
	pppp.push_back (puntos_angulo_usado[ii]);
      }
    for (int ii = 0; ii < pos_min_X; ii++)
      {
	pppp.push_back (puntos_angulo_usado[ii]);
      }
    //===========================================================

    // Recalculamos aristas y ángulos.
    angulo_usado = angulo_a_rotar;
    ini_edges ();
    angulos_pieza = calculateInnerAngles (aristas);
    // COMPROBAMOS SIMETRIA CON ANTERIOR:
    bool simetria = true;
    for (int i = 0; i < n_p; i++)
      {
	if (pppp[i].coordx < v_anterior[i].coordx - TOL
	    || pppp[i].coordx > v_anterior[i].coordx + TOL
	    || pppp[i].coordy < v_anterior[i].coordy - TOL
	    || pppp[i].coordy > v_anterior[i].coordy + TOL)
	  {
	    simetria = false;
	    break;
	  }
      }
    return simetria;
  }

  void
  PIEZA::translate (double x, double y)
  {
    for (int i = 0; i < no_vertices; i++)
      {
	puntos_angulo_usado[i].coordx += x;
	puntos_angulo_usado[i].coordy += y;
      }
    Coord.coordx += x;
    Coord.coordy += y;
    ini_edges ();
  }

  void
  PIEZA::write_coords ()
  {
    printf ("Pieza[%d]:\n", getID ());
    for (int i = 0; i < no_vertices; i++)
      {
	printf ("\t Punto[%d]: ( %.2f , %.2f )\n", i,
		puntos_angulo_usado[i].coordx, puntos_angulo_usado[i].coordy);
      }
    printf ("\n");
  }

  bool
  PIEZA::set_mirror (bool v)
  {
    if (mirror == v)
      return true;
    mirror = v;
    angulo_usado = 0;

    // CALCULAMOS COORDENADAS DE LA PIEZA EN LO DIFERENTES ANGULOS:

    PUNTO p_aux;
    p_aux.coordx = -1;
    p_aux.coordy = -1;
    int n_p = puntos_angulo_inicial.size ();
    vector<PUNTO> v_anterior = puntos_angulo_inicial;
    puntos_angulo_usado.assign (n_p, p_aux);
    int pos_min_X = -1;

    double xmin = GRANDE, xmax = -GRANDE, ymin = GRANDE, ymax = -GRANDE;
    for (int i = 0; i < n_p; i++)
      {
	PUNTO pp;
	pp.coordx = (-puntos_angulo_inicial[i].coordx);
	pp.coordy = puntos_angulo_inicial[i].coordy;
	puntos_angulo_usado[i] = pp;

	if (xmin >= pp.coordx)
	  xmin = pp.coordx;
	if (ymin > pp.coordy)
	  ymin = pp.coordy;
	if (xmax < pp.coordx)
	  xmax = pp.coordx;
	if (ymax < pp.coordy)
	  ymax = pp.coordy;
      }

    reverse (puntos_angulo_usado.begin (), puntos_angulo_usado.end ());

    // Nuevas dimensiones:
    //
    ancho = ymax - ymin;
    largo = xmax - xmin;

    // MOVEMOS LAS COORDENADAS PARA QUE EL PUNTO DE REFERENCIA SEA EL (0,0)
    //
    for (int i = 0; i < n_p; i++)
      {
	puntos_angulo_usado[i].coordx -= xmin;
	puntos_angulo_usado[i].coordy -= ymin;
      }
    puntos_angulo_inicial = puntos_angulo_usado; //(?) Por qué no te quieres quedar con las coordeandas originales?

    // COMENZAMOS A ESCRIBIR CON EL VERTICE DE MENOR COORDENADA X:
    //============================================================
    //Buscamos la posición del punto con menor X (y en caso de empate, menor Y)
    xmin = GRANDE, xmax = -GRANDE, ymin = GRANDE, ymax = -GRANDE;
    for (int i = 0; i < n_p; i++)
      {
	PUNTO pp;
	pp = puntos_angulo_usado[i];
	if (xmin >= pp.coordx)
	  {
	    if (equal_double (xmin, pp.coordx, TOL))
	      {
		if (ymin > pp.coordy)
		  {
		    xmin = pp.coordx;
		    ymin = pp.coordy;
		    pos_min_X = i;
		  }
	      }
	    else
	      {
		xmin = pp.coordx;
		pos_min_X = i;
	      }
	  }
	if (ymin > pp.coordy)
	  ymin = pp.coordy;
	if (xmax < pp.coordx)
	  xmax = pp.coordx;
	if (ymax < pp.coordy)
	  ymax = pp.coordy;
      }

    vector<PUNTO> pppp;
    for (int ii = pos_min_X; ii < puntos_angulo_usado.size (); ii++)
      {
	pppp.push_back (puntos_angulo_usado[ii]);
      }
    for (int ii = 0; ii < pos_min_X; ii++)
      {
	pppp.push_back (puntos_angulo_usado[ii]);
      }

    // Recalculamos aristas y angulos.
    ini_edges ();
    angulos_pieza = calculateInnerAngles (aristas);

    // COMPROBAMOS SIMETRIA CON ANTERIOR:
    bool simetria = true;
    for (int i = 0; i < n_p; i++)
      {
	if (pppp[i].coordx < v_anterior[i].coordx - TOL
	    || pppp[i].coordx > v_anterior[i].coordx + TOL
	    || pppp[i].coordy < v_anterior[i].coordy - TOL
	    || pppp[i].coordy > v_anterior[i].coordy + TOL)
	  {
	    simetria = false;
	    break;
	  }
      }

    return simetria;
  }

  void
  PIEZA::setbase (vector<EDGES> ar)
  {
    double max_edge = -1;
    for (int i = 0; i < ar.size (); i++)
      {
	if (ar[i].mod > max_edge)
	  max_edge = ar[i].mod;
      }
    base = max_edge;
  }

} /* namespace homogeneous_bs */
