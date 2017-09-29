//
//  Dibujar.cpp
//  GuillotineCuts
//
//  Created by Marta Cabo Nodar on 30/10/14.
//  Copyright (c) 2014 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"
NUMERO
redondear_numero_dos_cifras (double num);

void
dibujar_bins (vector<BIN> &bins, char *instance, char *name, double t, double L,
	      double W, int escalado)
{
  char filename[80];
  FILE *p_file;

  char name_inst[100];
  //sprintf (name_inst,"_tikzpicture_iter_%d.tex",p_datos->iter);
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
      sprintf (cadena, "\\draw[color=black] (-2,%d.%d%d) -- (%d.%d%d,%d.%d%d);",
	       nn.parte_entera, nn.decimal_1, nn.decimal_2, nn1.parte_entera,
	       nn1.decimal_1, nn1.decimal_2, nn2.parte_entera, nn2.decimal_1,
	       nn2.decimal_2);
      fprintf (p_file, "\t %s \n", cadena);
      cadena[0] = '\0';

      nn = redondear_numero_dos_cifras (L);
      nn1 = redondear_numero_dos_cifras (L);
      nn2 = redondear_numero_dos_cifras (W);
      sprintf (cadena, "\\draw[color=black] (%d.%d%d,-2) -- (%d.%d%d,%d.%d%d);",
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
		  nn.parte_entera, nn.decimal_1, nn.decimal_2, nn1.parte_entera,
		  nn1.decimal_1, nn1.decimal_2, nn2.parte_entera, nn2.decimal_1,
		  nn2.decimal_2, nn3.parte_entera, nn3.decimal_1,
		  nn3.decimal_2);
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

//(vector<NODE> &node, char *instance, char *name, double t,
//	       double L, double W, int escalado)

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
      sprintf (cadena, "\\clip(-3,-3) rectangle (%.2lf,%.2lf);", L + 3, W + 3);
      fprintf (p_file, "\t %s \n", cadena);
      cadena[0] = '\0';

      nn = redondear_numero_dos_cifras (W);
      nn1 = redondear_numero_dos_cifras (L);
      nn2 = redondear_numero_dos_cifras (W);
      sprintf (cadena, "\\draw[color=black] (-2,%.2lf) -- (%.2lf,%.2lf);", W, L,
	       W);
      fprintf (p_file, "\t %s \n", cadena);
      cadena[0] = '\0';

      nn = redondear_numero_dos_cifras (L);
      nn1 = redondear_numero_dos_cifras (L);
      nn2 = redondear_numero_dos_cifras (W);
      sprintf (cadena, "\\draw[color=black] (%.2lf,-2) -- (%.2lf,%.2lf);", L, L,
	       W);
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
