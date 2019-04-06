#include "Board.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace cimg_library;

unsigned char
color_alive[3] = { 0, 0, 255 },
color_dead[3] = { 255, 0, 0 },
color_birth[3] = { 0, 255, 0 },
color_blanc[3] = {255,255,255},
color_grid[3] = { 0, 0, 0 },
color_display[3] = { 200, 150, 60 };

Board::Board()
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
			num[i][j] = 0;
	}
}

void Board::initialisation()
{
	int z = 0;
	cout << "Please click on the position where you would like to set a cell." << endl;
	cout << "When you finish your initialisation, just click on Enter to cintinue." << endl;

	close = false;
	//definir le grid q'on va dessiner
	CImg <unsigned char> grid(1000, 750, 1, 3, 255);
	for (int i = 1; i < 25; i++)
		grid.draw_line(0, 30 * i, 750, 30 * i, color_grid);
	for (int j = 1; j < 26; j++)
		grid.draw_line(30 * j, 0, 30 * j, 750, color_grid);
	//grid.draw_circle(890, 400, 100, color_display);
	grid.draw_rectangle(795,360,990,440,color_display);
	grid.draw_text(840, 380, "PLAY", color_blanc, color_display, 1, 50);
	//grid.draw_circle(890, 700, 100, color_display);
	//grid.draw_rectangle(795, 660, 990, 740, color_display);
	//grid.draw_text(840, 680, "MENU", color_blanc, color_display, 1, 50);
	//grid.draw_circle(890, 100, 100, color_display);
	grid.draw_rectangle(795, 60, 990, 140, color_display);
	grid.draw_text(840, 80, "HELP", color_blanc, color_display, 1, 50);
	CImgDisplay disp(grid, "Life_Game", 0, false, false);

	disp.move((CImgDisplay::screen_width() - disp.width()) / 2, (CImgDisplay::screen_height() - disp.height()) / 2);//bouge la fenetre au centre d'ecran

	CImg <unsigned char> scene = grid;

	grille.resize(25);
	for (int i = 0; i < 25; i++) grille[i].resize(25); //initialiser la taille du tableau grille
	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 25; j++)
			grille[i][j].setEtat("aucun");

		while (!disp.is_keyENTER() && !(disp.button() & 1 && disp.mouse_x() >= 795 && disp.mouse_x() <= 990 && disp.mouse_y() >= 360 && disp.mouse_y() <= 440))//entrer dans l'etat suivant
	{
		scene.display(disp);
		if (disp.button() & 1 && disp.mouse_y()< 750 && disp.mouse_x()<750)// Detecter la souris est bien dans le plan de grille
		{
			int i = 25 * disp.mouse_y() / disp.height();
			int j = 25 * disp.mouse_x() / 750;
			
			//dessiner les cellules initialises et modifier leur etats
			scene.draw_circle(15 + j * 30, 15 + i * 30, 5, color_alive);
			grille[i][j].setEtat("alive");
		}
		
		if (disp.button() & 1 && disp.mouse_x() >= 795 && disp.mouse_x() <= 990 && disp.mouse_y() >= 60 && disp.mouse_y() <= 140 && z==0)
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
			cout << "The alive cells are in blue, the dead cells are in red, the born cells are in yellow" << endl << endl;
			z++;
		}
		if (disp.is_keyESC())
		{
			close = true;
			disp.close();
			//disp.set_key(53U, true);
		}
		/*
		if (disp.button() & 1 && disp.mouse_x() >= 795 && disp.mouse_x() <= 990 && disp.mouse_y() >= 660 && disp.mouse_y() <= 740)
		{
			disp.close();
			close = true;
		}
		*/
	}	
}

void Board::r_initialisation()
{
	close = false;
	srand((unsigned)time(NULL));
	grille.resize(25);
	for (int i = 0; i < 25; i++) {
		grille[i].resize(25);
	}
	for (int i = 0; i < 25;i++)
		for (int j = 0; j < 25; j++)
			grille[i][j].setEtat("aucun");
	int hauteur, largeur;
	hauteur = grille[0].size();
	largeur = grille.size();
		for (int i = 0; i < hauteur; i++)
		{
			for (int j = 0; j < largeur; j++)
			{
				if (rand()%2)
				{
					grille[i][j].setEtat("alive");
				}
			}
		}
}

