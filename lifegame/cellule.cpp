#include "cellule.h"
#include <fstream>
#include <iostream>
using namespace std;

cellule::cellule(string etat)
{
	etat_ = etat;
}

void cellule::setEtat(string etat)
{
	etat_ = etat;
}

void cellule::save(ofstream &os) const
{ 
	os << etat_<< endl;
}

