//
//  nodes.cpp
//  BS_Ideas
//
//  Created by Marta Cabo Nodar on 07/05/15.
//  Copyright (c) 2015 Marta Cabo. All rights reserved.
//

#include "classes_BPGC.hpp"

// ============================================================================
// Funciones asociadas a la clase NODE.
// ============================================================================

void
NODE::setID (int id)
{
  ID = id;
} //Crea el ID del bin

int
NODE::getID ()
{
  return ID;
} //Recupera el ID del bin

double
NODE::getL ()
{
  return L;
}

double
NODE::getW ()
{
  return W;
}

void
NODE::setWaste (PIEZA &p)
{
  waste = waste - p.getArea ();

} //calcula el area libre

double
NODE::get_waste ()
{
  return waste;
} //Devuelve el área libre.

void
NODE::setPropUtil ()
{
  prop_utilizada = 1 - waste / (L * W);
} //Calcula la proporción de bin utilizada

double
NODE::getPropUtil ()
{
  return prop_utilizada;

}
int
NODE::getNumPiezas ()
{
  return num_piezas;
}

void
NODE::setOpen (bool op)
{
  bin_open = op;
}

bool
NODE::getOpen ()
{
  return bin_open;
}

void
NODE::setDim (const string &name_sol)
{
  char cadena[128];
  ifstream p_file (name_sol);
  if (!p_file.is_open ())
    {
      cout << "ERROR: Unable to open " << name_sol << " file\n";
      exit (1);
    }

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
NODE::include_piece (PIEZA p)
{
  //Incluimos pieza p en el bin (i.e. aumentamos en uno el número de piezas e incluimos la pieza en el vector piezas_incluidas.
  piezas_incluidas[num_piezas] = p;
  num_piezas++;
  //Actualizar waste;
  setWaste (p);
  setPropUtil ();
  p.setbin (ID);
  p.set_placed (ID);
  //Actualizamos el vector de piezas disponibles para el nodo.
  if (!ID_pzas_disp.empty ())
    update_pzas_disp (p.getID ());
}

vector<PIEZA*>
NODE::getPI ()
{
  vector<PIEZA*> p;
  for (int i = 0; i < num_piezas; i++)
    p.push_back (&piezas_incluidas[i]);
  return (p); //Raro que funcione según Toni.. Veremos que hace.
}

void
NODE::empty_bin ()
{
  for (int i = 0; i < num_piezas; i++)
    {
      piezas_incluidas[i].setID (-1);
      piezas_incluidas[i].setbin (-1);
      piezas_incluidas[i].set_mirror (false);
      piezas_incluidas[i].set_placed (false);
    }
  num_piezas = 0;
  ID = -1;
  //L_used = 0;
  //W_used = 0;
  waste = L * W;
  prop_utilizada = 0;
  //piezas_incluidas.clear();
  section.clear ();
  GC.clear ();
  ID_pzas_disp.clear ();
  num_sect = 0;
  bin_open = true;
  predecessor = nullptr;
}

void
NODE::initialize_node (double stock_length, double stock_width, int ID)
{
  this->ID = ID;
  this->L = stock_length;
  this->W = stock_width;

  num_piezas = 0;
  waste = L * W;
  prop_utilizada = 0;
  bin_open = true;
  num_sect = 0;
  for (int i = 0; i < 30; i++)
    {
      piezas_incluidas[i].setID (-1);
      piezas_incluidas[i].setbin (-1);
    }
}

void
NODE::add_GC (EDGES e)
{
  e.mod = -1;
  GC.insert (GC.begin (), e);
}

vector<EDGES> *
NODE::getGC ()
{
  return (&GC);
}

void
NODE::add_IB (IRR_BIN &ib)
{
  num_sect++;
  section.push_back (ib);
}

int
NODE::getNumSect ()
{
  return num_sect;
}

void
NODE::update_section (IRR_BIN &ib) //This function adds the pieces that are included in the irregular bin but not in the section of the bin.
{
  vector<PIEZA*> *pi = ib.get_pzas ();	//pieces in the irregular bin
  int i = 0;
  while (ib.getID () != section[i].getID ())
    i++;	//We are now in the section of the bin that correspond to ib.

  vector<PIEZA*>::iterator it_pib, it_pb;
  it_pib = pi->begin ();	//Iterator to the pieces in the irregular bin
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

void
NODE::update_ptos_sect (IRR_BIN &ib)
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
NODE::add_piece_SectToBin (IRR_BIN &ib)
{
  vector<PIEZA*> pi = *ib.get_pzas ();	//pieces in the section of the bin
  PIEZA *last = pi.back ();
  //Add the last piece from the section of the bin, to the bin.
  include_piece (*last);

}
IRR_BIN
NODE::get_ib (int IDib)
{
  int i = 0;
  while (section[i].getID () != IDib)
    i++;
  return section[i];
}

//Funciones asociadas al NODO como nodo, no como objeto bin

void
NODE::set_pred (NODE &pred)
{
  predecessor = &pred;
}

void
NODE::set_ID_pzas_disp (vector<PIEZA> &pz)
{
  for (int i = 0; i < pz.size (); i++)
    {
      if (!pz[i].is_placed ())
	ID_pzas_disp.push_back (pz[i].getID ());
    }
}

vector<int>
NODE::get_IDdisp ()
{
  return ID_pzas_disp;
}
void
NODE::update_pzas_disp (int ID)
{
  int pos = 0;
  while (pos < ID_pzas_disp.size () && ID_pzas_disp[pos] != ID)
    pos++;
  ID_pzas_disp.erase (ID_pzas_disp.begin () + pos);
}

NODE*
NODE::get_Pred ()
{
  return predecessor;
}

void
NODE::set_level (int i)
{
  level = i;
}
int
NODE::get_level ()
{
  return level;
}

void
NODE::set_globaleval (double of)
{
  global_eval = of;
}

double
NODE::get_globaleval ()
{
  return global_eval;
}

void
NODE::FixUtil (double util)
{
  prop_utilizada = util;
}

void
NODE::CopyPiecesInSect ()
{
  int pos = 0;
  for (int s = 0; s < num_sect; s++)	//For each section
    {
      for (int p = 0; p < section[s].get_pzas ()->size (); p++)	//For each piece in section
	{
	  vector<PIEZA*> *pzas_sec = section[s].get_pzas ();
	  (*pzas_sec)[p] = &piezas_incluidas[p + pos];
	}
      pos = pos + section[s].get_pzas ()->size ();
    }
}
