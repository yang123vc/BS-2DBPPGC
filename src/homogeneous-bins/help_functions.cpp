/*
 * helpers.cpp
 *
 *  See helpers.hpp for contents description.
 *
 *  Created on: Sep 27, 2017
 *      Author: Carlos Alegría Galicia
 */

#include "help_functions.hpp"

#include "EDGES.hpp"
#include "PIEZA.hpp"
#include "NODE.hpp"
#include "BIN.hpp"
#include "TREE.hpp"
#include "IRR_BIN.hpp"
#include "NUMERO.hpp"

#include <cstring>

#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

namespace homogeneous_bs
{
  //
  // print
  //

  void
  print_solution (const string &data_file_name, const string &output_file_name,
		  double runtime, TREE &bs_sol)
  {
    list<NODE>::iterator it_child;
    list<NODE> tree;
    tree = bs_sol.get_tree ();
    int last_level;
    it_child = tree.end ();
    it_child--;
    last_level = it_child->get_level ();
    //Identify solution node
    int bestID = -1;
    double bestUtil = HBS_GRANDE;
    while (it_child->get_level () == last_level)
      {
	if (it_child->get_IDdisp ().empty ())
	  {
	    if (bestUtil > it_child->getPropUtil ())
	      {
		bestUtil = it_child->getPropUtil ();
		bestID = it_child->getID ();
	      }
	  }
	it_child--;
      }

    //======================
    it_child = tree.end ();
    it_child--;
    while (it_child->get_level () == last_level)
      {
	vector<NODE> branch_sol;
	if (it_child->get_IDdisp ().empty () && it_child->getID () == bestID)
	  {
	    NODE child;
	    child = *it_child;
	    while (child.get_Pred () != NULL) //While not at FATHER level
	      {
		branch_sol.push_back (child);
		child = *child.get_Pred ();
	      }
	    reverse (branch_sol.begin (), branch_sol.end ());
	    char name[200];
	    sprintf (name, "SOL");

	    dibujar_nodes (data_file_name, output_file_name, branch_sol,
			   runtime, branch_sol[0].getL (),
			   branch_sol[0].getW (), 1);
	  }
	it_child--;
      }
  }

