//  bin.cpp
//  GuillotineCuts
//
//  Created by Marta Cabo Nodar on 24/10/14.
//  Copyright (c) 2014 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"
//Funciones asociadas a la clase BIN.
//===================================
void
BIN::setID (int id)
{
  ID = id;
} //Crea el ID del bin

int
BIN::getID ()
{
  return ID;
} //Recupera el ID del bin

double
BIN::getL ()
{
  return L;
}

double
BIN::getW ()
{
  return W;
}

void
BIN::setWaste (PIEZA &p)
{
  waste = waste - p.getArea ();

} //calcula el area libre

double
BIN::get_waste ()
{
  return waste;
} //Devuelve el área libre. 

void
BIN::setPropUtil ()
{
  prop_utilizada = 1 - waste / (L * W);
} //Calcula la proporción de bin utilizada

double
BIN::getPropUtil ()
{
  return prop_utilizada;

}
int
BIN::getNumPiezas ()
{
  return num_piezas;
}

void
BIN::setOpen (bool op)
{
  bin_open = op;
}

bool
BIN::getOpen ()
{
  return bin_open;
}

void
BIN::setDim (const string &name_sol)
{
  char cadena[128];
  ifstream p_file (name_sol);
  p_file >> cadena;
  while (!p_file.eof ())
    {
      sscanf (cadena, "%lf", &L);
      p_file >> cadena;
      sscanf (cadena, "%lf", &W);
      p_file >> cadena;
    }
}

void
BIN::include_piece (PIEZA &p)
{
  //Incluimos pieza p en el bin (i.e. aumentamos en uno el número de piezas e incluimos la pieza en el vector piezas_incluidas. 
  piezas_incluidas.push_back (&p);
  num_piezas++;
  //Actualizar largo y ancho utilizado y waste;
  setWaste (p);
  setPropUtil ();
  p.setbin (ID);
  p.set_placed (ID);
}

vector<PIEZA*> *
BIN::getPI ()
{
  return (&piezas_incluidas);
}

void
BIN::empty_bin ()
{
  num_piezas = 0;
  ID = -1;
  //L_used = 0;
  //W_used = 0;
  waste = L * W;
  prop_utilizada = 0;
  piezas_incluidas.clear ();
  section.clear ();
  GC.clear ();
}

void
BIN::initialize_bin (double stock_length, double stock_width, int ID)
{
  this->ID = ID;
  this->L = stock_length;
  this->W = stock_width;

  num_piezas = 0;
  waste = L * W;
  prop_utilizada = 0;
  bin_open = true;
  num_sect = 0;
}

void
BIN::add_GC (EDGES e)
{
  e.mod = -1;
  GC.insert (GC.begin (), e);
}

vector<EDGES> *
BIN::getGC ()
{
  return (&GC);
}

void
BIN::add_IB (IRR_BIN &ib)
{
  num_sect++;
  section.push_back (ib);
}
;

int
BIN::getNumSect ()
{
  return num_sect;
}

void
BIN::update_section (IRR_BIN ib) //This function adds the pieces that are included in the irregular bin but not in the section of the bin.
{
  vector<PIEZA*> pi = *ib.get_pzas ();	//pieces in the irregular bin
  int i = 0;
  while (ib.getID () != section[i].getID ())
    i++;	//We are now in the section of the bin that correspond to ib.

  vector<PIEZA*>::iterator it_pib, it_pb;
  it_pib = pi.begin ();	//Iterator to the pieces in the irregular bin
  vector<PIEZA*> *ps = section[i].get_pzas ();
  it_pb = ps->begin ();	//Iterator to the pieces in the section of the bin
  while ((*it_pib)->getID () == (*it_pb)->getID ())
    {
      it_pib++;
      it_pb++;
      if (it_pb == ps->end ())
	break;	//Si llega al final, no sigue
    }
  //Add the last piece from the irregular bin, to the section of the bin.
  ps->push_back (*it_pib);

}
;

void
BIN::update_ptos_sect (IRR_BIN ib)
{
  int i = 0;
  while (ib.getID () != section[i].getID ())
    i++;	//We are now in the section of the bin that correspond to ib.
  vector<PUNTO> *ptos_sect = section[i].get_ptos ();
  ptos_sect->clear ();	//delete the points in the section
  vector<PUNTO> *ptos_new = ib.get_ptos ();
  for (int j = 0; j < ptos_new->size (); j++)
    ptos_sect->push_back ((*ptos_new)[j]);
  //Update area
  section[i].setArea ();
  //Update Angles
  vector<double> angles = section[i].get_angles ();
}

