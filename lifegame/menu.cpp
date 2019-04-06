#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "menu.h"

using namespace std;

// Definition des methodes de la classe OptionMenu

OptionMenu::OptionMenu(const string &nom,const string &description)
  : nom_(nom), description_(description)
{
}


// Definition des methodes de la classe Menu

Menu::Menu(const string & titre) : titre_(titre)
{
}

void Menu::setTitre(const string &titre)
{
  titre_=titre;
}

void Menu::ajouterOption(const string &nom,const string &description)
{
  listeOptions_.push_back(OptionMenu(nom,description));
}


void Menu::afficherMenu()
{
  cout<<titre_<<endl;
  for (int i=0;i<listeOptions_.size();i++) {
    cout<<"- "<<setw(2)<<i<<" : "<<listeOptions_[i].getDescription()<<endl;
  }
}

int Menu::demanderChoix()
{
  int choix;
  cout<<"Your choice : ";
  cin>>choix;
  cout<<endl;
  return choix;
}

void Menu::executer()
{
  bool fin=false;
  while(!fin) {
    system("cls");
    afficherMenu();
    int choix=demanderChoix();
    if (choix>=0 && choix<listeOptions_.size())
      executerOption(listeOptions_[choix].getNom(),fin);
    else {
      cout<<"Choice incorrect"<<endl;
      system("pause");
    }
  }
}

void Menu::executerOption(const string &nom,bool &fin)
{
  fin=false;
  if (nom=="quit") fin=quitter();
  else if (nom=="aide") aide();
  else {
    cout<<"Option dpesn't exist"<<endl;
    system("pause");
    }
}

bool Menu::quitter()
{
  bool fin=false;
  char reponse;
  cout<<"Do you really want to quit the game (o/n) ?";
  cin>>reponse;
  if ((reponse=='o')||(reponse=='O')||(reponse=='0')) fin=true;
  return fin;
}

void Menu::aide()
{
	cout << "To play the game, just choose 1, and click enter." << endl;
	cout << "If you'd like to initialise the first scene by yourself, choose 1," << endl;
	cout << "if you'd like a random intialisation, choose 2," << endl;
	cout << "if you'd like an already set intialisation, choose 3," << endl;
	cout << "Click on 'play' button or Enter to refresh and see the next status," << endl;
	cout << "click on 'menu' and then Enter to quit to the main menu," << endl;
	cout << "click on 'help' to read this insrtuction again." << endl << endl;
	cout << "The rule of the game is :" << endl;
	cout << "For one cell in the center, if it has 2 or 3 neighbours alive, it'll be alive in the next status," << endl;
	cout << "for a blank space, if it has exactly 3 neighbours alive, there will be a cell born" << endl;
	cout << "in all the other cases, the cell in the center will die." << endl;
	cout << "The alive cells are in blue, the dead cells are in red, the born cells are in yellow." << endl << endl;
  system("pause");
}