void Board::c_initialisation()
{
	close = false;
	cout << "You can choose an intialistion which is already set: " << endl;
	cout << "1.blinker 2.beacon 3.toad 4.pulsar 5.pentadecathlon" << endl;
	int a;
	cin >> a;
	switch (a)
	{
	case 1:
	{
			  ifstream ifs("blinker.txt");
			  if (ifs.is_open()){
				  grille.clear();	//supprimer les cellules existant

				  // resize la grille
				  grille.resize(25);
				  for (int i = 0; i < 25; i++) {
					  grille[i].resize(25);
				  }

				  ifs.ignore();
				  string text;
				  for (int i = 0; i < 25; i++)
				  for (int j = 0; j < 25; j++)
				  {
					  ifs >> text;
					  grille[i][j].setEtat(text);
				  }
			  }
			  else cout << "failed to load the display" << endl;
			  ifs.close();
			  break;
	}
	case 2:
	{
			  ifstream ifs("beacon.txt");
			  if (ifs.is_open()){
				  grille.clear();	//supprimer les cellules existant

				  // resize la grille
				  grille.resize(25);
				  for (int i = 0; i < 25; i++) {
					  grille[i].resize(25);
				  }

				  ifs.ignore();
				  string text;
				  for (int i = 0; i < 25; i++)
				  for (int j = 0; j < 25; j++)
				  {
					  ifs >> text;
					  grille[i][j].setEtat(text);
				  }
			  }
			  else cout << "failed to load the display" << endl;
			  ifs.close();
			  break;
	}
	case 3:
	{
			  ifstream ifs("toad.txt");
			  if (ifs.is_open()){
				  grille.clear();	//supprimer les cellules existant

				  // resize la grille
				  grille.resize(25);
				  for (int i = 0; i < 25; i++) {
					  grille[i].resize(25);
				  }

				  ifs.ignore();
				  string text;
				  for (int i = 0; i < 25; i++)
				  for (int j = 0; j < 25; j++)
				  {
					  ifs >> text;
					  grille[i][j].setEtat(text);
				  }
			  }
			  else cout << "failed to load the display" << endl;
			  ifs.close();
			  break;
	}
	case 4:
	{
			  ifstream ifs("pulsar.txt");
			  if (ifs.is_open()){
				  grille.clear();	//supprimer les cellules existant

				  // resize la grille
				  grille.resize(25);
				  for (int i = 0; i < 25; i++) {
					  grille[i].resize(25);
				  }

				  ifs.ignore();
				  string text;
				  for (int i = 0; i < 25; i++)
				  for (int j = 0; j < 25; j++)
				  {
					  ifs >> text;
					  grille[i][j].setEtat(text);
				  }
			  }
			  else cout << "failed to load the display" << endl;
			  ifs.close();
			  break;
	}
	default:
		ifstream ifs("pentadecathlon.txt");
		if (ifs.is_open()){
			grille.clear();	//supprimer les cellules existant

			// resize la grille
			grille.resize(25);
			for (int i = 0; i < 25; i++) {
				grille[i].resize(25);
			}

			ifs.ignore();
			string text;
			for (int i = 0; i < 25; i++)
			for (int j = 0; j < 25; j++)
			{
				ifs >> text;
				grille[i][j].setEtat(text);
			}
		}
		else cout << "failed to load the display" << endl;
		ifs.close();
		break;
	}
}

void Board::rule()
{
	//partie pour decider si la cellule va etre mort, ne ou reste vivant
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			//pour une grille blanc
			if (grille[i][j].getEtat() == "aucun" )
			{
				if (num[i][j] == 3)
					grille[i][j].setEtat("birth");
			}

			//pour une cellule deja vivant
			else if (grille[i][j].getEtat() == "alive" || grille[i][j].getEtat() == "birth")
			{
				if (num[i][j] == 2 || num[i][j] == 3)
					grille[i][j].setEtat("alive");
				else if (num[i][j] < 2 || num[i][j] > 3)
					grille[i][j].setEtat("dead");
			}

			//pour une cellue qui est morte
			else if (grille[i][j].getEtat() == "dead")
			{
				if (num[i][j] == 3)
					grille[i][j].setEtat("birth");
				else grille[i][j].setEtat("aucun");
			}
		}
	}
}

