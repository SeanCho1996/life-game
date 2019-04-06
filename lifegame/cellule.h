#include<fstream>
#include<iostream>
#include<string>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

class cellule
{
	string etat_;
public:
	cellule(string etat = "aucun");
	string &getEtat() { return(etat_); }
	void setEtat(string etat);
	void save(ofstream &os) const;

};