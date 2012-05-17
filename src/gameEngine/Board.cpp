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

using namespace PolyBomber;

void vector<Cell> Board::caseLibreAdjacente(sf::Vector2<int> location, int portee) {
	
}

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
	switch (nbPlayer) {
		case 2:
			//un joueur en haut à gauche(0,0) et un joueur en bas à droite (19,13)
			break;
			
		case 3:
			//un joueur en haut à gauche(0,0) et un joueur en haut à droite(19,0) et un joueur en bas au milieu(10,13)
			break;
			
		case 4:
			//un joueur en haut à gauche(0,0) et un joueur en bas à droite(19,13) et un joueur en haut à droite(19,0) et un joueur en bas à gauche(0,13)
			break;
			
		default:
			break;
	}
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