void Board::num_neighbour()
{
	int count=0;
	int i = 0, j = 0;
	for (i = 0;i< 25;i++)
	{
		for (j = 0;j < 25; j++)
		{
			count = 0;
			//pour la positon (0,0)
			if (i == 0 && j == 0)
			{
				if (grille[i][j + 1].getEtat() == "alive" || grille[i][j + 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j + 1].getEtat() == "alive" || grille[i + 1][j + 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j].getEtat() == "alive" || grille[i + 1][j].getEtat() == "birth")
					count++;

			}

			//pour les position (24,0) 
			else if (i == 24 && j == 0)
			{
				if (grille[i][j + 1].getEtat() == "alive" || grille[i][j + 1].getEtat() == "birth")
					count++;
				if (grille[i - 1][j + 1].getEtat() == "alive" || grille[i - 1][j + 1].getEtat() == "birth")
					count++;
				if (grille[i - 1][j].getEtat() == "alive" || grille[i - 1][j].getEtat() == "birth")
					count++;

			}

			//pour la position (24,24) 
			else if (i == 24 && j == 24)
			{
				if (grille[i][j - 1].getEtat() == "alive" || grille[i][j - 1].getEtat() == "birth")
					count++;
				if (grille[i - 1][j - 1].getEtat() == "alive" || grille[i - 1][j - 1].getEtat() == "birth")
					count++;
				if (grille[i - 1][j].getEtat() == "alive" || grille[i - 1][j].getEtat() == "birth")
					count++;

			}

			//pour la position (0,24) 
			else if (i == 0 && j == 24)
			{
				if (grille[i][j - 1].getEtat() == "alive" || grille[i][j - 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j - 1].getEtat() == "alive" || grille[i + 1][j - 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j].getEtat() == "alive" || grille[i + 1][j].getEtat() == "birth")
					count++;

			}

			//pour les position (1,0) a (23,0)
			else if (j == 0)
			{
				if (grille[i - 1][j].getEtat() == "alive" || grille[i - 1][j].getEtat() == "birth")
					count++;
				if (grille[i - 1][j + 1].getEtat() == "alive" || grille[i - 1][j + 1].getEtat() == "birth")
					count++;
				if (grille[i][j + 1].getEtat() == "alive" || grille[i][j + 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j + 1].getEtat() == "alive" || grille[i + 1][j + 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j].getEtat() == "alive" || grille[i + 1][j].getEtat() == "birth")
					count++;

			}

			

			//pour les positions (24,1) a (24,23)
			else if (i == 24)
			{
				if (grille[i][j - 1].getEtat() == "alive" || grille[i][j - 1].getEtat() == "birth")
					count++;
				if (grille[i - 1][j - 1].getEtat() == "alive" || grille[i - 1][j - 1].getEtat() == "birth")
					count++;
				if (grille[i - 1][j].getEtat() == "alive" || grille[i - 1][j].getEtat() == "birth")
					count++;
				if (grille[i - 1][j + 1].getEtat() == "alive" || grille[i - 1][j + 1].getEtat() == "birth")
					count++;
				if (grille[i][j + 1].getEtat() == "alive" || grille[i][j + 1].getEtat() == "birth")
					count++;

			}

			//pour les positions (1,24) a (23,24)
			else if (j == 24)
			{
				if (grille[i - 1][j].getEtat() == "alive" || grille[i - 1][j].getEtat() == "birth")
					count++;
				if (grille[i - 1][j - 1].getEtat() == "alive" || grille[i - 1][j - 1].getEtat() == "birth")
					count++;
				if (grille[i][j - 1].getEtat() == "alive" || grille[i][j - 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j - 1].getEtat() == "alive" || grille[i + 1][j - 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j].getEtat() == "alive" || grille[i + 1][j].getEtat() == "birth")
					count++;

			}

			

			//pour les positions (0,1) a (0,23)
			else if (i == 0)
			{
				if (grille[i][j - 1].getEtat() == "alive" || grille[i][j - 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j - 1].getEtat() == "alive" || grille[i + 1][j - 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j].getEtat() == "alive" || grille[i + 1][j].getEtat() == "birth")
					count++;
				if (grille[i + 1][j + 1].getEtat() == "alive" || grille[i + 1][j + 1].getEtat() == "birth")
					count++;
				if (grille[i][j + 1].getEtat() == "alive" || grille[i][j + 1].getEtat() == "birth")
					count++;

			}

			//pour les autre positions
			else if (i > 0 && i < 24 && j>0 && j<24)
			{
				if (grille[i][j - 1].getEtat() == "alive" || grille[i][j - 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j - 1].getEtat() == "alive" || grille[i + 1][j - 1].getEtat() == "birth")
					count++;
				if (grille[i - 1][j - 1].getEtat() == "alive" || grille[i - 1][j - 1].getEtat() == "birth")
					count++;
				if (grille[i + 1][j].getEtat() == "alive" || grille[i + 1][j].getEtat() == "birth")
					count++;
				if (grille[i - 1][j].getEtat() == "alive" || grille[i - 1][j].getEtat() == "birth")
					count++;
				if (grille[i + 1][j + 1].getEtat() == "alive" || grille[i + 1][j + 1].getEtat() == "birth")
					count++;
				if (grille[i][j + 1].getEtat() == "alive" || grille[i][j + 1].getEtat() == "birth")
					count++;
				if (grille[i - 1][j + 1].getEtat() == "alive" || grille[i - 1][j + 1].getEtat() == "birth")
					count++;
				
			}
			num[i][j] = count;
		}
	}
}


