#include "CImg.h"
#include  "cellule.h"
#include <vector>
using namespace std;
using namespace cimg_library;

class Board
{
	vector <vector <cellule>> grille;
	int num[25][25];
	bool close = false;
public:
	Board();
	bool getClose()	{ return close; }
	void initialisation();
	void r_initialisation();
	void c_initialisation();
	void rule();
	void num_neighbour();
	void afficher();
	void save() const;
	void load();
	void savei();
	void loadi();
};