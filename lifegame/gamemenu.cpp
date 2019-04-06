#include <iostream>
#include <cstdlib>
#include "gamemenu.h"

using namespace std;


ExempleMenu::ExempleMenu(Board &s)  : Menu("Welcome to the life game of  Conway : (we recommand you to read the instructions first, by choosing 0!)")
{
  x = &s;
  ajouterOption("aide","display the help");
  ajouterOption("play","execute to play the game");
  ajouterOption("save", "save the current display");
  ajouterOption("load", "load a saved display");
  ajouterOption("quit","quit the application");
}

void ExempleMenu::executerOption(const string &nom,bool &fin)
{
	if (nom == "play") play();
	else if (nom == "save") save();
	else if (nom == "load") load();
	else Menu::executerOption(nom, fin);
}

void ExempleMenu::play()
{
	cout << "Would like to initialise the first scene by yourself,  a random initialistion or an already set initialisaton?" << endl;
	cout << "1-I'd like to do it myself.  2-I'd like a random initialisation.   3.-I'd like an already set initialisation." << endl << endl;
	
	int i = 0;
	cin >> i;

	cout << "Press enter or click on button 'play' to display the next status" << endl;
	cout << "Press ESC then press enter to leave the game" << endl;

		if (i == 1)
		{
			x->initialisation();
			x->savei();
			while (x->getClose() == false){
				x->num_neighbour();
				x->rule();
				x->afficher();
			};
			
		}
		else if (i == 2)
		{
			x->r_initialisation();
			x->afficher();
			x->savei();
		
			while (x->getClose() == false){
				x->num_neighbour();
				x->rule();
				x->afficher();
			};
		
		}
		else if (i == 3)
		{
			x->c_initialisation();
			x->afficher();
			x->savei();

			while (x->getClose() == false){
				x->num_neighbour();
				x->rule();
				x->afficher();
			} ;

		}
		else
		{
			cout << "Enter wrong! Please enter a number of 1 or 2!" << endl;
		}

	system("pause");
}

void ExempleMenu::save()
{
	x->save();
	cout << "save complete" << endl;
	system("pause");
}

void ExempleMenu::load()
{
	x->load();
	cout << "load complete" << endl;
	x->afficher();
	do{
		x->num_neighbour();
		x->rule();
		x->afficher();
	} while (x->getClose() == false);
}



