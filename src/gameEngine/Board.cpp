/*!
 * \file Board.cpp
 * \brief Implémentation de la classe Board
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards
#include <Vector>

// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Board.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"


using namespace PolyBomber;

void Board::generateBoard(int nbPlayer, int nbBonus, int nbBox) {
	generateWall();
	generatePlayer(nbPlayer);
	generateBonus(nbBonus);
	generateBox(nbBox);
}

void Board::generateWall() {
	int x;
	int y;
	
	for (x=0; x<19; x++) {
		for (y=0; y<13; y++) {
			if (x%2==1 && y%2==1) {
				//this->mur.push_back(new Wall());
				//TODO : A corriger
			}
		}
	}
}

void Board::generatePlayer(int nbPlayer) {
	/*switch (nbPlayer) {
		case 2:
			Location l1 = new Location(caseToPixel(0),caseToPixel(0));
			Location l2 = new Location(caseToPixel(18),caseToPixel(12));
			Player pl1 = new Player(l1);
			Player pl2 = new Player(l2);
			this->addLocation(pl1);
			this->addLocation(pl2);
			break;
			
		case 3:
			Location l3 = new Location(caseToPixel(0),caseToPixel(0));
			Location l4 = new Location(caseToPixel(18),caseToPixel(0));
			Location l5 = new Location(caseToPixel(9),caseToPixel(12));
			Player pl3 = new Player(l3);
			Player pl4 = new Player(l4);
			Player pl5 = new Player(l5);
			this->addLocation(pl3);
			this->addLocation(pl4);
			this->addLocation(pl5);
			//un joueur en haut à gauche(0,0) et un joueur en haut à droite(19,0) et un joueur en bas au milieu(10,13)
			break;
			
		case 4:
			Location l6 = new Location(caseToPixel(0),caseToPixel(0));
			Location l7 = new Location(caseToPixel(18),caseToPixel(0));
			Location l8 = new Location(caseToPixel(18),caseToPixel(12));
			Location l9 = new Location(caseToPixel(0),caseToPixel(12));
			Player pl6 = new Player(l6);
			Player pl7 = new Player(l7);
			Player pl8 = new Player(l8);
			Player pl9 = new Player(l9);
			this->addLocation(pl6);
			this->addLocation(pl7);
			this->addLocation(pl8);
			this->addLocation(pl9);
			//un joueur en haut à gauche(0,0) et un joueur en bas à droite(19,13) et un joueur en haut à droite(19,0) et un joueur en bas à gauche(0,13)
			break;
			
		default:
			//nothing
			break;
	}*/
}

void Board::generateBonus(int nbBonus) {
	for (int i=0; i<nbBonus; i++) {
		//définir deux nombre aléatoire définissant des coordonnées où on peut mettre des bonus et les mettre sachant qu'il faut un "L" autour des joueurs
	}
}

void Board::generateBox(int nbBox) {
	for (int i=0; i<nbBox; i++) {
		//définir deux nombre aléatoire définissant des coordonnées où on peut mettre des boites et les mettre sachant qu'il faut un "L" autour des joueurs
	}
}