void Board::afficher()
{
	int z = 0;
	//definir le grid q'on va dessiner
	CImg <unsigned char> grid(1000, 750, 1, 3, 255);
	for (int i = 1; i < 25; i++)
		grid.draw_line(0, 30 * i, 750, 30 * i, color_grid);
	for (int j = 1; j < 26; j++)
		grid.draw_line(30 * j, 0, 30 * j, 750, color_grid);

	//definir les boutons d interface utilisateur
	grid.draw_rectangle(795, 360, 990, 440, color_display);
	grid.draw_text(840, 380, "PLAY", color_blanc, color_display, 1, 50);
	//grid.draw_circle(890, 700, 100, color_display);
	grid.draw_rectangle(795, 660, 990, 740, color_display);
	grid.draw_text(840, 680, "MENU", color_blanc, color_display, 1, 50);
	//grid.draw_circle(890, 100, 100, color_display);
	grid.draw_rectangle(795, 60, 990, 140, color_display);
	grid.draw_text(840, 80, "HELP", color_blanc, color_display, 1, 50);

	CImgDisplay disp(grid, "Life_Game", 0, false, false);


	disp.move((CImgDisplay::screen_width() - disp.width()) / 2, (CImgDisplay::screen_height() - disp.height()) / 2);//bouge la fenetre au centre d'ecran

	CImg <unsigned char> scene = grid;
	while (!disp.is_keyENTER() && !(disp.button() & 1 && disp.mouse_x() >= 795 && disp.mouse_x() <= 990 && disp.mouse_y() >= 360 && disp.mouse_y() <= 440))
	{	
		scene.display(disp);
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (grille[i][j].getEtat() == "alive")
				{
					scene.draw_circle(15 + j * 30, 15 + i * 30, 5, color_alive);
				}
				else if (grille[i][j].getEtat() == "dead")
				{
					scene.draw_circle(15 + j * 30, 15 + i * 30, 5, color_dead);
				}
				else if (grille[i][j].getEtat() == "birth")
				{
					scene.draw_circle(15 + j * 30, 15 + i * 30, 5, color_birth);
				}
				else if (grille[i][j].getEtat() == "aucun")
				{
					scene.draw_circle(15 + j * 30, 15 + i * 30, 5, color_blanc);
				}
			}
			
			
				
		}
		
		if (disp.button() & 1 && disp.mouse_x() >= 795 && disp.mouse_x() <= 990 && disp.mouse_y() >= 60 && disp.mouse_y() <= 140 && z == 0)
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
			cout << "The alive cells are in blue, the dead cells are in red, the born cells are in yellow" << endl << endl;

					z++;
				}
		if (disp.button() & 1 && disp.mouse_x() >= 795 && disp.mouse_x() <= 990 && disp.mouse_y() >= 660 && disp.mouse_y() <= 740)
		{
			disp.close();
			close = true;
		}
		if (disp.is_keyESC())
		{
			close = true;
			disp.close();
			//disp.set_key(53U, true);
		}
		
	}

}

void Board::save() const
{
	ofstream ofs("save.txt");
	if (ofs.is_open())
	{
		for (int i = 0; i < 25; i++)
		for (int j = 0; j < 25; j++)
			grille[i][j].save(ofs);
	}
	else cout << "failed to save the display" << endl;
	ofs.close();
}

void Board::load()
{
	close = false;
	cout << "Would you like to load the initial play or the latest play?" << endl;
	cout << "1-The initial play   2-The latest play (we take the initial play by default)" << endl;
	int z = 1;
	cin >> z;
	if (z == 2)
	{
		ifstream ifs("save.txt");
		if (ifs.is_open()){
			grille.clear();	//supprimer les cellules existant

			// resize la grille
			grille.resize(25);
			for (int i = 0; i < 25; i++) {
				grille[i].resize(25);
			}

			ifs.ignore();
			string text;
			for (int i = 0; i < 25; i++)
			for (int j = 0; j < 25; j++)
			{
				ifs >> text;
				grille[i][j].setEtat(text);
			}
		}
		else cout << "failed to load the display" << endl;
		ifs.close();
	}
	else
	{
		ifstream ifs("savei.txt");
		if (ifs.is_open()){
			grille.clear();	//supprimer les cellules existant

			// resize la grille
			grille.resize(25);
			for (int i = 0; i < 25; i++) {
				grille[i].resize(25);
			}

			ifs.ignore();
			string text;
			for (int i = 0; i < 25; i++)
			for (int j = 0; j < 25; j++)
			{
				ifs >> text;
				grille[i][j].setEtat(text);
			}
		}
		else cout << "failed to load the display" << endl;
		ifs.close();
	}
}

void Board::savei()
{
	ofstream ofs("savei.txt");
	if (ofs.is_open())
	{
		for (int i = 0; i < 25; i++)
		for (int j = 0; j < 25; j++)
			grille[i][j].save(ofs);
	}
	else cout << "failed to save the display" << endl;
	ofs.close();
}