  void
  dibujar_bins (vector<BIN> &bins, char *instance, char *name, double t,
		double L, double W, int escalado)
  {
    char filename[80];
    FILE *p_file;

    char name_inst[100];
    sprintf (name_inst, "_%s.tex", instance);
    strcpy (filename, name);
    strcat (filename, name_inst);

    if ((p_file = fopen (filename, "w")) == NULL) /*  abre el fichero .txt  */
      {
	printf ("Error in file %s\n", filename);
	exit (1);
      }

    char cadena[120];
    sprintf (cadena, "\\documentclass[12pt,a4paper]{report}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{amsmath}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{txfonts}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{graphicx}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage[latin1]{inputenc}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage[spanish]{babel}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{times}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{datetime}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{placeins}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{subfigure}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{supertabular}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{fullpage,graphicx}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{afterpage}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage {color}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage [all] {xy}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{pgf,tikz}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{fit}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary{shapes.geometric}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary[shapes.geometric]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{shapes.geometric,shapes.arrows} ");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{shapes.symbols,positioning}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{matrix,chains,scopes,positioning,fit}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary[shapes.geometric]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgfmodule{shapes}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgfmodule[shapes] ");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary{arrows}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary[arrows]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{arrows}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary[arrows]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{positioning}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary{decorations.pathmorphing}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary[decorations.pathmorphing]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{decorations.pathmorphing}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary[decorations.pathmorphing]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{er}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary[er] ");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\tikzset{point/.default=} ");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\author{Marta Cabo}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\title{SOLUCION INSTANCIA}");
    fprintf (p_file, "%s \n\n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\begin{document} \n");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';
    //	sprintf(cadena,"\\noindent \\noindent Running Time: %.3f secs", t);
    sprintf (
	cadena,
	"\\noindent Instance name: $%s$, \n \n \\noindent Running Time: %.3f secs",
	instance, t);
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';
    sprintf (cadena,
	     "\n \\noindent Date: \\ddmmyydate  \\today  ~(\\currenttime)");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    int fig = 0;

    vector<BIN>::iterator b;
    for (b = bins.begin (); b != bins.end (); b++)
      {
	//---------
	fig++;
	NUMERO nn, nn1, nn2, nn3;

	sprintf (cadena, "\\begin{figure}[ht]");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\centering");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\definecolor{ffqqqq}{rgb}{1,0,0}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\definecolor{zzttqq}{rgb}{0.6,0.2,0}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\definecolor{cqcqcq}{rgb}{0.75,0.75,0.75}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	double sc = 100 / L;
	if (sc > 100 / W)
	  sc = 100 / W;
	sprintf (
	    cadena,
	    "\\begin{tikzpicture}[scale=0.1, line cap=round, line join=round, >=triangle 45, x=%lf cm,y=%lf cm]",
	    sc, sc);
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (L);
	sprintf (cadena, "\\draw[color=black] (0,0) -- (%d.%d%d,0);",
		 nn.parte_entera, nn.decimal_1, nn.decimal_2);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (W);
	sprintf (cadena, "\\draw[color=black] (0,0) -- (0,%d.%d%d);",
		 nn.parte_entera, nn.decimal_1, nn.decimal_2);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (L + 3);
	nn1 = redondear_numero_dos_cifras (W + 3);
	sprintf (cadena, "\\clip(-3,-3) rectangle (%d.%d%d,%d.%d%d);",
		 nn.parte_entera, nn.decimal_1, nn.decimal_2, nn1.parte_entera,
		 nn1.decimal_1, nn1.decimal_2);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (W);
	nn1 = redondear_numero_dos_cifras (L);
	nn2 = redondear_numero_dos_cifras (W);
	sprintf (cadena,
		 "\\draw[color=black] (-2,%d.%d%d) -- (%d.%d%d,%d.%d%d);",
		 nn.parte_entera, nn.decimal_1, nn.decimal_2, nn1.parte_entera,
		 nn1.decimal_1, nn1.decimal_2, nn2.parte_entera, nn2.decimal_1,
		 nn2.decimal_2);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (L);
	nn1 = redondear_numero_dos_cifras (L);
	nn2 = redondear_numero_dos_cifras (W);
	sprintf (cadena,
		 "\\draw[color=black] (%d.%d%d,-2) -- (%d.%d%d,%d.%d%d);",
		 nn.parte_entera, nn.decimal_1, nn.decimal_2, nn1.parte_entera,
		 nn1.decimal_1, nn1.decimal_2, nn2.parte_entera, nn2.decimal_1,
		 nn2.decimal_2);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	vector<PIEZA*> *pb = b->getPI ();

	for (int i = 0; i < b->getNumPiezas (); i++)
	  {
	    char cadena8[1200];
	    sprintf (cadena8, "\%% New Piece");
	    fprintf (p_file, "%s \n", cadena8);
	    cadena8[0] = '\0';

	    //nn=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx+(*pb)[i]->obtener_puntos()->front().coordx);
	    //nn1=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy+(*pb)[i]->obtener_puntos()->front().coordy);
	    nn = redondear_numero_dos_cifras (
		(*pb)[i]->obtener_puntos ()->front ().coordx);
	    nn1 = redondear_numero_dos_cifras (
		(*pb)[i]->obtener_puntos ()->front ().coordy);

	    sprintf (
		cadena8,
		"\\fill[color=zzttqq,fill=zzttqq,fill opacity=0.2] (%d.%d%d,%d.%d%d)",
		nn.parte_entera, nn.decimal_1, nn.decimal_2, nn1.parte_entera,
		nn1.decimal_1, nn1.decimal_2);

	    for (int j = 1; j < (*pb)[i]->obtener_puntos ()->size (); j++)
	      {
		//nn=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx+(*(*pb)[i]->obtener_puntos())[j-1].coordx);
		//nn1=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy+(*(*pb)[i]->obtener_puntos())[j-1].coordy);
		//nn2=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx+(*(*pb)[i]->obtener_puntos())[j].coordx);
		//nn3=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy+(*(*pb)[i]->obtener_puntos())[j].coordy);
		nn = redondear_numero_dos_cifras (
		    (*(*pb)[i]->obtener_puntos ())[j - 1].coordx);
		nn1 = redondear_numero_dos_cifras (
		    (*(*pb)[i]->obtener_puntos ())[j - 1].coordy);
		nn2 = redondear_numero_dos_cifras (
		    (*(*pb)[i]->obtener_puntos ())[j].coordx);
		nn3 = redondear_numero_dos_cifras (
		    (*(*pb)[i]->obtener_puntos ())[j].coordy);

		char aux[30];
		char cadena9[120];
		sprintf (
		    cadena9,
		    "\\draw[color=zzttqq] (%d.%d%d,%d.%d%d) -- (%d.%d%d,%d.%d%d);",
		    nn.parte_entera, nn.decimal_1, nn.decimal_2,
		    nn1.parte_entera, nn1.decimal_1, nn1.decimal_2,
		    nn2.parte_entera, nn2.decimal_1, nn2.decimal_2,
		    nn3.parte_entera, nn3.decimal_1, nn3.decimal_2);
		fprintf (p_file, "\t %s \n", cadena9);
		cadena9[0] = '\0';
		//nn=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx+(*(*pb)[i]->obtener_puntos())[j].coordx);
		//nn1=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy+(*(*pb)[i]->obtener_puntos())[j].coordy);
		nn = redondear_numero_dos_cifras (
		    (*(*pb)[i]->obtener_puntos ())[j].coordx);
		nn1 = redondear_numero_dos_cifras (
		    (*(*pb)[i]->obtener_puntos ())[j].coordy);

		sprintf (aux, " -- (%d.%d%d,%d.%d%d)", nn.parte_entera,
			 nn.decimal_1, nn.decimal_2, nn1.parte_entera,
			 nn1.decimal_1, nn1.decimal_2);
		strcat (cadena8, aux);
		aux[0] = '\0';
	      }

	    //nn = redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx + (*(*pb)[i]->obtener_puntos()).back().coordx);
	    //nn1 = redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy + (*(*pb)[i]->obtener_puntos()).back().coordy);
	    //nn2 = redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx + (*(*pb)[i]->obtener_puntos())[0].coordx);
	    //nn3 = redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy + (*(*pb)[i]->obtener_puntos())[0].coordy);
	    nn = redondear_numero_dos_cifras (
		(*(*pb)[i]->obtener_puntos ()).back ().coordx);
	    nn1 = redondear_numero_dos_cifras (
		(*(*pb)[i]->obtener_puntos ()).back ().coordy);
	    nn2 = redondear_numero_dos_cifras (
		(*(*pb)[i]->obtener_puntos ())[0].coordx);
	    nn3 = redondear_numero_dos_cifras (
		(*(*pb)[i]->obtener_puntos ())[0].coordy);
	    char cadena9[1200];
	    sprintf (
		cadena9,
		"\\draw[color=zzttqq] (%d.%d%d,%d.%d%d) -- (%d.%d%d,%d.%d%d);",
		nn.parte_entera, nn.decimal_1, nn.decimal_2, nn1.parte_entera,
		nn1.decimal_1, nn1.decimal_2, nn2.parte_entera, nn2.decimal_1,
		nn2.decimal_2, nn3.parte_entera, nn3.decimal_1, nn3.decimal_2);
	    fprintf (p_file, "\t %s \n", cadena9);
	    strcat (cadena8, " -- cycle;");
	    // PARA QUE NO SALTE SI HAY MAS DE 509 ELEMENTOS:
	    unsigned long tam_cad = strlen (cadena8);
	    for (int iii = 0; iii < tam_cad; iii++)
	      {
		fprintf (p_file, "%c", cadena8[iii]);
	      }
	    cadena8[0] = '\0';
	    fprintf (p_file, "\n");

	    nn = redondear_numero_dos_cifras (
		(*pb)[i]->getCoord ().coordx + ((*pb)[i]->getl () / 2));
	    nn1 = redondear_numero_dos_cifras (
		(*pb)[i]->getCoord ().coordy + ((*pb)[i]->getw () / 2));
	    //nn = redondear_numero_dos_cifras(((*pb)[i]->getl() / 2));
	    //nn1 = redondear_numero_dos_cifras(((*pb)[i]->getw() / 2));
	    sprintf (cadena8, "\\draw (%d.%d%d,%d.%d%d) node {\\tiny $%d$}; ",
		     nn.parte_entera, nn.decimal_1, nn.decimal_2,
		     nn1.parte_entera, nn1.decimal_1, nn1.decimal_2,
		     (*pb)[i]->getID ());
	    fprintf (p_file, "\t %s \n", cadena8);
	    cadena8[0] = '\0';
	  }

	// CORTES GUILLOTINA
	vector<EDGES>::iterator gc;
	vector<EDGES> *gil_cut = b->getGC ();

	for (gc = (*gil_cut).begin (); gc != (*gil_cut).end (); gc++) // para cada corte guillotina
	  {
	    char cadena9[1200];
	    nn = redondear_numero_dos_cifras (gc->ini.coordx);
	    nn1 = redondear_numero_dos_cifras (gc->ini.coordy);
	    nn2 = redondear_numero_dos_cifras (gc->fin.coordx);
	    nn3 = redondear_numero_dos_cifras (gc->fin.coordy);
	    sprintf (
		cadena9,
		"\\draw[color=black] (%d.%d%d,%d.%d%d) -- (%d.%d%d,%d.%d%d);",
		nn.parte_entera, nn.decimal_1, nn.decimal_2, nn1.parte_entera,
		nn1.decimal_1, nn1.decimal_2, nn2.parte_entera, nn2.decimal_1,
		nn2.decimal_2, nn3.parte_entera, nn3.decimal_1, nn3.decimal_2);
	    fprintf (p_file, "%s  \n", cadena9);
	    cadena9[0] = '\0';

	  }

	sprintf (cadena, "\\end{tikzpicture}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\caption{BIN %d - USAGE %lf}", b->getID (),
		 b->getPropUtil ());
	//sprintf (cadena,"\\caption{\\ddmmyydate  \\today (\\currenttime)}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\end{figure}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	if (fig % 2 == 0)
	  {
	    sprintf (cadena, "\\clearpage");
	    fprintf (p_file, "%s \n\n", cadena);
	    cadena[0] = '\0';
	  }
      }

    //---------

    sprintf (cadena, "\\end{document}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    fclose (p_file);
    return;

  }

  NUMERO
  redondear_numero_dos_cifras (double n)
  {
    NUMERO num;
    num.parte_entera = int (n);
    num.decimal_1 = int (n * 10) % 10;
    int dec = int (n * 100);
    if ((n * 100) + .5 > dec + 1)
      num.decimal_2 = dec + 1 - 100 * num.parte_entera - 10 * num.decimal_1;
    else
      num.decimal_2 = dec - 100 * num.parte_entera - 10 * num.decimal_1;

    return num;
  }

  void
  dibujar_nodes (const string &data_file_name, const string &output_file_name,
		 vector<NODE> &node, double runtime, double L, double W,
		 int escalado)
  {
    FILE *p_file;

    // abre el fichero .txt
    //
    if ((p_file = fopen (output_file_name.c_str (), "w")) == NULL)
      {
	printf ("Error in file %s\n", output_file_name);
	exit (1);
      }

    char cadena[120];
    sprintf (cadena, "\\documentclass[12pt,a4paper]{report}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{amsmath}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{txfonts}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{graphicx}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage[latin1]{inputenc}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage[spanish]{babel}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{times}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{datetime}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{placeins}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{subfigure}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{supertabular}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{fullpage,graphicx}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{afterpage}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage {color}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage [all] {xy}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepackage{pgf,tikz}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{fit}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary{shapes.geometric}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary[shapes.geometric]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{shapes.geometric,shapes.arrows} ");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{shapes.symbols,positioning}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{matrix,chains,scopes,positioning,fit}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary[shapes.geometric]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgfmodule{shapes}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgfmodule[shapes] ");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary{arrows}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary[arrows]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{arrows}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary[arrows]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{positioning}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary{decorations.pathmorphing}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usepgflibrary[decorations.pathmorphing]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{decorations.pathmorphing}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary[decorations.pathmorphing]");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary{er}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\usetikzlibrary[er] ");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\tikzset{point/.default=} ");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\author{Marta Cabo}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\title{SOLUCION INSTANCIA}");
    fprintf (p_file, "%s \n\n", cadena);
    cadena[0] = '\0';

    sprintf (cadena, "\\begin{document} \n");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';
    //sprintf(cadena,"\\noindent Instance name: %s, \n \n \\noindent Running Time: %.3f secs",instance, t);
    sprintf (
	cadena,
	"\\noindent Instance name: $%s$, \n \n \\noindent Running Time: %.3f secs",
	data_file_name, runtime);
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';
    sprintf (cadena,
	     "\n \\noindent Date: \\ddmmyydate  \\today  ~(\\currenttime)");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';
    sprintf (cadena, "\n \\noindent Total Number of Bins: %lu", node.size ());
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';
    double usage = node.size () - 1 + (node.end () - 1)->getPropUtil ();
    sprintf (cadena, "\n \\noindent Fractional Bin Usage: %.3f", usage);
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    int fig = 0;

    vector<NODE>::iterator n;
    for (n = node.begin (); n != node.end (); n++)
      {
	//---------
	fig++;
	NUMERO nn, nn1, nn2, nn3;

	sprintf (cadena, "\\begin{figure}[ht]");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\centering");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\definecolor{ffqqqq}{rgb}{1,0,0}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\definecolor{zzttqq}{rgb}{0.6,0.2,0}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\definecolor{cqcqcq}{rgb}{0.75,0.75,0.75}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	double sc = 100 / L;
	if (sc > 100 / W)
	  sc = 100 / W;
	sprintf (
	    cadena,
	    "\\begin{tikzpicture}[scale=0.1, line cap=round, line join=round, >=triangle 45, x=%lf cm,y=%lf cm]",
	    sc, sc);
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (L);
	sprintf (cadena, "\\draw[color=black] (0,0) -- (%.2lf,0);", L);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (W);
	sprintf (cadena, "\\draw[color=black] (0,0) -- (0,%.2lf);", W);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (L + 3);
	nn1 = redondear_numero_dos_cifras (W + 3);
	sprintf (cadena, "\\clip(-3,-3) rectangle (%.2lf,%.2lf);", L + 3,
		 W + 3);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (W);
	nn1 = redondear_numero_dos_cifras (L);
	nn2 = redondear_numero_dos_cifras (W);
	sprintf (cadena, "\\draw[color=black] (-2,%.2lf) -- (%.2lf,%.2lf);", W,
		 L, W);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	nn = redondear_numero_dos_cifras (L);
	nn1 = redondear_numero_dos_cifras (L);
	nn2 = redondear_numero_dos_cifras (W);
	sprintf (cadena, "\\draw[color=black] (%.2lf,-2) -- (%.2lf,%.2lf);", L,
		 L, W);
	fprintf (p_file, "\t %s \n", cadena);
	cadena[0] = '\0';

	vector<PIEZA*> pb = n->getPI ();

	for (int i = 0; i < n->getNumPiezas (); i++)
	  {
	    char cadena8[1200];
	    sprintf (cadena8, "\%% New Piece");
	    fprintf (p_file, "%s \n", cadena8);
	    cadena8[0] = '\0';

	    //nn=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx+(*pb)[i]->obtener_puntos()->front().coordx);
	    //nn1=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy+(*pb)[i]->obtener_puntos()->front().coordy);
	    nn = redondear_numero_dos_cifras (
		pb[i]->obtener_puntos ()->front ().coordx);
	    nn1 = redondear_numero_dos_cifras (
		pb[i]->obtener_puntos ()->front ().coordy);

	    sprintf (
		cadena8,
		"\\fill[color=zzttqq,fill=zzttqq,fill opacity=0.2] (%.2lf,%.2lf)",
		pb[i]->obtener_puntos ()->front ().coordx,
		pb[i]->obtener_puntos ()->front ().coordy);

	    for (int j = 1; j < pb[i]->obtener_puntos ()->size (); j++)
	      {
		//nn=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx+(*(*pb)[i]->obtener_puntos())[j-1].coordx);
		//nn1=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy+(*(*pb)[i]->obtener_puntos())[j-1].coordy);
		//nn2=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx+(*(*pb)[i]->obtener_puntos())[j].coordx);
		//nn3=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy+(*(*pb)[i]->obtener_puntos())[j].coordy);
		nn = redondear_numero_dos_cifras (
		    (*pb[i]->obtener_puntos ())[j - 1].coordx);
		nn1 = redondear_numero_dos_cifras (
		    (*pb[i]->obtener_puntos ())[j - 1].coordy);
		nn2 = redondear_numero_dos_cifras (
		    (*pb[i]->obtener_puntos ())[j].coordx);
		nn3 = redondear_numero_dos_cifras (
		    (*pb[i]->obtener_puntos ())[j].coordy);

		char aux[30];
		char cadena9[120];
		sprintf (cadena9,
			 "\\draw[color=zzttqq] (%.2lf,%.2lf) -- (%.2lf,%.2lf);",
			 (*pb[i]->obtener_puntos ())[j - 1].coordx,
			 (*pb[i]->obtener_puntos ())[j - 1].coordy,
			 (*pb[i]->obtener_puntos ())[j].coordx,
			 (*pb[i]->obtener_puntos ())[j].coordy);
		fprintf (p_file, "\t %s \n", cadena9);
		cadena9[0] = '\0';
		//nn=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx+(*(*pb)[i]->obtener_puntos())[j].coordx);
		//nn1=redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy+(*(*pb)[i]->obtener_puntos())[j].coordy);
		nn = redondear_numero_dos_cifras (
		    (*pb[i]->obtener_puntos ())[j].coordx);
		nn1 = redondear_numero_dos_cifras (
		    (*pb[i]->obtener_puntos ())[j].coordy);

		sprintf (aux, " -- (%.2lf,%.2lf)",
			 (*pb[i]->obtener_puntos ())[j].coordx,
			 (*pb[i]->obtener_puntos ())[j].coordy);
		strcat (cadena8, aux);
		aux[0] = '\0';
	      }

	    //nn = redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx + (*(*pb)[i]->obtener_puntos()).back().coordx);
	    //nn1 = redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy + (*(*pb)[i]->obtener_puntos()).back().coordy);
	    //nn2 = redondear_numero_dos_cifras((*pb)[i]->getCoord().coordx + (*(*pb)[i]->obtener_puntos())[0].coordx);
	    //nn3 = redondear_numero_dos_cifras((*pb)[i]->getCoord().coordy + (*(*pb)[i]->obtener_puntos())[0].coordy);
	    nn = redondear_numero_dos_cifras (
		(*pb[i]->obtener_puntos ()).back ().coordx);
	    nn1 = redondear_numero_dos_cifras (
		(*pb[i]->obtener_puntos ()).back ().coordy);
	    nn2 = redondear_numero_dos_cifras (
		(*pb[i]->obtener_puntos ())[0].coordx);
	    nn3 = redondear_numero_dos_cifras (
		(*pb[i]->obtener_puntos ())[0].coordy);
	    char cadena9[1200];
	    sprintf (cadena9,
		     "\\draw[color=zzttqq] (%.2lf,%.2lf) -- (%.2lf,%.2lf);",
		     (*pb[i]->obtener_puntos ()).back ().coordx,
		     (*pb[i]->obtener_puntos ()).back ().coordy,
		     (*pb[i]->obtener_puntos ())[0].coordx,
		     (*pb[i]->obtener_puntos ())[0].coordy);
	    fprintf (p_file, "\t %s \n", cadena9);
	    strcat (cadena8, " -- cycle;");
	    // PARA QUE NO SALTE SI HAY MAS DE 509 ELEMENTOS:
	    unsigned long tam_cad = strlen (cadena8);
	    for (int iii = 0; iii < tam_cad; iii++)
	      {
		fprintf (p_file, "%c", cadena8[iii]);
	      }
	    cadena8[0] = '\0';
	    fprintf (p_file, "\n");

	    nn = redondear_numero_dos_cifras (
		pb[i]->getCoord ().coordx + (pb[i]->getl () / 2));
	    nn1 = redondear_numero_dos_cifras (
		pb[i]->getCoord ().coordy + (pb[i]->getw () / 2));
	    //			nn = redondear_numero_dos_cifras((pb[i]->getl() / 2));
	    //			nn1 = redondear_numero_dos_cifras((pb[i]->getw() / 2));
	    sprintf (cadena8, "\\draw (%.2lf,%.2lf) node {\\tiny $%d$}; ",
		     pb[i]->getCoord ().coordx + (pb[i]->getl () / 2),
		     pb[i]->getCoord ().coordy + (pb[i]->getw () / 2),
		     pb[i]->getID ());
	    fprintf (p_file, "\t %s \n", cadena8);
	    cadena8[0] = '\0';
	  }

	// CORTES GUILLOTINA
	vector<EDGES>::iterator gc;
	vector<EDGES> *gil_cut = n->getGC ();

	for (gc = (*gil_cut).begin (); gc != (*gil_cut).end (); gc++) // para cada corte guillotina
	  {
	    char cadena9[1200];
	    nn = redondear_numero_dos_cifras (gc->ini.coordx);
	    nn1 = redondear_numero_dos_cifras (gc->ini.coordy);
	    nn2 = redondear_numero_dos_cifras (gc->fin.coordx);
	    nn3 = redondear_numero_dos_cifras (gc->fin.coordy);
	    sprintf (cadena9,
		     "\\draw[color=black] (%.2lf,%.2lf) -- (%.2lf,%.2lf);",
		     gc->ini.coordx, gc->ini.coordy, gc->fin.coordx,
		     gc->fin.coordy);
	    fprintf (p_file, "%s  \n", cadena9);
	    cadena9[0] = '\0';

	  }

	sprintf (cadena, "\\end{tikzpicture}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\caption{BIN %d - USAGE %lf}", n->getID (),
		 n->getPropUtil ());
	//sprintf (cadena,"\\caption{\\ddmmyydate  \\today (\\currenttime)}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	sprintf (cadena, "\\end{figure}");
	fprintf (p_file, "%s \n", cadena);
	cadena[0] = '\0';

	if (fig % 2 == 0)
	  {
	    sprintf (cadena, "\\clearpage");
	    fprintf (p_file, "%s \n\n", cadena);
	    cadena[0] = '\0';
	  }
      }

    //---------

    sprintf (cadena, "\\end{document}");
    fprintf (p_file, "%s \n", cadena);
    cadena[0] = '\0';

    fclose (p_file);
    return;
  }


  //
  // area
  //

  bool
    orden_area (PIEZA i, PIEZA j)
    {
      return (i.getArea () > j.getArea ());
    }

  //
  // angle
  //

  vector<double>
  calculateInnerAngles (vector<EDGES> &ar)
  {
    vector<double> angles;
    double angle;
    double numer, denom;
    EDGES aux;
    //Obtain first angle
    long last = ar.size () - 1;
    //Set aux edge
    aux.ini = ar[last].ini;
    aux.fin = ar[0].fin;
    aux.set_mod ();
    //Cosine Law a^2 = b^2 + c^2 - 2bccos(angle(bc)).
    numer = pow (ar[last].mod, 2) + pow (ar[0].mod, 2) - pow (aux.mod, 2);
    denom = 2 * ar[last].mod * ar[0].mod;
    angle = acos (numer / denom) * 180.0 / HBS_PI;
    angles.push_back (angle);

    //Obtain remaining angles
    for (int i = 1; i < ar.size (); i++)
      {
	//Set aux edge
	aux.ini = ar[i - 1].ini;
	aux.fin = ar[i].fin;
	aux.set_mod ();
	//Cosine law for the remaining of the angles
	numer = pow (ar[i - 1].mod, 2) + pow (ar[i].mod, 2) - pow (aux.mod, 2);
	denom = 2 * ar[i - 1].mod * ar[i].mod;
	angle = acos (numer / denom) * 180.0 / HBS_PI;
	angles.push_back (angle);
      }
    return angles;
  }

  vector<double>
  calculate_rotations_FitNode (NODE &n, PIEZA &p, int num_rot, double epsilon)
  {
    if (p.get_angulo_usado () != 0) //Coloca la pieza en su posición original.
      {
	p.obtener_rotacion (0);
      }
    vector<double> g_angles; //Vector of possible rotations
    vector<int> g_matchings; //non increasing order
    vector<double> breaking_ties;
    g_angles.assign (num_rot, -100);
    g_matchings.assign (num_rot, -1);
    breaking_ties.assign (num_rot, -1);

    vector<EDGES> *edges_p;
    vector<EDGES>::iterator it_e, it_e2, it_e3, it_e4;
    edges_p = p.getEdges ();

    // PRIMERO AÑADIMOS LAS DEL BIN:
    // CONSTRUIMOS EDGES DEL BIN EN SENTIDO HORARIO (para que la pieza quede
    // dentro):
    vector<EDGES> edges_bin;
    PUNTO pp1, pp2, pp4;
    pp1.coordx = 0;
    pp1.coordy = 0;
    pp2.coordx = 0;
    pp2.coordy = n.getW ();
    pp4.coordx = n.getL ();
    pp4.coordy = 0;
    EDGES eb1, eb4;	//Considerar solo dos aristas del bin.
    eb1.ini = pp1;
    eb1.fin = pp2;
    eb4.ini = pp4;
    eb4.fin = pp1;
    eb1.set_mod ();
    eb4.set_mod ();
    edges_bin.push_back (eb1);
    edges_bin.push_back (eb4);
    //=======================
    for (it_e = edges_p->begin (); it_e != edges_p->end (); it_e++)
      {
	for (it_e2 = edges_bin.begin (); it_e2 != edges_bin.end (); it_e2++)
	  {
	    // CALCULATE ROTATION TO MATCH EDGES OF BIN
	    double alpha = calculate_rotation_match ((*it_e), (*it_e2));
	    bool ya_probado = false;
	    for (int compr_disp = 0; compr_disp < num_rot; compr_disp++)
	      {
		if (alpha >= g_angles[compr_disp] - epsilon
		    && alpha <= g_angles[compr_disp] + epsilon)
		  {
		    ya_probado = true;
		    break;
		  }
	      }
	    if (ya_probado)
	      continue;

	    // MATCHING:
	    int cont_match = 0;
	    double bt2 = 0;

	    // CALCULATING ROTATED EDGES OF p:
	    vector<EDGES> rp;
	    rp = rotation_piece (p, alpha);

	    for (it_e3 = rp.begin (); it_e3 != rp.end (); it_e3++)
	      {
		for (it_e4 = edges_bin.begin (); it_e4 != edges_bin.end ();
		    it_e4++)
		  {
		    (*it_e3).set_mod ();
		    if (calculate_rotation_match ((*it_e3), (*it_e4))
			<= epsilon)
		      {
			cont_match++;
			(*it_e3).set_mod ();
			(*it_e4).set_mod ();
			double min_length = (*it_e3).mod;
			double aux_d = (*it_e4).mod;
			if (aux_d < min_length)
			  min_length = aux_d;
			bt2 += min_length;
		      }
		  }
	      }

	    //VEMOS SI ES MEJOR QUE LOS num_rot primeros:
	    int pos = 0;
	    while (pos < g_matchings.size ()
		&& (cont_match < g_matchings[pos]
		    || (cont_match == g_matchings[pos]
			&& bt2 < breaking_ties[pos] - HBS_TOL)))
	      {
		pos++;
	      }

	    if (pos < g_matchings.size ())
	      {
		// GUARDAMOS ANGULO
		for (int j = g_matchings.size () - 1; j > pos; j--)
		  {
		    g_matchings[j] = g_matchings[j - 1];
		    g_angles[j] = g_angles[j - 1];
		    breaking_ties[j] = breaking_ties[j - 1];
		  }
		g_matchings[pos] = cont_match;
		g_angles[pos] = alpha;
		breaking_ties[pos] = bt2;
	      }
	  }
      }

    return g_angles;
  }

  double
  calculate_rotation_match (EDGES &e1, EDGES &e2)
  {
    double alpha;
    double u1 = e1.fin.coordx - e1.ini.coordx;
    double u2 = e1.fin.coordy - e1.ini.coordy;
    double v1 = e2.ini.coordx - e2.fin.coordx;
    double v2 = e2.ini.coordy - e2.fin.coordy;

    // CALCULAMOS ANGULO que forman las aristas. (mediante el prod interior)
    double num = (u1 * v1) + (u2 * v2);
    double denom = sqrt ((u1 * u1) + (u2 * u2)) * sqrt ((v1 * v1) + (v2 * v2));
    double cos_alpha = num / denom;
    if (cos_alpha >= 1 - HBS_TOL2) //Tolerance problems if cos_alpha is close to 1, alpha = 0.
      alpha = 0;
    else
      {
	if (equal_double (cos_alpha, -1.0, HBS_TOL))
	  cos_alpha = -1.0; //Avoid problems if cos_alpha very close to -1.
	alpha = acos (cos_alpha) * (180 / HBS_PI); //alpha is in degrees.
      }
    if (equal_double (alpha, 360.0, HBS_TOL2) || equal_double (alpha, 0.0, HBS_TOL2)) //e1 & e2 are already matched.
      {
	alpha = 0;
	return alpha;
      }

    // e1 is going to be rotated to match with e2
    double angulo_aux = 2 * HBS_PI * alpha / 360; //angulo_aux  = alpha rads.
    double cos_e1 = u1 / e1.mod; //cos of angle (e1, x-axis) (beta)
    double sin_e1 = u2 / e1.mod; //sin of angle (e1, x_axis) (beta)
    double cos_e2 = v1 / e2.mod; //cos of angle (e2, x-axis)
    double sin_e2 = v2 / e2.mod; //sin of angle (e2, x_axis)

    cos_alpha = cos (angulo_aux); //cos(alpha)
    double sin_alpha = sin (angulo_aux); //sin(alpha)

    double xx = (cos_e1 * cos_alpha) - (sin_e1 * sin_alpha); //cos(beta + alpha)
    double yy = (cos_e1 * sin_alpha) + (sin_e1 * cos_alpha); //sin(alpha + beta)

    if (equal_double (xx, cos_e2, HBS_TOL2) && equal_double (yy, sin_e2, HBS_TOL2)) //if alpha + beta = angle(e2, x-axis)  rotate clockwise
      {
	return alpha;
      }
    else
      //rotate anticlockwise.
      return (360 - alpha);
  }

  vector<EDGES>
  rotation_piece (PIEZA &p, double alpha)
  {
    vector<PUNTO>::iterator it;
    vector<EDGES> sol;
    vector<PUNTO> *pp;
    pp = p.obtener_puntos ();
    vector<PUNTO> ppp;

    double angulo_aux = 2 * HBS_PI * alpha / 360;

    for (it = pp->begin (); it != pp->end (); it++)
      {
	double modulo = sqrt (
	    (*it).coordx * (*it).coordx + (*it).coordy * (*it).coordy);
	double tita = HBS_PI / 2; // SI x=0 :: y>0
	if (modulo < HBS_TOL && modulo > -HBS_TOL)
	  tita = 0;
	else
	  {
	    if ((*it).coordx < HBS_TOL && (*it).coordx > -HBS_TOL && (*it).coordy < -HBS_TOL) // SI x>0 :: y>=0
	      {
		tita = 3 * HBS_PI / 2;
	      }
	    if ((*it).coordx > HBS_TOL && (*it).coordy >= 0) // SI x>0 :: y>=0
	      {
		tita = atan ((*it).coordy / (*it).coordx);
	      }
	    if ((*it).coordx > HBS_TOL && (*it).coordy < -HBS_TOL) // SI x>0 :: y<0
	      {
		tita = atan ((*it).coordy / (*it).coordx) + 2 * HBS_PI;
	      }
	    if ((*it).coordx < -HBS_TOL) // SI x<0
	      {
		tita = atan ((*it).coordy / (*it).coordx) + HBS_PI;
	      }
	  }

	PUNTO p_aux;
	p_aux.coordx = modulo * cos (angulo_aux + tita);
	p_aux.coordy = modulo * sin (angulo_aux + tita);
	ppp.push_back (p_aux);
      }
    for (int i = 0; i < ppp.size (); i++)
      {
	EDGES e_aux;
	e_aux.ini = ppp[i];
	if (i < ppp.size () - 1)
	  e_aux.fin = ppp[i + 1];
	else
	  e_aux.fin = ppp[0];
	sol.push_back (e_aux);
      }
    return sol;
  }

  vector<double>
  calculate_rotations_FitSection_Mirror (vector<EDGES> &ed_irrbin, PIEZA &p,
					 int num_rot, double epsilon)
  {
    // if piece is rotated, then place piece in original position.
    //
    if (p.get_angulo_usado () != 0)
      {
	p.obtener_rotacion (0);
      }
    vector<double> g_angles; //Vector of possible rotations
    vector<int> g_matchings; //number of edges that match
    vector<double> breaking_ties; //lenght of matching edges (sum)
    g_angles.assign (num_rot, -100);
    g_matchings.assign (num_rot, -1);
    breaking_ties.assign (num_rot, -1);
    int tot_ang = 0;
    vector<PIEZA*>::iterator it_p;

    vector<EDGES> *edges_p;
    vector<EDGES>::iterator it_e3, it_e4;
    edges_p = p.getEdges ();
    vector<EDGES>::iterator it_ep, it_es;
    //	for(int m = 0; m <= 0; m++)//For the rectangle instances, no need to mirror pieces

    for (int m = 0; m <= 1; m++)
      {
	if (m == 1 && p.get_mirror () == false)
	  p.set_mirror (true); //Trabajamos con la pieza reflejada.
	for (it_ep = edges_p->begin (); it_ep != edges_p->end (); it_ep++)
	  {
	    for (it_es = ed_irrbin.begin (); it_es != ed_irrbin.end (); it_es++)
	      {

		// CALCULATE ROTATION TO MATCH EDGES OF BIN
		double alpha = calculate_rotation_match ((*it_ep), (*it_es));
		double alpha_mir = alpha; //This angle indicates if the alpha calculated is the for the mirrrored piece
		if (m == 1)
		  {
		    if (equal_double (alpha, 0, epsilon))
		      alpha_mir = -1000;
		    else
		      alpha_mir = -1 * alpha;
		  }

		bool ya_probado = false;
		for (int compr_disp = 0; compr_disp < num_rot; compr_disp++)
		  {
		    if (alpha_mir >= g_angles[compr_disp] - epsilon
			&& alpha_mir <= g_angles[compr_disp] + epsilon)
		      {
			ya_probado = true;
			break;
		      }
		  }
		if (ya_probado)
		  continue;

		// MATCHING:
		int cont_match = 0;
		double bt2 = 0;
		// CALCULATING ROTATED EDGES OF p:
		vector<EDGES> rp;
		rp = rotation_piece (p, alpha);
		for (it_e3 = rp.begin (); it_e3 != rp.end (); it_e3++)
		  {
		    for (it_e4 = ed_irrbin.begin (); it_e4 != ed_irrbin.end ();
			it_e4++)
		      {
			(*it_e3).set_mod ();
			if (calculate_rotation_match ((*it_e3), (*it_e4))
			    <= epsilon)
			  {
			    cont_match++;
			    (*it_e3).set_mod ();
			    (*it_e4).set_mod ();
			    double min_length = (*it_e3).mod;
			    double aux_d = (*it_e4).mod;
			    if (aux_d < min_length)
			      min_length = aux_d;
			    bt2 += min_length; //break ties by matching edges. (maybe change this later).
			  }
		      }
		  }
		//VEMOS SI ES MEJOR QUE LOS num_rot primeros:
		int pos = 0;
		while (pos < g_matchings.size ()
		    && (cont_match < g_matchings[pos]
			|| (cont_match == g_matchings[pos]
			    && bt2 < breaking_ties[pos] - HBS_TOL)))
		  {
		    pos++;
		  }

		if (pos < g_matchings.size ())
		  {
		    // GUARDAMOS ANGULO
		    for (int j = g_matchings.size () - 1; j > pos; j--)
		      {
			g_matchings[j] = g_matchings[j - 1];
			g_angles[j] = g_angles[j - 1];
			breaking_ties[j] = breaking_ties[j - 1];
		      }
		    g_matchings[pos] = cont_match;
		    if (m == 0)
		      g_angles[pos] = alpha; //Piece is not mirrored
		    else if (alpha == 0)
		      g_angles[pos] = -1000; //Piece is mirrored and rotation angle is 0.
		    else
		      g_angles[pos] = -1 * alpha; //piece is mirrored.
		    breaking_ties[pos] = bt2;
		  }
	      }
	  }
      }
    p.set_mirror (false);
    int i = 0;
    tot_ang = 0;
    while (i < g_angles.size ())
      {
	if (g_angles[i] != -100)
	  tot_ang++;
	i++;
      }
    g_angles.resize (tot_ang);
    return g_angles;
  }

  vector<double>
  calculate_rotations_FitBin_Mirror (BIN &b, PIEZA &p, int num_rot,
				     double epsilon)
  {
    if (p.get_angulo_usado () != 0)
      {
	p.obtener_rotacion (0);
      }
    vector<double> g_angles; //Vector of possible rotations
    vector<int> g_matchings; //number of edges that match
    vector<double> breaking_ties; //lenght of matching edges (sum)
    g_angles.assign (num_rot, -100);
    g_matchings.assign (num_rot, -1);
    breaking_ties.assign (num_rot, -1);

    vector<PIEZA*>::iterator it_p;

    vector<EDGES> *edges_p;
    vector<EDGES>::iterator it_e, it_e2, it_e3, it_e4;
    edges_p = p.getEdges ();

    // PRIMERO AÑADIMOS LOS LADOS DEL BIN:
    // CONSTRUIMOS EDGES DEL BIN EN SENTIDO HORARIO (para que la pieza quede
    // dentro):
    vector<EDGES> edges_bin;
    PUNTO pp1, pp2, pp4;
    pp1.coordx = 0;
    pp1.coordy = 0;
    pp2.coordx = 0;
    pp2.coordy = b.getW ();
    pp4.coordx = b.getL ();
    pp4.coordy = 0;
    EDGES eb1, eb4;	//Considerar solo dos aristas del bin.
    eb1.ini = pp1;
    eb1.fin = pp2;
    eb4.ini = pp4;
    eb4.fin = pp1;
    eb1.set_mod ();
    eb4.set_mod ();
    edges_bin.push_back (eb1);
    edges_bin.push_back (eb4);
    //=======================
    //	for(int m = 0; m<= 0; m++)//For the rectangle instances, no need of mirroring.
    for (int m = 0; m <= 1; m++)
      {
	if (m == 1 && p.get_mirror () == false)
	  p.set_mirror (true);	//Trabajamos con la pieza reflejada.
	for (it_e = edges_p->begin (); it_e != edges_p->end (); it_e++)
	  {
	    for (it_e2 = edges_bin.begin (); it_e2 != edges_bin.end (); it_e2++)
	      {
		// CALCULATE ROTATION TO MATCH EDGES OF BIN
		double alpha = calculate_rotation_match ((*it_e), (*it_e2));
		double alpha_mir = alpha; //This angle indicates if the alpha calculated is the for the mirrrored piece
		if (m == 1)
		  {
		    if (equal_double (alpha, 0, epsilon))
		      alpha_mir = -1000;
		    else
		      alpha_mir = -1 * alpha;
		  }

		bool ya_probado = false;
		for (int compr_disp = 0; compr_disp < num_rot; compr_disp++)
		  {
		    if (alpha_mir >= g_angles[compr_disp] - epsilon
			&& alpha_mir <= g_angles[compr_disp] + epsilon)
		      {
			ya_probado = true;
			break;
		      }
		  }
		if (ya_probado)
		  continue;

		// MATCHING:
		int cont_match = 0;
		double bt2 = 0;
		// CALCULATING ROTATED EDGES OF p:
		vector<EDGES> rp;
		rp = rotation_piece (p, alpha);

		for (it_e3 = rp.begin (); it_e3 != rp.end (); it_e3++)
		  {
		    for (it_e4 = edges_bin.begin (); it_e4 != edges_bin.end ();
			it_e4++)
		      {
			if (calculate_rotation_match ((*it_e3), (*it_e4))
			    <= epsilon)
			  {
			    cont_match++;
			    (*it_e3).set_mod ();
			    (*it_e4).set_mod ();
			    double min_length = (*it_e3).mod;
			    double aux_d = (*it_e4).mod;
			    if (aux_d < min_length)
			      min_length = aux_d;
			    bt2 += min_length;
			  }
		      }
		  }

		//VEMOS SI ES MEJOR QUE LOS num_rot primeros:
		int pos = 0;
		while (pos < g_matchings.size ()
		    && (cont_match < g_matchings[pos]
			|| (cont_match == g_matchings[pos]
			    && bt2 < breaking_ties[pos] - HBS_TOL)))
		  {
		    pos++;
		  }

		if (pos < g_matchings.size ())
		  {
		    // GUARDAMOS ANGULO
		    for (int j = g_matchings.size () - 1; j > pos; j--)
		      {
			g_matchings[j] = g_matchings[j - 1];
			g_angles[j] = g_angles[j - 1];
			breaking_ties[j] = breaking_ties[j - 1];
		      }
		    g_matchings[pos] = cont_match;
		    if (m == 0)
		      g_angles[pos] = alpha; //Piece is not mirrored
		    else if (alpha == 0)
		      g_angles[pos] = -1000; //Piece is mirrored and rotation angle is 0.
		    else
		      g_angles[pos] = -1 * alpha; //piece is mirrored.
		    breaking_ties[pos] = bt2;
		  }
	      }
	  }
      }
    p.set_mirror (false);
    return g_angles;
  }


  //
  // convex hull
  //

  double
  calcular_area_exacta (vector<PUNTO> &poligono)
  {
    if (poligono.empty () == true)
      return -1;
    if (poligono.size () < 3)
      return -1;
    double suma = 0;
    //Calculo del área utilizando la fórmula A = 1/2(x(i)y(i+1) - x(i+1)y(i))
    for (int i = 0; i < poligono.size () - 1; i++) //Sentido antihorario
      {
	suma += poligono[i].coordx * poligono[i + 1].coordy
	    - poligono[i].coordy * poligono[i + 1].coordx;
      } //for
	//ahora el ultimo con el primero
    int i = poligono.size () - 1;
    suma += poligono[i].coordx * poligono[0].coordy
	- poligono[i].coordy * poligono[0].coordx;
    //Si la suma es negativa, entonces recorremos los vértices en sentido horario
    if (suma <= HBS_TOL)
      {
	std::reverse (poligono.begin (), poligono.end ());
      }
    return fabs (suma) / 2;
  }

  // This function returns the convex hull (as a piece) of all the pieces in one
  // section of the bin.
  //
  PIEZA
  create_convexhull_in_section (IRR_BIN &sect)
  {
    PIEZA convexhull;
    vector<PIEZA*> *pb = sect.get_pzas (); //pb pieces in bin.
    vector<PUNTO> ptos_sect; //vector que contiene todos los puntos de las piezas que están en la sección. Para construir el convex hull.
    vector<PUNTO> ptos_pza; //Puntos de cada pieza.
    vector<PUNTO> ch_sect;
    vector<PUNTO>::iterator it_pto;
    vector<PIEZA*>::iterator it_pza;
    //Create the convex hull of the pieces in the bin.
    //===============================================================
    convexhull.setID ((-1) * sect.getID ());	//convex hull ID = -ID sect.
    convexhull.setbin (sect.getID ());//Indicates the bin in which these pieces are placed.
    for (it_pza = pb->begin (); it_pza != pb->end (); it_pza++)
      {
	ptos_pza = *(*it_pza)->obtener_puntos ();
	for (it_pto = ptos_pza.begin (); it_pto != ptos_pza.end (); it_pto++)
	  {
	    ptos_sect.push_back (*it_pto);
	  }
      }
    ch_sect = convex_hull (ptos_sect);//Returns points in the convex hull counter clockwise. Last point equals to first.
    for (int i = 0; i < ch_sect.size () - 1; i++)//Delete all duplicates created by numerical errors with convexhull.
      {
	if (equal_pto (ch_sect[i], ch_sect[i + 1]))
	  {
	    ch_sect.erase (ch_sect.begin () + i);
	  }
      }
    ch_sect.back ();	//Move to last point in vector
    ch_sect.pop_back (); //Delete last entry

    for (int i = 0; i < ch_sect.size (); i++)
      convexhull.add_point (ch_sect[i]); //adds convexhull points to convexhull (piece).
    convexhull.initialize_piece ();
    //Redefine edges, since ptos iniciales are placed in origin.
    convexhull.ini_edges ();
    return convexhull;
  }

  // Returns a list of points on the convex hull in counter-clockwise order.
  // Note: the last point in the returned list is the same as the first one.
  //
  vector<PUNTO>
  convex_hull (vector<PUNTO> P)
  {
    unsigned long n = P.size ();
    int k = 0;
    vector<PUNTO> H (2 * n);
    //Initialize vector H to (-100, -100)
    for (int i = 0; i < H.size (); i++)
      {
	H[i].coordx = -100;
	H[i].coordy = -100;
      }
    // Sort points lexicographically
    sort (P.begin (), P.end (), lexicographic);

    // Build lower hull
    for (int i = 0; i < n; ++i)
      {
	while (k >= 2 && cross (H[k - 2], H[k - 1], P[i]) <= 0)
	  k--;
	H[k++] = P[i];
      }

    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--)
      {
	while (k >= t && cross (H[k - 2], H[k - 1], P[i]) <= 0)
	  k--;
	H[k++] = P[i];
      }

    H.resize (k);
    return H;
  }

  double
  convexhull_Utilization (PIEZA P1, PIEZA P2)
  {
    double Util;
    vector<PUNTO> ptos_ch, ptos_p1, ptos_p2;
    vector<PUNTO> ch;
    vector<PUNTO>::iterator it_pto;
    ptos_p1 = *P1.obtener_puntos (); //puntos pieza 1
    ptos_p2 = *P2.obtener_puntos (); //puntos pieza 2

    //Create the convex hull of P1 U P2
    for (it_pto = ptos_p1.begin (); it_pto != ptos_p1.end (); it_pto++)
      ptos_ch.push_back (*it_pto);
    for (it_pto = ptos_p2.begin (); it_pto != ptos_p2.end (); it_pto++)
      ptos_ch.push_back (*it_pto);
    ch = convex_hull (ptos_ch);
    ch.back (); //Move to last point in vector
    ch.pop_back (); //Delete last entry
    //=================================

    //Calculate utilization of convex hull.
    double area_ch = calcular_area_exacta (ch);
    Util = (P1.getArea () + P2.getArea ()) / area_ch;
    //=========================================
    return Util;
  }

  double
  cross (PUNTO &O, PUNTO &A, PUNTO &B)
  {
    return (A.coordx - O.coordx) * (B.coordy - O.coordy)
	- (A.coordy - O.coordy) * (B.coordx - O.coordx);
  }

  double
  convexhull_Length (PIEZA P1, PIEZA P2)
  {
    double ancho = 0;
    vector<PUNTO> ptos_ch, ptos_p1, ptos_p2;
    vector<PUNTO> ch;
    vector<PUNTO>::iterator it_pto;
    ptos_p1 = *P1.obtener_puntos ();	//puntos pieza 1
    ptos_p2 = *P2.obtener_puntos ();	//puntos pieza 2

    //Create the convex hull of P1 U P2
    for (it_pto = ptos_p1.begin (); it_pto != ptos_p1.end (); it_pto++)
      ptos_ch.push_back (*it_pto);
    for (it_pto = ptos_p2.begin (); it_pto != ptos_p2.end (); it_pto++)
      ptos_ch.push_back (*it_pto);
    ch = convex_hull (ptos_ch);
    ch.back ();	//Move to last point in vector
    ch.pop_back (); //Delete last entry
    //=================================
    for (int i = 0; i < ch.size (); i++)
      {
	if (ch[i].coordx > ancho)
	  ancho = ch[i].coordx;
      }
    //=========================================
    return ancho;
  }

  double
  convexhull_Height (PIEZA P1, PIEZA P2)
  {
    double alto = 0;
    vector<PUNTO> ptos_ch, ptos_p1, ptos_p2;
    vector<PUNTO> ch;
    vector<PUNTO>::iterator it_pto;
    ptos_p1 = *P1.obtener_puntos ();	//puntos pieza 1
    ptos_p2 = *P2.obtener_puntos ();	//puntos pieza 2

    //Create the convex hull of P1 U P2
    for (it_pto = ptos_p1.begin (); it_pto != ptos_p1.end (); it_pto++)
      ptos_ch.push_back (*it_pto);
    for (it_pto = ptos_p2.begin (); it_pto != ptos_p2.end (); it_pto++)
      ptos_ch.push_back (*it_pto);
    ch = convex_hull (ptos_ch);
    ch.back ();	//Move to last point in vector
    ch.pop_back (); //Delete last entry
    //=================================
    for (int i = 0; i < ch.size (); i++)
      {
	if (ch[i].coordy > alto)
	  alto = ch[i].coordy;
      }
    //=========================================
    return alto;
  }


  //
  // basic functions
  //

  void
  read_pieces (const string &data_file_name, vector<PIEZA> &pieces)
  {
    char cadena[128];
    ifstream p_file (data_file_name);
    if (!p_file.is_open ())
      {
	cout << "ERROR: Unable to open " << data_file_name << " file\n";
	exit (1);
      }

    // Lee la primera fila de los archivos de datos, que contiene una línea de
    // información
    PIEZA p_actual;
    p_file >> cadena; // polyNo
    p_file >> cadena; // pointNo
    p_file >> cadena; // X
    p_file >> cadena; // Y
    int pieza_anterior = -1;
    p_actual.setID (1); //Crea el ID de la pieza, inicialmente =1
    //p_actual.setID(5);//Crea el ID de la pieza, inicialmente =5 (Para la permutación)
    int v_anterior = -1;
    while (!p_file.eof ()) //Mientras no llegue al fin del archivo (end_of_file)
      {
	int pieza;
	p_file >> cadena;
	sscanf (cadena, "%d", &pieza);	//Número de pieza
	if (pieza_anterior == -1)
	  pieza_anterior = pieza;
	if (pieza == pieza_anterior)
	  {
	    PUNTO ppp;
	    int v_actual;
	    p_file >> cadena;
	    sscanf (cadena, "%d", &v_actual);	//Numero de punto de la pieza
	    p_file >> cadena;
	    sscanf (cadena, "%lf", &ppp.coordx);
	    p_file >> cadena;
	    sscanf (cadena, "%lf", &ppp.coordy);
	    if (v_actual != v_anterior)
	      {
		v_anterior = v_actual;
		p_actual.add_point (ppp);
	      }
	  }
	else
	  {
	    // AÑADIMOS pieza al vector solución:
	    pieces.push_back (p_actual);
	    // COMENZAMOS CON LA SIGUIENTE
	    p_actual.clear_points ();
	    p_actual.setID (pieza);
	    PUNTO ppp;
	    p_file >> cadena;
	    p_file >> cadena;
	    sscanf (cadena, "%lf", &ppp.coordx);
	    p_file >> cadena;
	    sscanf (cadena, "%lf", &ppp.coordy);
	    p_actual.add_point (ppp);
	    pieza_anterior++;
	    //pieza_anterior = pieza;
	  }
      }
    // AñADIMOS LA ULTIMA pieza
    pieces.push_back (p_actual);
    for (int i = 0; i < pieces.size (); i++)
      {
	// INICIALIZAMOS PIEZAS:
	pieces[i].initialize_piece ();
      }
  }

  bool
  equal_double (double a, double b, double prec)
  {
    if (a >= b - prec && a <= b + prec)
      return true;
    else
      return false;
  }

  bool
  equal_pto (PUNTO a, PUNTO b)
  {
    if (equal_double (a.coordx, b.coordx, HBS_TOL)
	&& equal_double (a.coordy, b.coordy, HBS_TOL))
      return true;
    else
      return false;
  }

  bool
  lexicographic (PUNTO P1, PUNTO P2)
  {
    return (P1.coordx < P2.coordx
	|| (P1.coordx == P2.coordx && P1.coordy < P2.coordy));
  }

  int
  position (PUNTO A, PUNTO B, PUNTO C)
  {
    int pos = 100;
    double crosprod;
    //Avoid numerical errors, by rounding for comparison  pourposes
    //=============================================================
    if (fabs (A.coordx - C.coordx) < 0.01 && fabs (A.coordy - C.coordy) < 0.01) //A & C can be considered the same point
      C = A;
    if (fabs (B.coordx - C.coordx) < 0.01 && fabs (B.coordy - C.coordy) < 0.01) //B & C can be considered the same point
      C = B;
    //=============================================================
    crosprod = (B.coordx - A.coordx) * (C.coordy - A.coordy)
	- (B.coordy - A.coordy) * (C.coordx - A.coordx);
    if (crosprod > 0 + HBS_TOL)
      return 1;	//C is left of vector AB
    if (crosprod < 0 - HBS_TOL)
      return -1;	//C is right of vector AB
    if (equal_double (crosprod, 0, HBS_TOL))
      return 0;	//Alignded
    return pos;	//if returns 100 something is wrong.
  }

  double
  distancia (PUNTO p1, PUNTO p2)
  {
    double dist;
    dist = sqrt (
	pow (p2.coordy - p1.coordy, 2) + pow (p2.coordx - p1.coordx, 2));
    return dist;
  }

  int
  argmax_mod (vector<EDGES> &a)
  {
    int argmax = 0;
    double max = a[0].mod;
    for (int i = 1; i < a.size (); i++)
      {
	if (max < a[i].mod)
	  {
	    max = a[i].mod;
	    argmax = i;
	  }
      }
    return argmax;
  }

  //
  // move in section
  //

  bool
  edge_of_section (EDGES ed, IRR_BIN ib)
  {
    bool is_edge = false;
    vector<PUNTO> ib_ptos = *ib.get_ptos ();
    //Create all edges of section
    vector<EDGES> ib_ar;
    EDGES aux;
    unsigned long last = ib_ptos.size ();
    //Create edges of IRRBIN
    for (int i = 0; i < last; i++)
      {
	aux.ini = ib_ptos[i];
	if (i + 1 != last)
	  aux.fin = ib_ptos[i + 1];
	else
	  aux.fin = ib_ptos[0];
	aux.set_mod ();
	ib_ar.push_back (aux);
      }
    //If ed.ini and ed.fin is aligned with ib.ini and ib.fin then is_edge = true
    for (int i = 0; i < last; i++)
      {
	if (position (ib_ar[i].ini, ib_ar[i].fin, ed.ini) == 0
	    && position (ib_ar[i].ini, ib_ar[i].fin, ed.fin) == 0)
	  return true;
      }
    return is_edge;
  }

  void
  trans_piece_ini_fin (PIEZA &item2, EDGES e1, EDGES e2)
  {
    //Calculate translation:
    double trasX = e1.fin.coordx - e2.ini.coordx;
    double trasY = e1.fin.coordy - e2.ini.coordy;
    //Translate all points in P2 to vertex1
    item2.translate (trasX, trasY);
  }

  void
  trans_piece_fin_ini (PIEZA &item2, EDGES e1, EDGES e2)
  {
    //Calculate translation:
    double trasX = e1.ini.coordx - e2.fin.coordx;
    double trasY = e1.ini.coordy - e2.fin.coordy;
    //Translate all points in P2 to vertex1
    item2.translate (trasX, trasY);
  }

  double
  match_dist (EDGES e1, EDGES e2)
  {
    double md;
    double abs_dist = fabs (e1.mod - e2.mod);
    double max = e1.mod;
    if (e2.mod > e1.mod)
      max = e2.mod;
    md = 1 - abs_dist / max;
    return md;
  }

  bool
  Feasible_Slide_InSect (IRR_BIN bin, PIEZA item1, PIEZA &item2, int v1, int v2,
			 double dis)
  {
    bool feasible = true;
    //This function slides edge from piece p2 over edge 1 a distance dist as long as is a feasible move.
    vector<EDGES> *ed1 = item1.getEdges ();
    EDGES e1 = (*ed1)[v1];	//arista de la envoltura convexa.

    vector<PUNTO> ptos_i2 = *item2.obtener_puntos ();	//ptos de la pieza
    double xx = (e1.fin.coordx - e1.ini.coordx);
    double yy = (e1.fin.coordy - e1.ini.coordy);
    double alpha = atan2 (yy, xx);	//angle in radians (-180, 180).
    double xslide = dis * cos (alpha);	// slide over the x axis
    double yslide = dis * sin (alpha);	//slide over the y axis.
    //======================================================
    //Feasibility Check. Let's check if with this slide the piece fits in the bin.
    //First we have to slide copy of the points.
    vector<PUNTO> border = *bin.get_ptos ();
    for (int i = 0; i < ptos_i2.size (); i++)
      {
	ptos_i2[i].coordx += xslide;
	ptos_i2[i].coordy += yslide;
      }
    //Ver si es factible (si entra en la sección)
    unsigned long last = border.size ();
    for (int i = 0; i < ptos_i2.size (); i++)
      {
	for (int j = 0; j < border.size (); j++)
	  {
	    if (j + 1 != last)
	      {
		if (position (border[j], border[j + 1], ptos_i2[i]) == 1)
		  return false;
	      }
	    else if (position (border[last - 1], border[0], ptos_i2[i]) == 1)
	      return false;
	  }

      }

    //Slide piece
    item2.translate (xslide, yslide);
    return feasible;
  }

  void
  Attach (PIEZA item1, PIEZA &item2, int v1, int v2)
  {
    vector<EDGES> *ed_i2 = item2.getEdges ();
    vector<EDGES> *ed_i1 = item1.getEdges ();
    double rot_angle;
    EDGES e1 = (*ed_i1)[v1];
    EDGES e2 = (*ed_i2)[v2];
    //Rotate item2 so e2  matches edge e1
    rot_angle = calculate_rotation_match (e2, e1);
    item2.obtener_rotacion (rot_angle);
    ed_i2 = item2.getEdges ();
    //Translate end of edge p2 from piece 2 to begining of edge p1 of piece 1
    //trans_piece_fin_ini(item2, e1, (*ed_i2)[v2]);
    //Translate beginning of edge p2 from piece 2 to end of edge p1 of piece 1
    trans_piece_ini_fin (item2, e1, (*ed_i2)[v2]);
  }

  //
  // guillotine cuts
  //

  EDGES
  IntersectBin (EDGES gc, vector<PUNTO> rbin)
  {
    PUNTO A = gc.ini;
    PUNTO B = gc.fin;

    //We are checking intersection of line AB vs all lines in rbin.
    for (int j = 0; j < rbin.size () - 1; j++)
      {
	PUNTO p; //Intersection point
	PUNTO C = rbin[j];
	PUNTO D = rbin[j + 1];
	double xmin = C.coordx;
	double xmax = D.coordx;
	if (C.coordx > D.coordx)
	  {
	    xmin = D.coordx;
	    xmax = C.coordx;
	  }
	double ymin = C.coordy;
	double ymax = D.coordy;
	if (C.coordy > D.coordy)
	  {
	    ymin = D.coordy;
	    ymax = C.coordy;
	  }
	p = IntersectTwoLines (A, B, C, D);
	//Check whether the intersection point is whithin the limits of rbin.
	if (p.coordx > xmin - HBS_TOL && p.coordx < xmax + HBS_TOL
	    && p.coordy > ymin - HBS_TOL && p.coordy < ymax + HBS_TOL)
	  {
	    //The intersection point is in rbin.
	    //Check distance to ini or fin of current to update limits.
	    double dist_ini = distancia (p, gc.ini);
	    double dist_fin = distancia (p, gc.fin);
	    if (dist_ini < dist_fin)
	      gc.ini = p;//The intersection point is the ini of the current GC
	    else
	      gc.fin = p;//The intersection point is the fin of the current GC
	  }
	//The intersection point is not in the bin, so we do not change anything
      }
    //Check last edge of rbin
    //===========================
    unsigned long j = rbin.size () - 1;
    PUNTO p;	//Intersection point
    PUNTO C = rbin[j];
    PUNTO D = rbin[0];
    double xmin = C.coordx;
    double xmax = D.coordx;
    if (C.coordx > D.coordx)
      {
	xmin = D.coordx;
	xmax = C.coordx;
      }
    double ymin = C.coordy;
    double ymax = D.coordy;
    if (C.coordy > D.coordy)
      {
	ymin = D.coordy;
	ymax = C.coordy;
      }
    p = IntersectTwoLines (A, B, C, D);
    //Check whether the intersection point is whithin the limits of rbin.
    if (p.coordx > xmin - HBS_TOL && p.coordx < xmax + HBS_TOL && p.coordy > ymin - HBS_TOL
	&& p.coordy < ymax + HBS_TOL)
      {
	//The intersection point is in rbin.
	//Check distance to ini or fin of current to update limits.
	double dist_ini = distancia (p, gc.ini);
	double dist_fin = distancia (p, gc.fin);
	if (dist_ini < dist_fin)
	  gc.ini = p;	//The intersection point is the ini of the current GC
	else
	  gc.fin = p;	//The intersection point is the fin of the current GC
      }
    //The intersection point is not in the bin, so we do not change anything
    gc.set_mod ();
    return gc;
  }

  PUNTO
  IntersectTwoLines (PUNTO ini_l1, PUNTO fin_l1, PUNTO ini_l2, PUNTO fin_l2)
  {
    PUNTO r;
    //Write first line in slope intercept mode
    double x0 = ini_l1.coordx;
    double y0 = ini_l1.coordy;
    double x1 = fin_l1.coordx;
    double y1 = fin_l1.coordy;
    double slope1;
    if (!equal_double (x0, x1, HBS_TOL))
      slope1 = (y1 - y0) / (x1 - x0);			//Slope of first line
    else
      slope1 = HBS_GRANDE; //Line 1 is vertical
    //===================================================
    //Write second line in slope intercept mode
    double x2 = ini_l2.coordx;
    double y2 = ini_l2.coordy;
    double x3 = fin_l2.coordx;
    double y3 = fin_l2.coordy;
    double slope2;
    if (!equal_double (x2, x3, HBS_TOL))
      slope2 = (y3 - y2) / (x3 - x2);	//Slope of second line
    else
      slope2 = HBS_GRANDE;
    //=====================================================
    if (equal_double (slope1, slope2, HBS_TOL))	//Lines are parallel
      {
	r.coordx = -1;
	r.coordy = -1;
	return r;
      }
    r.coordx = (y2 - slope2 * x2 + slope1 * x0 - y0) / (slope1 - slope2);
    r.coordy = slope1 * (r.coordx - x0) + y0;
    if (slope1 == HBS_GRANDE)	//Line 1 is vertical
      {
	r.coordx = x0;
	r.coordy = slope2 * (x0 - x2) + y2;
	return r;
      }
    if (slope2 == HBS_GRANDE)	//Line 2 is vertical
      {
	r.coordx = ini_l2.coordx;
	return r;
      }
    return r;
  }

  vector<PUNTO>
  Redefine_IrrBin_withPieces (vector<PUNTO> &rbin, EDGES gc)
  {
    vector<PUNTO>::iterator it;
    it = rbin.begin ();
    //Change orientation of guillotine cut.
    PUNTO aux;
    aux = gc.ini;
    gc.ini = gc.fin;
    gc.fin = aux;
    //====================================
    //Add new limits of gc to rbin, to make the cut.
    //==============================================
    //For each edge check if limits of gc are aligned with the edge
    int j = 0;
    int j_next = 1;
    while (j < rbin.size ())
      {
	j_next = j + 1;
	if (j_next == rbin.size ())
	  j_next = 0;
	if (position (rbin[j], rbin[j_next], gc.ini) != 0)
	  j++;
	else
	  break;
      }

    if (j < rbin.size ()) //Insert gc after rbin[j]
      {
	int s = rbin.size ();
	//If gc.ini not equal to vertex of residual bin, include point
	if (!equal_pto (gc.ini, rbin[j]) && !equal_pto (gc.ini, rbin[j_next])) //Antes j+1
	  {
	    rbin.insert (it + j_next, gc.ini); //Antes j+1
	    it = rbin.begin ();
	  }
	if (!equal_pto (gc.fin, rbin[j_next]) && !equal_pto (gc.fin, rbin[j])) //Antes j+1
	//If gc.fin not equal to vertex of residual bin, include point.
	  {
	    it = it + j_next + 1; //Antes j+1
	    if (j_next + 1 >= s) //Antes j+1
	      //the guillotine cut is added at the end of rbin
	      rbin.push_back (gc.fin);
	    else
	      rbin.insert (it, gc.fin);
	    it = rbin.begin ();
	  }
      }
    else if (j == rbin.size ())				//Last edge
      {
	rbin.push_back (gc.ini);
	rbin.push_back (gc.fin);
      }
    j = 0;
    //Delete points that are to the left of the gc
    while (j < rbin.size ())
      {
	if (position (gc.ini, gc.fin, rbin[j]) != 1)
	  j++;
	else
	  rbin.erase (rbin.begin () + j);

      }
    return rbin;
  }

  double
  GuillotineCutWaste (PIEZA ch, IRR_BIN current_sect, EDGES &best_gc)
  {
    double min_waste = HBS_GRANDE;
    double prop_waste;
    vector<EDGES> ed_ch = *ch.getEdges ();//Get the edges of the convex hull of the pieces in the section
    vector<EDGES>::iterator it_ed;
    vector<PUNTO> ib_ptos;
    double area_used = ch.getArea ();
    bool is_edge_sect = false;
    ib_ptos = *current_sect.get_ptos ();
    EDGES gc;
    int countfalse = 0;
    //Initialize best_gc so we know if there are no more gc associated with that section
    //======================
    best_gc.ini.coordx = -1;
    best_gc.ini.coordy = -1;
    best_gc.fin.coordx = -1;
    best_gc.fin.coordy = -1;
    //======================
    if (equal_double (area_used, current_sect.getArea (), 5))
      return 0; //The convex hull fulfills the entire section.
    for (it_ed = ed_ch.begin (); it_ed != ed_ch.end (); it_ed++) //For each edge in the convex hull
      {
	is_edge_sect = edge_of_section (*it_ed, current_sect);
	if (!is_edge_sect) //That is not on the edge of a section
	  {
	    countfalse++;
	    gc = IntersectBin (*it_ed, ib_ptos); //get the guillotine cut defined by the edge of the ch.
	    prop_waste = CalculatePropWasteCut (ib_ptos, gc, area_used);
	    if (prop_waste < min_waste)
	      {
		best_gc = gc;
		min_waste = prop_waste;
	      }

	  }
      }
    return min_waste;
  }

  double
  CalculatePropWasteCut (vector<PUNTO> ib_ptos, EDGES gc, double area_used)
  {
    double waste;
    double prop_waste;
    vector<PUNTO> ptos_new;
    ptos_new = Redefine_IrrBin_withPieces (ib_ptos, gc);
    double totalarea;
    reverse (ptos_new.begin (), ptos_new.end ()); //To have the points in anticlockwise order
    totalarea = calcular_area_exacta (ptos_new);
    waste = totalarea - area_used;
    prop_waste = waste / totalarea;
    return prop_waste;
  }

  //
  // construct solution
  //

  bool
  FillBin (vector<PIEZA> &item, IRR_BIN &csect, EDGES &gc, int id)
  {
    bool placed = false;
    // Copy of the section in case no candidates fit in the new section
    //
    IRR_BIN old_sec = csect;
    vector<PUNTO> sect_points = *csect.get_ptos ();
    //Define the new section we are going to place pieces in
    int bin = csect.getBin ();
    csect = Redefine_NewSection (sect_points, gc);
    csect.set_ID (id);
    csect.setBin (bin);
    sect_points = *csect.get_ptos ();
    //Check wich of the items may fit in the new section in terms of area.
    int count = 0;
    while (count < item.size () && item[count].getArea () > csect.getArea ())
      count++; //Find first piece that may fit in terms of area.
    while (!placed && count < item.size ())
      {
	if (!item[count].is_placed ())
	  {
	    placed = PieceInSect (item[count], csect); //Place piece
	    count++;
	  }
	else
	  count++;
      }
    if (!placed)
      csect = old_sec;
    return placed;
  }

  //
  // sections in node
  //

  IRR_BIN
  Redefine_NewSection (vector<PUNTO> &rbin, EDGES gc)
  {
    IRR_BIN sect;
    PUNTO ini, fin;
    ini = gc.ini;
    fin = gc.fin;
    vector<PUNTO> ptos_sec;
    ptos_sec.push_back (ini);
    ptos_sec.push_back (fin);

    //Create the points of the new section
    //====================================
    //Add every point from rbin that are to the right of the gc.
    int j = 0;
    //Add points that are to the right of the gc
    while (j < rbin.size ())
      {
	int pos = position (ini, fin, rbin[j]);
	if (pos != -1)
	  j++;
	else
	  {
	    ptos_sec.push_back (rbin[j]);
	    j++;
	  }
      }
    //====================================
    //Order ptos of ptos_sec in clockwise order
    ptos_sec = convex_hull (ptos_sec);
    std::reverse (ptos_sec.begin (), ptos_sec.end ());
    //Eliminate last point
    ptos_sec.back ();
    ptos_sec.pop_back ();
    //Add them to the new section
    for (int i = 0; i < ptos_sec.size (); i++)
      {
	sect.add_points (ptos_sec[i]);
      }
    sect.setArea ();
    sect.get_angles ();
    return sect;
  }

  bool
  FitInSect_IniPcFinSec (vector<EDGES> e_pza, vector<PUNTO> ptos_Sec,
			 EDGES esec_match, EDGES epza_match)
  {
    esec_match.set_mod ();
    epza_match.set_mod ();
    if (esec_match.mod < epza_match.mod)
      return false; //Edge on the piece is longer than the edge of the section

    //Calculate translation: Matching Ini_pz with fin_sect
    double trasX = esec_match.fin.coordx - epza_match.ini.coordx;
    double trasY = esec_match.fin.coordy - epza_match.ini.coordy;
    //Translate all points in P2 to vertex1
    for (int i = 0; i < e_pza.size (); i++)
      {
	e_pza[i].ini.coordx += trasX;
	e_pza[i].ini.coordy += trasY;
      }
    int last_pto = ptos_Sec.size () - 1;
    for (int i = 0; i < e_pza.size (); i++)
      {
	for (int j = 0; j < ptos_Sec.size () - 1; j++)
	  {
	    int side = position (ptos_Sec[j], ptos_Sec[j + 1], e_pza[i].ini);
	    if (side == 1)
	      return false; //the point is to the left of the section (outside)
	  }
	//Last edge of section
	int side = position (ptos_Sec[last_pto], ptos_Sec[0], e_pza[i].ini);
	if (side == 1)
	  return false;	//the point is to the left of the section (outside)
      }

    return true;
  }

  bool
  FitInSect_FinPcIniSec (vector<EDGES> e_pza, vector<PUNTO> ptos_Sec,
			 EDGES esec_match, EDGES epza_match)
  {
    esec_match.set_mod ();
    epza_match.set_mod ();
    if (esec_match.mod < epza_match.mod)
      return false;//Edge on the piece is longer than the edge of the section

    //Calculate translation: Matching Ini_pz with fin_sect
    double trasX = esec_match.ini.coordx - epza_match.fin.coordx;
    double trasY = esec_match.ini.coordy - epza_match.fin.coordy;
    //Translate all points in P2 to vertex1
    for (int i = 0; i < e_pza.size (); i++)
      {
	e_pza[i].ini.coordx += trasX;
	e_pza[i].ini.coordy += trasY;
      }
    int last_pto = ptos_Sec.size () - 1;
    for (int i = 0; i < e_pza.size (); i++)
      {
	for (int j = 0; j < ptos_Sec.size () - 1; j++)
	  {
	    int side = position (ptos_Sec[j], ptos_Sec[j + 1], e_pza[i].ini);
	    if (side == 1)
	      return false;//the point is to the left of the section (outside)
	  }
	//Last edge of section
	int side = position (ptos_Sec[last_pto], ptos_Sec[0], e_pza[i].ini);
	if (side == 1)
	  return false;	//the point is to the left of the section (outside)
      }

    return true;
  }

  int
  BreakTie (vector<EDGES> e_pza, vector<PUNTO> ptos_sect, EDGES esec,
	    EDGES epza)
  {
    int best = -1;

    // counts the number of matches between the piece and the section, when the
    // ini of the piece is matched with the end of the section.
    //
    int IpFs = 0;

    // counts the number of matches between the piece and the section, when the
    // end of the piece is matched with the ini of the section.
    //
    int FpIs = 0;
    //Number of matches IpFs:
    //Calculate translation: Matching Ini_pz with fin_sect
    //=======================================================
    double trasX = esec.fin.coordx - epza.ini.coordx;
    double trasY = esec.fin.coordy - epza.ini.coordy;
    //Translate all points in piece to vertex in section
    for (int i = 0; i < e_pza.size (); i++)
      {
	e_pza[i].ini.coordx += trasX;
	e_pza[i].ini.coordy += trasY;
      }
    //Identify ptos_sec that matches the end of esec
    int k = 0;
    while (!equal_pto (ptos_sect[k], esec.fin))
      k++;
    int next = k + 1;
    if (k + 1 >= ptos_sect.size ())
      next = 0;

    // For all points in the piece, add those that are in line with the adjacent
    // edge
    //
    for (int i = 0; i < e_pza.size (); i++)
      {
	int match = position (ptos_sect[k], ptos_sect[next], e_pza[i].ini);
	if (match == 0)
	  IpFs++;
      }
    //Edges back to original position
    for (int i = 0; i < e_pza.size (); i++)
      {
	e_pza[i].ini.coordx -= trasX;
	e_pza[i].ini.coordy -= trasY;
      }
    //Calculate translation: Matching Fin_pz with Ini_sect
    //=======================================================
    trasX = esec.ini.coordx - epza.fin.coordx;
    trasY = esec.ini.coordy - epza.fin.coordy;
    //Translate all points in piece to vertex in section
    for (int i = 0; i < e_pza.size (); i++)
      {
	e_pza[i].ini.coordx += trasX;
	e_pza[i].ini.coordy += trasY;
      }
    //Identify ptos_sec that matches the ini of esec
    k = 0;
    while (!equal_pto (ptos_sect[k], esec.ini))
      k++;
    next = k - 1;
    if (k - 1 < 0)
      next = ptos_sect.size () - 1;
    for (int i = 0; i < e_pza.size (); i++) //For all points in the piece, add those that are in line with the adjacent edge
      {
	int match = position (ptos_sect[next], ptos_sect[k], e_pza[i].ini);
	if (match == 0)
	  FpIs++;
      }

    //=======================================================
    if (IpFs > FpIs)
      best = 0; //IniPz-EndSec more matches than the other position
    else
      best = 1; //EndPz-IniSec more matches than the other position
    return best; //If best = -1 still a tie.
  }

  //
  // open bin
  //

  bool
  PieceInSect (PIEZA &piece, IRR_BIN &current_sect)
  {
    if (piece.getArea () > current_sect.getArea ())
      return false;

    bool placed = false;
    vector<double> angle_piece, angle_sect;
    angle_piece = piece.get_angles ();
    angle_sect = current_sect.get_angles ();
    // CONSTRUIMOS EDGES DEL IRR_BIN EN SENTIDO HORARIO (para que la pieza quede dentro):
    vector<EDGES> edges_sec;
    vector<PUNTO> ptos_sect = *current_sect.get_ptos ();
    EDGES aux;
    unsigned long last = ptos_sect.size () - 1;
    for (int i = 0; i < ptos_sect.size () - 1; i++)
      {
	aux.ini = ptos_sect[i];
	aux.fin = ptos_sect[i + 1];
	edges_sec.push_back (aux);
      }
    //Last edge
    aux.ini = ptos_sect[last];
    aux.fin = ptos_sect[0];
    edges_sec.push_back (aux);
    //=====================================================
    vector<EDGES> ed_cand = *piece.getEdges ();
    vector<EDGES> ed_pza;

    vector<double> rots; //vector of possible rotations in which the given piece fits in the given section
    int max_rots = angle_sect.size () * angle_piece.size ();
    max_rots = 2 * max_rots;
    //	int max_rots = 2;
    rots = calculate_rotations_FitSection_Mirror (edges_sec, piece, max_rots,
    HBS_ALPHA);
    //===================================================================
    int count_rot = 0;
    bool is_in_sect_IpFs = false;
    bool is_in_sect_FpIs = false;
    while (!placed && count_rot < rots.size ())
      {
	//Rotate piece
	if (rots[count_rot] >= 0)
	  {
	    piece.set_mirror (false);
	    piece.obtener_rotacion (rots[count_rot]);
	  }
	else
	  {
	    piece.set_mirror (true);
	    if (rots[count_rot] != -1000) //rotation angle is not 0.
	      piece.obtener_rotacion (-1 * rots[count_rot]);
	  }
	ed_pza = *piece.getEdges ();
	vector<EDGES>::iterator it_sec, it_pza;
	//Check which edge of this rotation matches.
	for (it_pza = ed_pza.begin (); it_pza != ed_pza.end () && !placed;
	    it_pza++)
	  {
	    for (it_sec = edges_sec.begin (); it_sec != edges_sec.end ();
		it_sec++)
	      {
		if (calculate_rotation_match (*it_pza, *it_sec) <= HBS_ALPHA)
		  {
		    //Need to traslate a copy of the edges to see if it would be feasible.
		    is_in_sect_IpFs = FitInSect_IniPcFinSec (ed_pza, ptos_sect,
							     *it_sec, *it_pza); //check feasibility of matching.
		    is_in_sect_FpIs = FitInSect_FinPcIniSec (ed_pza, ptos_sect,
							     *it_sec, *it_pza);
		    if (is_in_sect_FpIs && is_in_sect_IpFs) //La pieza cabe en ambos extremos
		      {
			int pos = BreakTie (ed_pza, ptos_sect, *it_sec,
					    *it_pza);
			if (pos == 0)
			  is_in_sect_FpIs = false; //Aplicamos IniPz-FinSec
			if (pos == 1)
			  is_in_sect_IpFs = false; //APlicamos FinPz-IniSec

		      }
		    if (is_in_sect_IpFs)
		      {
			trans_piece_ini_fin (piece, *it_sec, *it_pza);
			current_sect.add_piece (piece);
			placed = true;
			break;
		      }
		    if (is_in_sect_FpIs)
		      {
			trans_piece_fin_ini (piece, *it_sec, *it_pza);
			//Place piece
			current_sect.add_piece (piece);
			placed = true;
			break;
		      }
		  }
	      }
	  }
	count_rot++;
      }

    // If candidate has not been placed. We need to take it back to original
    // position.
    //
    if (!placed)
      {
	piece.set_mirror (false);
	// Not necessarily true that with this we get the candidate to original
	// position.
	//
	piece.obtener_rotacion (0);
      }

    return placed;
  }

  bool
  FillBin (vector<PIEZA> &item, IRR_BIN &csect, EDGES &gc, int id,
	   vector<int> ID_disp)
  {
    bool placed = false;
    // Copy of the section in case no candidates fit in the new section
    //
    IRR_BIN old_sec = csect;
    vector<PUNTO> sect_points = *csect.get_ptos ();
    //Define the new section we are going to place pieces in
    int bin = csect.getBin ();
    csect = Redefine_NewSection (sect_points, gc);
    //In case it has created an unusual section with 2 points (not a polygon)
    //To avoid numerical problems.
    if ((csect.get_ptos ())->size () <= 2)
      {
	csect = old_sec;
	return false;
      }
    //==============================
    csect.set_ID (id);
    csect.setBin (bin);
    sect_points = *csect.get_ptos ();
    //Check wich of the items may fit in the new section in terms of area.
    int count = 0;
    while (count < item.size () && item[count].getArea () > csect.getArea ())
      count++;	//Find first piece that may fit in terms of area.
    while (!placed && count < item.size ())
      {
	vector<int>::iterator it;
	it = find (ID_disp.begin (), ID_disp.end (), item[count].getID ());//Piece has not been placed yet
	if (it != ID_disp.end ())
	  {
	    placed = PieceInSect (item[count], csect);	//Place piece
	    count++;
	  }
	else
	  count++;
      }
    if (!placed)
      csect = old_sec;
    return placed;
  }

  bool
  Place_in_NewSection (IRR_BIN &current_sect, vector<PIEZA*> &candidates,
		       EDGES &best_gc, int id)
  {
    bool placed = false;
    IRR_BIN old_sec = current_sect; //Copy of the section in case no candidates fit in the new section
    vector<PUNTO> sect_points = *current_sect.get_ptos ();
    //Define the new section we are going to place pieces in
    //int id = current_sect.getID()+1;
    int bin = current_sect.getBin ();
    current_sect = Redefine_NewSection (sect_points, best_gc);
    current_sect.set_ID (id);
    current_sect.setBin (bin);
    sect_points = *current_sect.get_ptos ();
    //Check which of the candidates may fit area-wise in the new section:
    int count = 0;
    while (count < candidates.size ())
      {
	if (candidates[count]->getArea () > current_sect.getArea ()) //The candidate does not fit
	  candidates.erase (candidates.begin () + count); //Eliminate the candidate from the candidate list.
	else
	  {
	    count++;
	  }
      }
    if (candidates.empty ()) //if no candidates left
      {
	current_sect = old_sec;
	return placed;
      }
    //=================================================================
    //There is at least one candidate that may fit in the new section (area-wise).
    int i = 0;
    while (!placed && i < candidates.size ())
      {
	placed = PieceInSect (*candidates[i], current_sect);
	i++;
      }
    if (!placed)
      current_sect = old_sec;
    return placed;
  }

  bool
  NextBestCG_candidates (vector<PIEZA*> &item, IRR_BIN &csect, EDGES &gc)
  {
    bool placed = false;
    IRR_BIN old_sec = csect; //Copy of the section in case no candidates fit in the new section
    vector<PUNTO> sect_points = *csect.get_ptos ();
    //Define the new section we are going to place pieces in
    int id = csect.getID () + 1;
    int bin = csect.getBin ();
    csect = Redefine_NewSection (sect_points, gc);
    csect.set_ID (id);
    csect.setBin (bin);
    sect_points = *csect.get_ptos ();
    //Check wich of the items may fit in the new section in terms of area.
    int count = 0;
    while (count < item.size () && item[count]->getArea () > csect.getArea ())
      count++; //Find first piece that may fit in terms of area.
    while (!placed && count < item.size ())
      {
	if (!item[count]->is_placed ())
	  {
	    placed = PieceInSect (*item[count], csect); //Place piece
	    count++; //Try next piece.
	  }
	else
	  count++; //Try next piece.
      }
    if (!placed)
      csect = old_sec;
    return placed;
  }

  void
  OpenBin (BIN &bin, PIEZA &item)
  {
    vector<double> angles = item.get_angles ();
    vector<double> try_rots;
    EDGES base_bin;
    base_bin.ini.coordx = bin.getL ();
    base_bin.ini.coordy = 0.0;
    base_bin.fin.coordx = 0.0;
    base_bin.fin.coordy = 0.0;
    base_bin.set_mod ();
    //=============================================
    try_rots = calculate_rotations_FitBin_Mirror (bin, item, 10, HBS_ALPHA); //Rotations that match the piece and the bin.
    //For the rectangle instances:
    //=============================
    //try_rots = calculate_rotations_FitBin_Mirror(bin, item, 2, HBS_ALPHA);//Rotations that match the piece and the
    //=============================
    bool placed = false;
    int count_rot = 0;
    if (item.getArea () < bin.get_waste () + HBS_TOL) //Area of piece < free area of bin
      {
	while (!placed && count_rot < try_rots.size ())
	  {
	    if (try_rots[count_rot] >= 0)
	      {
		item.set_mirror (false);
		item.obtener_rotacion (try_rots[count_rot]); //rotation refers to original piece
	      }
	    else	//rotation refers to piece mirrored
	      {
		item.set_mirror (true);
		if (try_rots[count_rot] != -1000) //rotation angle is not 0.
		  item.obtener_rotacion (-1 * try_rots[count_rot]);
	      }
	    //index holds the index of the closest point to Coord (ref point) on the x axis.
	    //==============================================================================
	    if (item.Fits_Bin (bin.getL (), bin.getW ()))
	      {
		placed = true;
		bin.include_piece (item);
	      }
	    count_rot++;
	  }
	if (!placed)
	  {
	    item.obtener_rotacion (0);
	    if (item.Fits_Bin (bin.getL (), bin.getW ()))
	      {
		placed = true;
		bin.include_piece (item);
	      }
	    //
	    //            double diag;
	    //            diag = sqrt(pow(bin.getL(),2) + pow(bin.getW(),2));
	    //            double ang_diag;
	    //            ang_diag = acos(bin.getL()/diag)*180 /HBS_PI;
	    // PlaceBigPiece();
	  }
      }
    else
      {
	cout << "Piece is Bigger than the Bin\n";
	exit (1);
      }
    return;
  }

  //
  // candidates
  //

  vector<PIEZA*>
  CreateList (vector<PIEZA> &item, IRR_BIN &sect, int LIST_SIZE, double thres,
	      vector<int> ID_disp)
  {
    vector<PIEZA*> list;
    PIEZA convexhull;
    convexhull = create_convexhull_in_section (sect);
    //convexhull = create_rectencl_in_section(sect);//Rectangle enclosure for the rectangle instances.
    vector<EDGES> *e_ch = convexhull.getEdges (); //Edges of the convex hull.
    vector<EDGES> *e_item;
    double area_ch = convexhull.getArea ();
    double area_sect = sect.getArea ();
    int p = 0;
    int pzas_rem = ID_disp.size ();
    bool is_ed_sect = false;
    while (list.size () < LIST_SIZE && !ID_disp.empty ())
      {
	p = pos_disp (item, ID_disp); //First available piece
	bool is_item_list = false;
	if (item[p].getArea () + area_ch < area_sect && !item[p].is_placed ()) //piece is candidate in terms of area, not being the list and not previusly placed.
	  {
	    if (pzas_rem <= LIST_SIZE) //All remaining pieces are candidates.
	      {
		list.push_back (&item[p]);
		continue;
	      }
	    e_item = item[p].getEdges ();
	    //Compare each edge of the convex hull with each edge of the piece to see if there is a possible match and include the piece in the list.
	    for (int i = 0; i < (*e_ch).size () && !is_item_list; i++) //For each edge of the convex hull
	      {
		is_ed_sect = edge_of_section ((*e_ch)[i], sect);
		if (!is_ed_sect) //The edge to match is not in the edge of the bin.
		  {
		    for (int j = 0; j < (*e_item).size () && !is_item_list; j++) //For each edge of the piece
		      {
			double md = match_dist ((*e_ch)[i], (*e_item)[j]); //Calculate md
			if (md >= thres) //if edges of convex hull and edges of piece are likely in lenght
			  {
			    list.push_back (&item[p]); //include piece in the list.
			    is_item_list = true;
			    break;
			  }
		      }
		  }
	      }
	    if (!is_item_list) //Item did not make it to the list, because edges are not of matching distance
	      {
		continue;
	      }
	  }
      }
    return list;
  }

  int
  pos_disp (vector<PIEZA> &item, vector<int> &ID)
  {
    int p = 0;
    bool piece_disp = false;
    vector<int>::iterator it;
    while (!piece_disp)
      {
	it = find (ID.begin (), ID.end (), item[p].getID ());
	if (it != ID.end ())
	  {
	    ID.erase (it);
	    piece_disp = true;
	  }
	else
	  p++; //move to the first available piece
      }
    return p;
  }

  bool
  Place_Candidates (NODE &node, IRR_BIN &sect, vector<PIEZA*> &list,
		    bool &CH_crit, bool &bestGC_crit, bool &NextGC_crit,
		    EDGES &best_gc, int &sec_mod_id)
  {
    bool placed = false;
    PIEZA convex_hull;
    IRR_BIN old_sec = sect;
    double ch_util = -1; //best utilization of the convex hull when the next piece is attached.
    int best_i = -1; //Best edge of the ch
    int best_j = -1; //Best edge of the piece
    int best_p = -1; //Best piece from list
    int best_m = -1; // = 0 piece not mirrored
    double best_d = -1; // best slide distance.
    double gc_util = -1; //best utilization of the bin, when the guillotine cut is performed.

    convex_hull = create_convexhull_in_section (sect);
    //convex_hull = create_rectencl_in_section(sect); //Rectangle enclosure for the rectangle instances.
    ch_util = SelectBestMatch (sect, list, convex_hull, best_i, best_j, best_d,
			       best_p, best_m);
    gc_util = GuillotineCutWaste (convex_hull, sect, best_gc);
    gc_util = 1 - gc_util;
    if (ch_util != -1 && ch_util > gc_util)
      {
	//Use CH-Criterion to place piece
	if (best_m == 1) //mirror piece
	  list[best_p]->set_mirror (true);
	Attach (convex_hull, *list[best_p], best_i, best_j); //Attach best values of edge i from convex hull and edge j from piece
	Feasible_Slide_InSect (sect, convex_hull, *list[best_p], best_i, best_j,
			       best_d); //Slide edges along best distance
	//Get the edges of the convex hull to include the guillotine cut.
	vector<EDGES> ed_ch = *convex_hull.getEdges ();
	sect.add_GC (ed_ch[best_i]); //Include the guillotine cut in the section
	sect.add_piece (*list[best_p]); //Include the new piece in the current sect
	placed = true;
	CH_crit = true;
      }
    else
      {
	//Use BestGC-Criterion: Place candidates in an empty section.
	placed = Place_in_NewSection (sect, list, best_gc, node.getNumSect ());
	if (placed)
	  {
	    sec_mod_id = old_sec.getID ();
	    sect.add_GC (best_gc);	//Add the guillotine cut to the section
	    bestGC_crit = true;
	  }
      }
    if (!placed && node.getNumSect () > 1)
      {
	//Use GC-Criterion if there is more than one section
	PUNTO gc_empty;
	gc_empty.coordx = -1;
	gc_empty.coordy = -1;
	//========================================
	for (int i = 0; i < node.getNumSect (); i++)
	  {
	    sect = node.get_ib (i);
	    convex_hull = create_convexhull_in_section (sect);//Creates the convex hull of pieces in the section
	    //			convex_hull = create_rectencl_in_section(sect); //Rectangle enclosure for the rectangle instances.
	    GuillotineCutWaste (convex_hull, sect, best_gc);
	    if (equal_pto (best_gc.ini, gc_empty)
		&& equal_pto (best_gc.fin, gc_empty)) //No more gc possible in current section, move to next
	      continue;
	    placed = NextBestCG_candidates (list, sect, best_gc);
	    if (placed)
	      {
		sec_mod_id = i;
		sect.set_ID (node.getNumSect ());
		sect.add_GC (best_gc);	//Add the guillotine cut to the section
		NextGC_crit = true;
		break;		//Out of the loop
	      }
	  }
      }
    if (!placed)
      sect = old_sec;
    return placed;
  }

  //
  // global evaluation
  //

  vector<PIEZA*>
  CreateList (vector<PIEZA> &item, IRR_BIN &sect)
  {
    int LIST_SIZE = 5;
    vector<PIEZA*> list;
    PIEZA convexhull;
    convexhull = create_convexhull_in_section (sect);
    //convexhull = create_rectencl_in_section(sect); //Rectangle enclosure for the rectangle instances.

    vector<EDGES> *e_ch = convexhull.getEdges (); //Edges of the convex hull.
    vector<EDGES> *e_item;
    double area_ch = convexhull.getArea ();
    double area_sect = sect.getArea ();
    int p = 0;
    bool is_ed_sect = false;

    while (item[p].is_placed ())
      {
	p++; //move to the first non placed piece
      }
    while (list.size () < LIST_SIZE && p < item.size ())
      {
	bool is_item_list = false;
	if (item[p].getArea () + area_ch < area_sect && !item[p].is_placed ()) //piece is candidate in terms of area, not being the list and not previusly placed.
	  {
	    e_item = item[p].getEdges ();
	    //Compare each edge of the convex hull with each edge of the piece to see if there is a possible match and include the piece in the list.
	    for (int i = 0; i < (*e_ch).size () && !is_item_list; i++) //For each edge of the convex hull
	      {
		is_ed_sect = edge_of_section ((*e_ch)[i], sect);
		if (!is_ed_sect) //The edge to match is not in the edge of the bin.
		  {
		    for (int j = 0; j < (*e_item).size () && !is_item_list; j++) //For each edge of the piece
		      {
			double md = match_dist ((*e_ch)[i], (*e_item)[j]); //Calculate md
			if (md > 0.8) //if edges of convex hull and edges of piece are likely in lenght
			  {
			    list.push_back (&item[p]); //include piece in the list.
			    is_item_list = true;
			    p++;
			    break;
			  }
		      }
		  }
	      }
	    if (!is_item_list) //Item did not make it to the list, because edges are not of matching distance
	      p++; //try next piece.

	  }
	else
	  p++; //piece does not fit in terms of area, go to next piece.
      }
    return list;
  }

  //
  // match pieces
  //

  double
  SelectBestMatch (IRR_BIN &bin, vector<PIEZA*> list, PIEZA convex_hull,
		   int &best_e1, int &best_e2, double &best_d, int &best_p,
		   int &best_m)
  {
    // This function finds the best match between a set of pieces and all the
    // others in the bin. It uses ideas from EJORS paper (Han et al.)
    //
    PIEZA citem;
    bool is_ed_bin = false;
    double MaxUtil = -1;
    double dist = 0;
    bool is_sym = true;
    bool slide_feas = false;
    vector<EDGES> *e_ch = convex_hull.getEdges ();  //Edges of the convex hull.
    for (int p = 0; p < list.size (); p++) //For each piece in the list, find the best match
      {
	citem = *list[p];
	vector<EDGES> *e_citem = list[p]->getEdges ();	//edges of the piece
	for (int i = 0; i < (*e_ch).size (); i++)//for each edge on the convex hull
	  {
	    is_ed_bin = edge_of_section ((*e_ch)[i], bin);
	    if (!is_ed_bin)//The edge to match is not in the edge of the bin.
	      {
		//for(int m = 0; m<= 0; m++) //Rectangle instances, no mirror considered.
		for (int m = 0; m <= 1; m++)
		  {
		    for (int j = 0; j < (*e_citem).size (); j++)//for each edge of the piece
		      {
			citem = *list[p];//initialise citem so we do the rotations and traslations with the piece in its original position.
			if (m == 1) //Perform a reflection on piece item to check if the mirrored piece fits better.
			  {
			    is_sym = citem.set_mirror (true);
			  }
			if (m == 1 && is_sym)
			  continue; //Mirrorred piece is the same as not mirrrored. Already checked its position.
			double md = match_dist ((*e_ch)[i], (*e_citem)[j]); //Calculate md
			if ((*e_ch)[i].mod - (*e_citem)[j].mod > 0)
			  dist = (*e_ch)[i].mod - (*e_citem)[j].mod; //Calculate dist
			else
			  dist = 0;
			double slide = 0;
			slide_feas = false;
			if (md > HBS_THRES + HBS_TOL)
			  {
			    Attach (convex_hull, citem, i, j); //Attach edge j from piece to edge i of convex hull
			    for (double d = 0; d <= dist; d += slide_ep)
			      {
				if (slide_feas)
				  slide = slide_ep;
				else if (d != 0)
				  slide += slide_ep;
				slide_feas = Feasible_Slide_InSect (bin,
								    convex_hull,
								    citem, i, j,
								    slide);
				if (slide_feas) //Slide edge j from piece to edge i of convex hull only if feasible
				  {
				    double Util = convexhull_Utilization (
					convex_hull, citem);
				    //double Util = rectencl_Utilization(convex_hull, citem);
				    if (Util > MaxUtil + HBS_TOL) //If it is a good utilization of the new convex hull area, store best values
				      {
					MaxUtil = Util;
					best_d = d;
					best_e1 = i;
					best_e2 = j;
					best_m = m;
					best_p = p;
				      }
				  }
			      }
			  }
		      }
		  }

	      }
	  }

      }
    return MaxUtil;
  }


  //
  // last bin
  //

  void
  LastBinRefinementGE (vector<PIEZA> &pzas, BIN &sol)
  {
    double hor_util = (-1) * HBS_GRANDE;
    double ver_util = (-1) * HBS_GRANDE;
    BIN lastbin = sol; //Copy of last node
    //Calculate the horizontal utilization with the pieces in the original position
    double orig_hor_util = (-1);
    double orig_vert_util = (-1);
    vector<PIEZA> pzas_orig = pzas;

    for (int p = 0; p < pzas.size (); p++)
      {
	vector<PUNTO> pto = *pzas[p].obtener_puntos ();
	for (int i = 0; i < pto.size (); i++)
	  {
	    if (pto[i].coordy > orig_hor_util)
	      orig_hor_util = pto[i].coordy;
	    if (pto[i].coordx > orig_vert_util)
	      orig_vert_util = pto[i].coordx;
	  }
      }
    orig_hor_util = orig_hor_util / sol.getW ();
    orig_vert_util = orig_vert_util / sol.getL ();
    //    cout<<"\nRepacking bin: "<<sol.getID()<<"\n";

    vector<PIEZA> pzas_hor = pzas;
    sort (pzas_hor.begin (), pzas_hor.end (), orden_area);
    hor_util = ArrangeHorGE (pzas_hor, sol);
    if (hor_util == (-1) * HBS_GRANDE)
      {
	double maxheight = -1;
	for (int id = 0; id < sol.getNumSect (); id++)
	  {
	    bool is_feasible = true;
	    IRR_BIN sec = sol.get_ib (id);
	    PIEZA ch = create_convexhull_in_section (sec);
	    //					PIEZA ch = create_rectencl_in_section(sec); //Rectangle enclosure for the rectangle instances.

	    double slide = 0;
	    while (is_feasible)
	      {
		is_feasible = MoveDownInSect (ch, sec, slide);
		slide = 5;
	      }
	    for (int i = 0; i < (*ch.obtener_puntos ()).size (); i++)
	      {
		double p = (*ch.obtener_puntos ())[i].coordy;
		if (maxheight < p)
		  maxheight = (*ch.obtener_puntos ())[i].coordy;
	      }
	    if (equal_double (maxheight, sol.getW (), HBS_TOL))
	      break;
	  }
	hor_util = maxheight / sol.getW ();
	if (hor_util < 0)
	  hor_util = 1.0;
	if (hor_util > orig_hor_util)
	  {
	    hor_util = orig_hor_util;
	    pzas_hor = pzas_orig;
	  }
      }
    //    BIN lastbin_hor = sol;
    sol = lastbin;
    vector<PIEZA> pzas_vert = pzas;
    sort (pzas_vert.begin (), pzas_vert.end (), orden_area);
    ver_util = ArrangeVertGE (pzas_vert, sol);
    if (ver_util == (-1) * HBS_GRANDE)
      {
	double maxlength = -1;
	for (int id = 0; id < sol.getNumSect (); id++)
	  {
	    bool is_feasible = true;
	    IRR_BIN sec = sol.get_ib (id);
	    PIEZA ch = create_convexhull_in_section (sec);
	    //			PIEZA ch = create_rectencl_in_section(sec); //Rectangle enclosure for the rectangle instances.

	    double slide = 0;
	    while (is_feasible)
	      {
		is_feasible = MoveLeftInSect (ch, sec, slide);
		slide = 5;
	      }
	    for (int i = 0; i < (*ch.obtener_puntos ()).size (); i++)
	      {
		double p = (*ch.obtener_puntos ())[i].coordx;
		if (maxlength < p)
		  maxlength = (*ch.obtener_puntos ())[i].coordx;
	      }
	    if (equal_double (maxlength, sol.getL (), HBS_TOL))
	      break;
	  }
	ver_util = maxlength / sol.getL ();
	if (ver_util < 0)
	  ver_util = 1.0;
	if (ver_util > orig_vert_util)
	  {
	    ver_util = orig_vert_util;
	    pzas_vert = pzas_orig;
	  }

      }
    //    BIN lastbin_vert = sol;
    if (ver_util > 0 && ver_util < hor_util + HBS_TOL)
      {
	pzas = pzas_vert;
	//sol = lastbin_vert;
	sol.FixUtil (ver_util);

      }
    if (hor_util > 0 && hor_util < ver_util + HBS_TOL)
      {
	pzas = pzas_hor;
	//        sol = lastbin_hor;
	sol.FixUtil (hor_util);
      }
  }

  void
  LastBinRefinement (list<NODE> &tree)
  {
    list<NODE>::iterator it_node;
    it_node = tree.end ();
    it_node--;
    double hor_util = (-1) * HBS_GRANDE;
    double ver_util = (-1) * HBS_GRANDE;
    int last_level = it_node->get_level ();
    while (it_node->get_level () == last_level) //At last level
      {
	if ((it_node->get_IDdisp ()).empty ()) //If node is the last bin on a solution
	  {
	    NODE lastbin = *it_node; //Copy of last node
	    it_node->CopyPiecesInSect ();
	    //get pieces from last node
	    vector<PIEZA> pzas;
	    for (int i = 0; i < it_node->getPI ().size (); i++)
	      {
		PIEZA p = *(it_node->getPI ())[i];
		pzas.push_back (p);
	      }
	    //========================
	    sort (pzas.begin (), pzas.end (), orden_area);
	    hor_util = ArrangeHor (pzas, *it_node);
	    if (hor_util == (-1) * HBS_GRANDE)
	      {
		it_node->CopyPiecesInSect ();
		double maxheight = -1;
		for (int id = 0; id < it_node->getNumSect (); id++)
		  {
		    bool is_feasible = true;
		    IRR_BIN sec = it_node->get_ib (id);
		    PIEZA ch = create_convexhull_in_section (sec);
		    //					PIEZA ch = create_rectencl_in_section(sec); //Rectangle enclosure for the rectangle instances.

		    double slide = 0;
		    while (is_feasible)
		      {
			is_feasible = MoveDownInSect (ch, sec, slide);
			slide = 5;
		      }
		    for (int i = 0; i < (*ch.obtener_puntos ()).size (); i++)
		      {
			double p = (*ch.obtener_puntos ())[i].coordy;
			if (maxheight < p)
			  maxheight = (*ch.obtener_puntos ())[i].coordy;
		      }
		    if (equal_double (maxheight, it_node->getW (), HBS_TOL))
		      break;
		  }
		hor_util = maxheight / it_node->getW ();
		if (hor_util < 0)
		  hor_util = 1.0;
	      }
	    NODE lastbin_hor = *it_node;
	    *it_node = lastbin;
	    ver_util = ArrangeVert (pzas, *it_node);
	    if (ver_util == (-1) * HBS_GRANDE)
	      {
		it_node->CopyPiecesInSect ();
		double maxlength = -1;
		for (int id = 0; id < it_node->getNumSect (); id++)
		  {
		    bool is_feasible = true;
		    IRR_BIN sec = it_node->get_ib (id);
		    PIEZA ch = create_convexhull_in_section (sec);
		    //					PIEZA ch = create_rectencl_in_section(sec); //Rectangle enclosure for the rectangle instances.

		    double slide = 0;
		    while (is_feasible)
		      {
			is_feasible = MoveLeftInSect (ch, sec, slide);
			slide = 5;
		      }
		    for (int i = 0; i < (*ch.obtener_puntos ()).size (); i++)
		      {
			double p = (*ch.obtener_puntos ())[i].coordx;
			if (maxlength < p)
			  maxlength = (*ch.obtener_puntos ())[i].coordx;
		      }
		    if (equal_double (maxlength, it_node->getL (), HBS_TOL))
		      break;
		  }
		ver_util = maxlength / it_node->getL ();
		if (ver_util < 0)
		  ver_util = 1.0;
	      }
	    NODE lastbin_vert = *it_node;
	    if (ver_util > 0 && ver_util < hor_util + HBS_TOL)
	      {
		*it_node = lastbin_vert;
		it_node->FixUtil (ver_util);

	      }
	    if (hor_util > 0 && hor_util < ver_util + HBS_TOL)
	      {
		*it_node = lastbin_hor;
		it_node->FixUtil (hor_util);
	      }
	  }
	it_node--;
      }
  }


  //
  // irregular bins
  //

  IRR_BIN
  ConvertToIRRBIN (NODE &bin)
  {
    IRR_BIN ib;
    int ID = bin.getID ();
    ib.setBin (ID);
    ib.set_ID (0);
    PUNTO aux;
    //Add coordinates of bin in clockwise order
    aux.coordx = 0;
    aux.coordy = 0;
    ib.add_points (aux);
    aux.coordx = 0;
    aux.coordy = bin.getW ();
    ib.add_points (aux);
    aux.coordx = bin.getL ();
    aux.coordy = bin.getW ();
    ib.add_points (aux);
    aux.coordx = bin.getL ();
    aux.coordy = 0;
    ib.add_points (aux);
    //=======================================
    ib.setArea ();
    int np = bin.getNumPiezas ();
    for (int i = 0; i < np; i++)
      {
	PIEZA p = *(bin.getPI ())[i];
	ib.add_piece (*(bin.getPI ())[i]);
	ib.set_waste (*(bin.getPI ())[i]);
	ib.set_prop_used ();
      }
    ib.get_angles ();
    return ib;
  }

  IRR_BIN
  ConvertToIRRBIN (BIN &bin)
  {
    IRR_BIN ib;
    vector<PIEZA*> pzas;
    pzas = *bin.getPI ();
    int ID = bin.getID ();
    ib.setBin (ID);
    ib.set_ID (0);
    PUNTO aux;
    //Add coordinates of bin in clockwise order
    aux.coordx = 0;
    aux.coordy = 0;
    ib.add_points (aux);
    aux.coordx = 0;
    aux.coordy = bin.getW ();
    ib.add_points (aux);
    aux.coordx = bin.getL ();
    aux.coordy = bin.getW ();
    ib.add_points (aux);
    aux.coordx = bin.getL ();
    aux.coordy = 0;
    ib.add_points (aux);
    //=======================================
    ib.setArea ();
    for (int i = 0; i < pzas.size (); i++)
      {
	ib.add_piece (*pzas[i]);
	ib.set_waste (*pzas[i]);
	ib.set_prop_used ();
      }
    ib.get_angles ();
    return ib;
  }


  //
  // horizontal placement
  //

  double
  ArrangeHorGE (vector<PIEZA> &pzas, BIN &node)
  {
    double hor_util = (-1) * HBS_GRANDE;
    BIN c_node = node; //Copy of node, in case nothing gets modify we can retrieve it.
    c_node.empty_bin ();
    c_node.setID (node.getID ());
    double nodeW = node.getW ();
    double nodeL = node.getL ();
    //Pieces in original position
    for (int i = 0; i < pzas.size (); i++)
      {
	PUNTO origen;
	origen.coordy = 0.0;
	origen.coordx = 0.0;
	pzas[i].set_mirror (false);
	pzas[i].obtener_rotacion (0);
	pzas[i].setCoord (origen);
      }
    vector<PIEZA*> last_pzas;
    for (int i = 0; i < pzas.size (); i++)
      last_pzas.push_back (&pzas[i]);
    //==========================
    EDGES base_bin;
    base_bin.ini.coordx = node.getL ();
    base_bin.ini.coordy = 0.0;
    base_bin.fin.coordx = 0.0;
    base_bin.fin.coordy = 0.0;
    base_bin.set_mod ();
    double rot_angle = -1;
    double height_bm = -1; //Height of the convex hull of all pieces placed.
    double height_gc = -1; //Height of the highest piece when placed one next to the other
    double height = -1;
    // Place first piece with longest edge as base.

    //Falta comprobar si es mejor con la pieza reflejada.

    // First no mirrors.
    vector<EDGES> edges = *last_pzas[0]->getEdges ();
    int longest_edge = argmax_mod (edges);
    rot_angle = calculate_rotation_match (edges[longest_edge], base_bin);
    last_pzas[0]->obtener_rotacion (rot_angle);
    if (!last_pzas[0]->Fits_Bin (c_node.getL (), c_node.getW ())) //Piece does not fit horizontally.
      return hor_util;
    IRR_BIN ib_node = ConvertToIRRBIN (c_node);
    ib_node.set_ID (c_node.getID ());
    ib_node.add_piece (*last_pzas[0]);
    //Delete pza 0 from last_pzas
    height = last_pzas[0]->getw ();
    last_pzas.erase (last_pzas.begin ());
    //	double height_layer = -1;//Height of the highest piece when creating a new section by applying a horizontal guillotine cut
    while (!last_pzas.empty ()) //Not all the pieces have been placed.
      {
	int best_ec = -1; //Best edge of the ch
	int best_ep = -1; //Best edge of the piece
	int best_p_bm = -1; //Best piece from list
	int best_m = -1; // = 0 piece not mirrored
	double best_d = -1; // best slide distance.
	double best_rot = -1;
	int best_p_vc = -1;
	int best_i_vc = -1;
	EDGES vcg;
	PIEZA convex_hull = create_convexhull_in_section (ib_node);
	//PIEZA convex_hull = create_rectencl_in_section(ib_node); //Rectangle enclosure for the rectangle instances.

	height_bm = HorAligMatch (ib_node, last_pzas, convex_hull, best_ec,
				  best_ep, best_d, best_p_bm, best_m);
	if (height_gc < HBS_GRANDE)
	  height_gc = VertGuillCut (ib_node, last_pzas, convex_hull, nodeW,
				    nodeL, best_rot, best_p_vc, best_i_vc, vcg); //Devuelve la altura total si la pieza se coloca a la dcha del actual convex hull.
	if (height_bm == HBS_GRANDE && height_gc == HBS_GRANDE)
	  return hor_util; //Piece did not fit

	if (height_bm <= height_gc)
	  {
	    //Place using best match
	    height = height_bm;
	    if (best_m == 1)
	      {
		last_pzas[best_p_bm]->set_mirror (true);
	      }
	    Attach (convex_hull, *last_pzas[best_p_bm], best_ec, best_ep);
	    Feasible_Slide_InSect (ib_node, convex_hull, *last_pzas[best_p_bm],
				   best_ec, best_ep, best_d);
	    //Get the edges of the convex hull to include the guillotine cut.
	    vector<EDGES> ed_ch = *convex_hull.getEdges ();
	    ib_node.add_GC (ed_ch[best_ec]); //Include the guillotine cut in the section
	    ib_node.add_piece (*last_pzas[best_p_bm]); //Include the new piece in the current sect
	    last_pzas.erase (last_pzas.begin () + best_p_bm);
	  }
	else //Place using the guillotine cut.
	  {
	    height = height_gc;
	    last_pzas[best_p_vc]->obtener_rotacion (best_rot);
	    EDGES e_pza = (*last_pzas[best_p_vc]->getEdges ())[best_i_vc];
	    trans_piece_fin_ini (*last_pzas[best_p_vc], vcg, e_pza);
	    ib_node.add_piece (*last_pzas[best_p_vc]); //Include the new piece in the current sect
	    //ib_node.add_GC(vcg);
	    last_pzas.erase (last_pzas.begin () + best_p_vc);
	  }
      }
    hor_util = height / nodeW;
    //Copy pieces from ib_node to node;
    for (int p = 0; p < ib_node.get_pzas ()->size (); p++)
      {
	vector<PIEZA*> pz_sect = *ib_node.get_pzas ();
	c_node.include_piece (*pz_sect[p]);
	vector<EDGES> gc = *ib_node.get_ibGC ();
	for (int g = 0; g < gc.size (); g++)
	  c_node.add_GC (gc[g]);
      }
    node = c_node;
    return hor_util;
  }

  bool
  MoveDownInSect (PIEZA &ch, IRR_BIN &sec, double slide)
  {
    bool is_feas = true;
    //Move all points slide units down
    vector<EDGES> e_pza = *ch.getEdges ();
    for (int i = 0; i < e_pza.size (); i++)
      {
	e_pza[i].ini.coordy = e_pza[i].ini.coordy - slide;
	if (e_pza[i].ini.coordy < 0 - HBS_TOL) //Movement out of the bin.
	  return false;
      }
    //Check feasibility
    vector<PUNTO> ptos_Sec = *sec.get_ptos ();
    int last_pto = ptos_Sec.size () - 1;
    for (int i = 0; i < e_pza.size (); i++)
      {
	for (int j = 0; j < ptos_Sec.size () - 1; j++)
	  {
	    int side = position (ptos_Sec[j], ptos_Sec[j + 1], e_pza[i].ini);
	    if (side == 1)
	      return false;
	    //the point is to the left of the section (outside)
	  }
	//Last edge of section
	int side = position (ptos_Sec[last_pto], ptos_Sec[0], e_pza[i].ini);
	if (side == 1)
	  return false;
	//the point is to the left of the section (outside)
      }
    if (is_feas)
      {
	ch.translate (0, -slide); //Translate the convex hull
	for (int i = 0; i < sec.get_pzas ()->size (); i++)
	  {
	    PIEZA *pz = (*sec.get_pzas ())[i];
	    pz->translate (0, -slide); //Translate all the pieces in the section.
	  }
      }
    return is_feas;
  }

  double
  VertGuillCut (IRR_BIN &ib_node, vector<PIEZA*> list, PIEZA convex_hull,
		double node_w, double node_l, double &best_rot, int &best_p,
		int &best_i, EDGES &v_gc)
  {
    double MaxHeight = HBS_GRANDE;
    PIEZA item;
    double xmax = -1;
    double ymin = HBS_GRANDE;
    // Calculamos la coordenada más a la derecha de la envoltura convexa. En
    // caso de empate, nos quedamos con la más baja (?).
    vector<PUNTO> ch_ptos = *convex_hull.obtener_puntos ();
    for (int i = 0; i < ch_ptos.size (); i++)
      {
	if (ch_ptos[i].coordx > xmax)
	  xmax = ch_ptos[i].coordx;
	if (ch_ptos[i].coordy < ymin)
	  ymin = ch_ptos[i].coordy;
      }
    v_gc.ini.coordx = xmax;
    v_gc.ini.coordy = ymin;
    v_gc.fin.coordx = xmax;
    v_gc.fin.coordy = node_w;
    v_gc.set_mod ();
    for (int p = 0; p < list.size (); p++)
      {
	for (int i = 0; i < list[p]->getEdges ()->size (); i++) //for each edge on the piece
	  {
	    bool fit = true;
	    item = *list[p];
	    vector<EDGES> e_item = *item.getEdges (); //edges of the piece
	    double alpha = calculate_rotation_match (e_item[i], v_gc);
	    //Rotamos y trasladamos citem para coincida con el corte vertical.
	    item.obtener_rotacion (alpha);
	    e_item = *item.getEdges ();
	    trans_piece_fin_ini (item, v_gc, e_item[i]);
	    //Check if the piece is inside the bin.
	    for (int j = 0; j < (item.obtener_puntos ())->size (); j++)
	      {
		vector<PUNTO> i_ptos = *item.obtener_puntos ();
		if (i_ptos[j].coordx < 0 - HBS_TOL
		    || i_ptos[j].coordx > node_l + HBS_TOL
		    || i_ptos[j].coordy < 0 - HBS_TOL
		    || i_ptos[j].coordy > node_w + HBS_TOL)
		  {
		    item = *list[p]; //Piece does not fit in bin, back to original position.
		    fit = false;
		    break;
		  }
	      }
	    if (fit)
	      {
		//Keep rotation that minimizes height.
		double height;
		if (item.getw () < convex_hull.getw ())
		  height = convex_hull.getw ();
		else
		  height = item.getw ();
		if (height < MaxHeight)
		  {
		    MaxHeight = height;
		    best_rot = alpha;
		    best_p = p;
		    best_i = i;
		  }
	      }

	  }
      }

    return MaxHeight;
  }

  double
  ArrangeVert (vector<PIEZA> &pzas, NODE &node)
  {
    double vert_util = (-1) * HBS_GRANDE;
    NODE c_node = node; //Copy of node, in case nothing gets modify we can retrieve it.
    c_node.empty_bin ();
    c_node.setID (node.getID ());
    c_node.set_pred (*node.get_Pred ());
    double nodeW = node.getW ();
    double nodeL = node.getL ();
    //Pieces in original position
    for (int i = 0; i < pzas.size (); i++)
      {
	PUNTO origen;
	origen.coordy = 0.0;
	origen.coordx = 0.0;
	pzas[i].set_mirror (false);
	pzas[i].obtener_rotacion (0);
	pzas[i].setCoord (origen);
      }
    vector<PIEZA*> last_pzas;
    for (int i = 0; i < pzas.size (); i++)
      last_pzas.push_back (&pzas[i]);
    //==========================
    EDGES side_bin;
    side_bin.ini.coordx = 0.0;
    side_bin.ini.coordy = 0.0;
    side_bin.fin.coordx = 0.0;
    side_bin.fin.coordy = nodeW;
    side_bin.set_mod ();
    double rot_angle = -1;
    double length_bm = -1; //Height of the convex hull of all pieces placed.
    double length_gc = -1; //Height of the highest piece when placed one next to the other
    double length = -1;

    // Place first piece with longest edge as base.

    //Falta comprobar si es mejor con la pieza reflejada.

    // First no mirrors.
    vector<EDGES> edges = *last_pzas[0]->getEdges ();
    int longest_edge = argmax_mod (edges);
    rot_angle = calculate_rotation_match (edges[longest_edge], side_bin);
    last_pzas[0]->obtener_rotacion (rot_angle);
    if (!last_pzas[0]->Fits_Bin (c_node.getL (), c_node.getW ())) //Piece does not fit horizontally.
      return vert_util;
    IRR_BIN ib_node = ConvertToIRRBIN (c_node);
    ib_node.set_ID (c_node.getID ());
    ib_node.add_piece (*last_pzas[0]);
    //Delete pza 0 from last_pzas
    length = last_pzas[0]->getl ();
    last_pzas.erase (last_pzas.begin ());
    while (!last_pzas.empty ()) //Not all the pieces have been placed.
      {
	int best_ec = -1; //Best edge of the ch
	int best_ep = -1; //Best edge of the piece
	int best_p_bm = -1; //Best piece from list
	int best_m = -1; // = 0 piece not mirrored
	double best_d = -1; // best slide distance.
	double best_rot = -1;
	int best_p_hc = -1;
	int best_i_hc = -1;
	EDGES hcg;
	PIEZA convex_hull = create_convexhull_in_section (ib_node);
	//PIEZA convex_hull = create_rectencl_in_section(ib_node); //Rectangle enclosure for the rectangle instances.
	length_bm = VertAligMatch (ib_node, last_pzas, convex_hull, best_ec,
				   best_ep, best_d, best_p_bm, best_m);
	if (length_gc < HBS_GRANDE)
	  length_gc = HorGuillCut (ib_node, last_pzas, convex_hull, nodeW,
				   nodeL, best_rot, best_p_hc, best_i_hc, hcg); //Devuelve la altura total si la pieza se coloca a la dcha del actual convex hull.
	if (length_bm == HBS_GRANDE && length_gc == HBS_GRANDE)
	  return vert_util; //Piece did not fit

	if (length_bm <= length_gc)
	  {
	    //Place using best match
	    length = length_bm;
	    if (best_m == 1)
	      {
		last_pzas[best_p_bm]->set_mirror (true);
	      }
	    Attach (convex_hull, *last_pzas[best_p_bm], best_ec, best_ep);
	    Feasible_Slide_InSect (ib_node, convex_hull, *last_pzas[best_p_bm],
				   best_ec, best_ep, best_d);
	    //Get the edges of the convex hull to include the guillotine cut.
	    vector<EDGES> ed_ch = *convex_hull.getEdges ();
	    ib_node.add_GC (ed_ch[best_ec]); //Include the guillotine cut in the section
	    ib_node.add_piece (*last_pzas[best_p_bm]); //Include the new piece in the current sect
	    last_pzas.erase (last_pzas.begin () + best_p_bm);
	  }
	else //Place using the guillotine cut.
	  {
	    length = length_gc;
	    last_pzas[best_p_hc]->obtener_rotacion (best_rot);
	    EDGES e_pza = (*last_pzas[best_p_hc]->getEdges ())[best_i_hc];
	    trans_piece_ini_fin (*last_pzas[best_p_hc], hcg, e_pza);
	    ib_node.add_piece (*last_pzas[best_p_hc]); //Include the new piece in the current sect
	    //ib_node.add_GC(hcg);
	    last_pzas.erase (last_pzas.begin () + best_p_hc);
	  }
      }
    vert_util = length / nodeL;
    //Copy pieces from ib_node to node;
    for (int p = 0; p < ib_node.get_pzas ()->size (); p++)
      {
	vector<PIEZA*> pz_sect = *ib_node.get_pzas ();
	c_node.include_piece (*pz_sect[p]);
	vector<EDGES> gc = *ib_node.get_ibGC ();
	for (int g = 0; g < gc.size (); g++)
	  c_node.add_GC (gc[g]);
      }
    node = c_node;
    return vert_util;
  }

  double
  ArrangeHor (vector<PIEZA> &pzas, NODE &node)
  {
    double hor_util = (-1) * HBS_GRANDE;
    NODE c_node = node; //Copy of node, in case nothing gets modify we can retrieve it.
    c_node.empty_bin ();
    c_node.setID (node.getID ());
    c_node.set_pred (*node.get_Pred ());
    double nodeW = node.getW ();
    double nodeL = node.getL ();
    //Pieces in original position
    for (int i = 0; i < pzas.size (); i++)
      {
	PUNTO origen;
	origen.coordy = 0.0;
	origen.coordx = 0.0;
	pzas[i].set_mirror (false);
	pzas[i].obtener_rotacion (0);
	pzas[i].setCoord (origen);
      }
    vector<PIEZA*> last_pzas;
    for (int i = 0; i < pzas.size (); i++)
      last_pzas.push_back (&pzas[i]);
    //==========================
    EDGES base_bin;
    base_bin.ini.coordx = node.getL ();
    base_bin.ini.coordy = 0.0;
    base_bin.fin.coordx = 0.0;
    base_bin.fin.coordy = 0.0;
    base_bin.set_mod ();
    double rot_angle = -1;
    double height_bm = -1; //Height of the convex hull of all pieces placed.
    double height_gc = -1; //Height of the highest piece when placed one next to the other
    double height = -1;
    // Place first piece with longest edge as base.

    //Falta comprobar si es mejor con la pieza reflejada.

    // First no mirrors.
    vector<EDGES> edges = *last_pzas[0]->getEdges ();
    int longest_edge = argmax_mod (edges);
    rot_angle = calculate_rotation_match (edges[longest_edge], base_bin);
    last_pzas[0]->obtener_rotacion (rot_angle);
    if (!last_pzas[0]->Fits_Bin (c_node.getL (), c_node.getW ())) //Piece does not fit horizontally.
      return hor_util;
    IRR_BIN ib_node = ConvertToIRRBIN (c_node);
    ib_node.set_ID (c_node.getID ());
    ib_node.add_piece (*last_pzas[0]);
    //Delete pza 0 from last_pzas
    height = last_pzas[0]->getw ();
    last_pzas.erase (last_pzas.begin ());
    //	double height_layer = -1;//Height of the highest piece when creating a new section by applying a horizontal guillotine cut
    while (!last_pzas.empty ()) //Not all the pieces have been placed.
      {
	int best_ec = -1; //Best edge of the ch
	int best_ep = -1; //Best edge of the piece
	int best_p_bm = -1; //Best piece from list
	int best_m = -1; // = 0 piece not mirrored
	double best_d = -1; // best slide distance.
	double best_rot = -1;
	int best_p_vc = -1;
	int best_i_vc = -1;
	EDGES vcg;
	PIEZA convex_hull = create_convexhull_in_section (ib_node);
	//PIEZA convex_hull = create_rectencl_in_section(ib_node); //Rectangle enclosure for the rectangle instances.

	height_bm = HorAligMatch (ib_node, last_pzas, convex_hull, best_ec,
				  best_ep, best_d, best_p_bm, best_m);
	if (height_gc < HBS_GRANDE)
	  height_gc = VertGuillCut (ib_node, last_pzas, convex_hull, nodeW,
				    nodeL, best_rot, best_p_vc, best_i_vc, vcg); //Devuelve la altura total si la pieza se coloca a la dcha del actual convex hull.
	if (height_bm == HBS_GRANDE && height_gc == HBS_GRANDE)
	  return hor_util; //Piece did not fit

	if (height_bm <= height_gc)
	  {
	    //Place using best match
	    height = height_bm;
	    if (best_m == 1)
	      {
		last_pzas[best_p_bm]->set_mirror (true);
	      }
	    Attach (convex_hull, *last_pzas[best_p_bm], best_ec, best_ep);
	    Feasible_Slide_InSect (ib_node, convex_hull, *last_pzas[best_p_bm],
				   best_ec, best_ep, best_d);
	    //Get the edges of the convex hull to include the guillotine cut.
	    vector<EDGES> ed_ch = *convex_hull.getEdges ();
	    ib_node.add_GC (ed_ch[best_ec]); //Include the guillotine cut in the section
	    ib_node.add_piece (*last_pzas[best_p_bm]); //Include the new piece in the current sect
	    last_pzas.erase (last_pzas.begin () + best_p_bm);
	  }
	else //Place using the guillotine cut.
	  {
	    height = height_gc;
	    last_pzas[best_p_vc]->obtener_rotacion (best_rot);
	    EDGES e_pza = (*last_pzas[best_p_vc]->getEdges ())[best_i_vc];
	    trans_piece_fin_ini (*last_pzas[best_p_vc], vcg, e_pza);
	    ib_node.add_piece (*last_pzas[best_p_vc]); //Include the new piece in the current sect
	    //ib_node.add_GC(vcg);
	    last_pzas.erase (last_pzas.begin () + best_p_vc);
	  }
      }
    hor_util = height / nodeW;
    //Copy pieces from ib_node to node;
    for (int p = 0; p < ib_node.get_pzas ()->size (); p++)
      {
	vector<PIEZA*> pz_sect = *ib_node.get_pzas ();
	c_node.include_piece (*pz_sect[p]);
	vector<EDGES> gc = *ib_node.get_ibGC ();
	for (int g = 0; g < gc.size (); g++)
	  c_node.add_GC (gc[g]);
      }
    node = c_node;
    return hor_util;
  }

  double
  HorAligMatch (IRR_BIN &bin, vector<PIEZA*> list, PIEZA convex_hull,
		int &best_e1, int &best_e2, double &best_d, int &best_p,
		int &best_m)
  {
    //This function finds the best match between a set of pieces and all the others in the bin.
    //It uses ideas from EJORS paper (Han et al.)
    PIEZA citem;
    bool is_ed_bin = false;
    double MaxHeight = HBS_GRANDE;
    double dist = 0;
    //bool matched = false;
    bool is_sym = true;
    bool slide_feas = false;
    vector<EDGES> *e_ch = convex_hull.getEdges ();  //Edges of the convex hull.
    for (int p = 0; p < list.size (); p++) //For each piece in the list, find the best match
      {
	citem = *list[p];
	vector<EDGES> *e_citem = list[p]->getEdges ();	//edges of the piece
	for (int i = 0; i < (*e_ch).size (); i++)//for each edge on the convex hull
	  {
	    is_ed_bin = edge_of_section ((*e_ch)[i], bin);
	    if (!is_ed_bin)//The edge to match is not in the edge of the bin.
	      {
		for (int m = 0; m <= 1; m++)
		  {
		    for (int j = 0; j < (*e_citem).size (); j++)//for each edge of the piece
		      {
			citem = *list[p];//initialise citem so we do the rotations and traslations with the piece in its original position.
			if (m == 1) //Perform a reflection on piece item to check if the mirrored piece fits better.
			  {
			    is_sym = citem.set_mirror (true);
			  }
			if (m == 1 && is_sym)
			  continue; //Mirrorred piece is the same as not mirrrored. Already checked its position.
			double md = match_dist ((*e_ch)[i], (*e_citem)[j]); //Calculate md
			if ((*e_ch)[i].mod - (*e_citem)[j].mod > 0)
			  dist = (*e_ch)[i].mod - (*e_citem)[j].mod; //Calculate dist
			else
			  dist = 0;
			double slide = 0;
			slide_feas = false;
			if (md > 0 - HBS_TOL)
			  {
			    Attach (convex_hull, citem, i, j); //Attach edge j from piece to edge i of convex hull
			    for (double d = 0; d <= dist; d += slide_ep)
			      {
				if (slide_feas)
				  slide = slide_ep;
				else if (d != 0)
				  slide += slide_ep;
				slide_feas = Feasible_Slide_InSect (bin,
								    convex_hull,
								    citem, i, j,
								    slide);
				if (slide_feas) //Slide edge j from piece to edge i of convex hull only if feasible
				  {
				    double Height = convexhull_Height (
					convex_hull, citem);
				    //double Height = rectencl_Height(convex_hull, citem);

				    if (Height < MaxHeight - HBS_TOL)
				      {
					//matched = true;
					MaxHeight = Height;
					best_d = d;
					best_e1 = i;
					best_e2 = j;
					best_m = m;
					best_p = p;
				      }
				  }
			      }
			  }
		      }
		  }

	      }
	  }

      }
    return MaxHeight;
  }


  //
  // vertical placement
  //

  double
  ArrangeVertGE (vector<PIEZA> &pzas, BIN &node)
  {
    double vert_util = (-1) * HBS_GRANDE;
    BIN c_node = node; //Copy of node, in case nothing gets modify we can retrieve it.
    c_node.empty_bin ();
    c_node.setID (node.getID ());
    double nodeW = node.getW ();
    double nodeL = node.getL ();
    //Pieces in original position
    for (int i = 0; i < pzas.size (); i++)
      {
	PUNTO origen;
	origen.coordy = 0.0;
	origen.coordx = 0.0;
	pzas[i].set_mirror (false);
	pzas[i].obtener_rotacion (0);
	pzas[i].setCoord (origen);
      }
    vector<PIEZA*> last_pzas;
    for (int i = 0; i < pzas.size (); i++)
      last_pzas.push_back (&pzas[i]);
    //==========================
    EDGES side_bin;
    side_bin.ini.coordx = 0.0;
    side_bin.ini.coordy = 0.0;
    side_bin.fin.coordx = 0.0;
    side_bin.fin.coordy = nodeW;
    side_bin.set_mod ();
    double rot_angle = -1;
    // Place first piece with longest edge as base.

    //Falta comprobar si es mejor con la pieza reflejada.

    // First no mirrors.
    vector<EDGES> edges = *last_pzas[0]->getEdges ();
    int longest_edge = argmax_mod (edges);
    rot_angle = calculate_rotation_match (edges[longest_edge], side_bin);
    last_pzas[0]->obtener_rotacion (rot_angle);
    if (!last_pzas[0]->Fits_Bin (c_node.getL (), c_node.getW ())) //Piece does not fit horizontally.
      return vert_util;
    IRR_BIN ib_node = ConvertToIRRBIN (c_node);
    ib_node.set_ID (c_node.getID ());
    ib_node.add_piece (*last_pzas[0]);
    //Delete pza 0 from last_pzas
    last_pzas.erase (last_pzas.begin ());
    double length_bm = -1; //Height of the convex hull of all pieces placed.
    double length_gc = -1; //Height of the highest piece when placed one next to the other
    double length = -1;
    while (!last_pzas.empty ()) //Not all the pieces have been placed.
      {
	int best_ec = -1; //Best edge of the ch
	int best_ep = -1; //Best edge of the piece
	int best_p_bm = -1; //Best piece from list
	int best_m = -1; // = 0 piece not mirrored
	double best_d = -1; // best slide distance.
	double best_rot = -1;
	int best_p_hc = -1;
	int best_i_hc = -1;
	EDGES hcg;
	PIEZA convex_hull = create_convexhull_in_section (ib_node);
	//PIEZA convex_hull = create_rectencl_in_section(ib_node); //Rectangle enclosure for the rectangle instances.
	length_bm = VertAligMatch (ib_node, last_pzas, convex_hull, best_ec,
				   best_ep, best_d, best_p_bm, best_m);
	if (length_gc < HBS_GRANDE)
	  length_gc = HorGuillCut (ib_node, last_pzas, convex_hull, nodeW,
				   nodeL, best_rot, best_p_hc, best_i_hc, hcg); //Devuelve la altura total si la pieza se coloca a la dcha del actual convex hull.
	if (length_bm == HBS_GRANDE && length_gc == HBS_GRANDE)
	  return vert_util; //Piece did not fit

	if (length_bm <= length_gc)
	  {
	    //Place using best match
	    length = length_bm;
	    if (best_m == 1)
	      {
		last_pzas[best_p_bm]->set_mirror (true);
	      }
	    Attach (convex_hull, *last_pzas[best_p_bm], best_ec, best_ep);
	    Feasible_Slide_InSect (ib_node, convex_hull, *last_pzas[best_p_bm],
				   best_ec, best_ep, best_d);
	    //Get the edges of the convex hull to include the guillotine cut.
	    vector<EDGES> ed_ch = *convex_hull.getEdges ();
	    ib_node.add_GC (ed_ch[best_ec]); //Include the guillotine cut in the section
	    ib_node.add_piece (*last_pzas[best_p_bm]); //Include the new piece in the current sect
	    last_pzas.erase (last_pzas.begin () + best_p_bm);
	  }
	else //Place using the guillotine cut.
	  {
	    length = length_gc;
	    last_pzas[best_p_hc]->obtener_rotacion (best_rot);
	    EDGES e_pza = (*last_pzas[best_p_hc]->getEdges ())[best_i_hc];
	    trans_piece_ini_fin (*last_pzas[best_p_hc], hcg, e_pza);
	    ib_node.add_piece (*last_pzas[best_p_hc]); //Include the new piece in the current sect
	    //ib_node.add_GC(hcg);
	    last_pzas.erase (last_pzas.begin () + best_p_hc);
	  }
      }
    vert_util = length / nodeL;
    //Copy pieces from ib_node to node;
    for (int p = 0; p < ib_node.get_pzas ()->size (); p++)
      {
	vector<PIEZA*> pz_sect = *ib_node.get_pzas ();
	c_node.include_piece (*pz_sect[p]);
	vector<EDGES> gc = *ib_node.get_ibGC ();
	for (int g = 0; g < gc.size (); g++)
	  c_node.add_GC (gc[g]);
      }
    node = c_node;
    return vert_util;
  }

  bool
  MoveLeftInSect (PIEZA &ch, IRR_BIN &sec, double slide)
  {
    bool is_feas = true;
    //Move all points slide units down
    vector<EDGES> e_pza = *ch.getEdges ();
    for (int i = 0; i < e_pza.size (); i++)
      {
	e_pza[i].ini.coordx = e_pza[i].ini.coordx - slide;
	if (e_pza[i].ini.coordx < 0 - HBS_TOL) //Movement out of the bin.
	  return false;
      }
    //Check feasibility
    vector<PUNTO> ptos_Sec = *sec.get_ptos ();
    int last_pto = ptos_Sec.size () - 1;
    for (int i = 0; i < e_pza.size (); i++)
      {
	for (int j = 0; j < ptos_Sec.size () - 1; j++)
	  {
	    int side = position (ptos_Sec[j], ptos_Sec[j + 1], e_pza[i].ini);
	    if (side == 1)
	      return false;
	    //the point is to the left of the section (outside)
	  }
	//Last edge of section
	int side = position (ptos_Sec[last_pto], ptos_Sec[0], e_pza[i].ini);
	if (side == 1)
	  return false;
	//the point is to the left of the section (outside)
      }
    if (is_feas)
      {
	ch.translate (-slide, 0); //Translate the convex hull
	for (int i = 0; i < sec.get_pzas ()->size (); i++)
	  {
	    PIEZA *pz = (*sec.get_pzas ())[i];
	    pz->translate (-slide, 0); //Translate all the pieces in the section.
	  }
      }
    return is_feas;
  }

  double
  VertAligMatch (IRR_BIN &bin, vector<PIEZA*> list, PIEZA convex_hull,
		 int &best_e1, int &best_e2, double &best_d, int &best_p,
		 int &best_m)
  {
    // This function finds the best match between a set of pieces and all the
    // others in the bin. It uses ideas from EJORS paper (Han et al.)
    PIEZA citem;
    bool is_ed_bin = false;
    double MaxLength = HBS_GRANDE;
    double dist = 0;
    //bool matched = false;
    bool is_sym = true;
    bool slide_feas = false;
    vector<EDGES> *e_ch = convex_hull.getEdges ();  //Edges of the convex hull.
    for (int p = 0; p < list.size (); p++) //For each piece in the list, find the best match
      {
	citem = *list[p];
	vector<EDGES> *e_citem = list[p]->getEdges ();	//edges of the piece
	for (int i = 0; i < (*e_ch).size (); i++)//for each edge on the convex hull
	  {
	    is_ed_bin = edge_of_section ((*e_ch)[i], bin);
	    if (!is_ed_bin)//The edge to match is not in the edge of the bin.
	      {
		for (int m = 0; m <= 1; m++)
		  {
		    for (int j = 0; j < (*e_citem).size (); j++)//for each edge of the piece
		      {
			citem = *list[p];//initialise citem so we do the rotations and traslations with the piece in its original position.
			if (m == 1) //Perform a reflection on piece item to check if the mirrored piece fits better.
			  {
			    is_sym = citem.set_mirror (true);
			  }
			if (m == 1 && is_sym)
			  continue; //Mirrorred piece is the same as not mirrrored. Already checked its position.
			double md = match_dist ((*e_ch)[i], (*e_citem)[j]); //Calculate md
			if ((*e_ch)[i].mod - (*e_citem)[j].mod > 0)
			  dist = (*e_ch)[i].mod - (*e_citem)[j].mod; //Calculate dist
			else
			  dist = 0;
			double slide = 0;
			slide_feas = false;
			if (md > 0 - HBS_TOL)
			  {
			    Attach (convex_hull, citem, i, j); //Attach edge j from piece to edge i of convex hull
			    for (double d = 0; d <= dist; d += slide_ep)
			      {
				if (slide_feas)
				  slide = slide_ep;
				else if (d != 0)
				  slide += slide_ep;
				slide_feas = Feasible_Slide_InSect (bin,
								    convex_hull,
								    citem, i, j,
								    slide);
				if (slide_feas) //Slide edge j from piece to edge i of convex hull only if feasible
				  {
				    double Length = convexhull_Length (
					convex_hull, citem);
				    //double Length = rectencl_Length(convex_hull, citem);
				    if (Length < MaxLength - HBS_TOL)
				      {
					//matched = true;
					MaxLength = Length;
					best_d = d;
					best_e1 = i;
					best_e2 = j;
					best_m = m;
					best_p = p;
				      }
				  }
			      }
			  }
		      }
		  }

	      }
	  }

      }
    return MaxLength;
  }

  double
  HorGuillCut (IRR_BIN &ib_node, vector<PIEZA*> list, PIEZA convex_hull,
	       double node_w, double node_l, double &best_rot, int &best_p,
	       int &best_i, EDGES &h_gc)
  {
    double MaxLength = HBS_GRANDE;
    PIEZA item;
    double xmin = HBS_GRANDE;
    double ymax = -1;
    // Calculamos la coordenada más arriba de la envoltura convexa. En caso de
    // empate, nos quedamos con la más a la izqda (?).
    vector<PUNTO> ch_ptos = *convex_hull.obtener_puntos ();
    for (int i = 0; i < ch_ptos.size (); i++)
      {
	if (ch_ptos[i].coordx < xmin)
	  xmin = ch_ptos[i].coordx;
	if (ch_ptos[i].coordy > ymax)
	  ymax = ch_ptos[i].coordy;
      }
    h_gc.fin.coordx = xmin;
    h_gc.fin.coordy = ymax;
    h_gc.ini.coordx = node_l;
    h_gc.ini.coordy = ymax;
    h_gc.set_mod ();
    for (int p = 0; p < list.size (); p++)
      {
	for (int i = 0; i < list[p]->getEdges ()->size (); i++) //for each edge on the piece
	  {
	    bool fit = true;
	    item = *list[p];
	    vector<EDGES> e_item = *item.getEdges (); //edges of the piece
	    double alpha = calculate_rotation_match (e_item[i], h_gc);
	    //Rotamos y trasladamos citem para coincida con el corte vertical.
	    item.obtener_rotacion (alpha);
	    e_item = *item.getEdges ();
	    trans_piece_ini_fin (item, h_gc, e_item[i]);
	    //Check if the piece is inside the bin.
	    for (int j = 0; j < (item.obtener_puntos ())->size (); j++)
	      {
		vector<PUNTO> i_ptos = *item.obtener_puntos ();
		if (i_ptos[j].coordx < 0 - HBS_TOL
		    || i_ptos[j].coordx > node_l + HBS_TOL
		    || i_ptos[j].coordy < 0 - HBS_TOL
		    || i_ptos[j].coordy > node_w + HBS_TOL)
		  {
		    item = *list[p]; //Piece does not fit in bin, back to original position.
		    fit = false;
		    break;
		  }
	      }
	    if (fit)
	      {
		//Keep rotation that minimizes length.
		double length;
		if (item.getl () < convex_hull.getl ())
		  length = convex_hull.getl ();
		else
		  length = item.getl ();
		if (length < MaxLength)
		  {
		    MaxLength = length;
		    best_rot = alpha;
		    best_p = p;
		    best_i = i;
		  }
	      }

	  }
      }

    return MaxLength;
  }

} /* namespace homogeneous_bs */