void
BIN::add_piece_SectToBin (IRR_BIN ib)
{
  vector<PIEZA*> pi = *ib.get_pzas ();	//pieces in the section of the bin
  PIEZA *last = pi.back ();
  //Add the last piece from the section of the bin, to the bin.
  include_piece (*last);

}

IRR_BIN
BIN::get_ib (int IDib)
{
  int i = 0;
  while (section[i].getID () != IDib)
    i++;
  return section[i];
}
void
BIN::FixUtil (double util)
{
  prop_utilizada = util;
}

//===============================================
//Funciones asociadas a la clase IRR_BIN
//===============================================
void
IRR_BIN::set_ID (int i)
{
  ID = i;
}
int
IRR_BIN::getID ()
{
  return ID;
}
;

void
IRR_BIN::setBin (int b)
{
  binID = b;
}

void
IRR_BIN::setArea ()
{
  area_ib = calcular_area_exacta (ib_ptos);
  //reverse ptos, dado que la función anterior está diseñada para polígonos en sentido antihorario, por lo que en este caso hace un reverse de los ptos. 
  std::reverse (ib_ptos.begin (), ib_ptos.end ());

}

double
IRR_BIN::getArea ()
{
  return area_ib;
}

void
IRR_BIN::set_waste (PIEZA &p)
{
  double area_p = p.getArea ();
  waste_ib = area_ib - area_p;
}
double
IRR_BIN::get_waste ()
{
  return waste_ib;
}
double
IRR_BIN::get_prop_used ()
{
  return prop_used;
}

void
IRR_BIN::set_prop_used ()
{
  prop_used = 1 - waste_ib / area_ib;
}

int
IRR_BIN::getBin ()
{
  return binID;
}

void
IRR_BIN::add_points (PUNTO &pto)
{
  ib_ptos.push_back (pto);
}

vector<PUNTO> *
IRR_BIN::get_ptos ()
{
  return &ib_ptos;
}
;

vector<PIEZA*> *
IRR_BIN::get_pzas ()
{
  return (&ib_pzas);
}

void
IRR_BIN::add_GC (EDGES &e)
{
  ib_GC.push_back (e);
}

vector<EDGES> *
IRR_BIN::get_ibGC ()
{
  return (&ib_GC);
}

void
IRR_BIN::add_piece (PIEZA &pza)
{
  //Incluimos pieza p en el bin (i.e. aumentamos en uno el número de piezas e incluimos la pieza en el vector piezas_incluidas.
  ib_pzas.push_back (&pza);
  //Actualizar largo y ancho utilizado y waste;
  set_waste (pza);
  set_prop_used ();
}

void
IRR_BIN::empty_irrbin ()
{
  ID = -1;
  binID = -1;
  prop_used = 0;
  ib_pzas.clear ();
  ib_ptos.clear ();
  ib_angles.clear ();
  ib_GC.clear ();
}

vector<double>
IRR_BIN::get_angles ()
{
  vector<EDGES> ar;
  EDGES aux;
  int last = ib_ptos.size ();
  //Create edges of IRRBIN
  for (int i = 0; i < last; i++)
    {
      aux.ini = ib_ptos[i];
      if (i + 1 != last)
	aux.fin = ib_ptos[i + 1];
      else
	aux.fin = ib_ptos[0];
      aux.set_mod ();
      ar.push_back (aux);
    }
  ib_angles = calculateInnerAngles (ar);
  return ib_angles;
}

////=========================================================
////Funciones asociadas a la clase POLYGON
////=========================================================
//void POLYGON::setID(int p)
//{
//	ID = p;
//}
//
//int POLYGON::getID()
//{
//	return ID;
//	
//};
//
//void POLYGON::clear_bp()
//{
//	ID = -1;
//	bp_points.clear();
//	
//}
//void POLYGON::add_points(PUNTO pt)
//{
//	bp_points.push_back(pt);
//}
//
//vector<PUNTO> POLYGON::get_ptos()
//{
//	return bp_points;
//}
//
//void POLYGON::set_bin(int b)
//{
//	bin = b;
//}
//
//void POLYGON:: set_area()
//{
//	bp_area = calcular_area_exacta(bp_points);
//};//Asigna el area del BP
//
//void add_piece(PIEZA &p);
//void add_GC(EDGES e);
//void include_in_bin(int bin_id);//Include pieces and guillotine cuts from the irregular bin into the bin