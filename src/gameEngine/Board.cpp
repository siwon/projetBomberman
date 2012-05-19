/*!
 * \file Board.cpp
 * \brief Implementation de la classe Board
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Board.hpp"


namespace PolyBomber {
	
	Board::Board() {
		this->bonus=std::vector<Bonus>();
		this->flame=std::vector<Flame>();
		this->box=std::vector<Box>();
		this->player=std::vector<Player>();
		this->explosive=std::vector<Explosive>();
		this->wall=std::vector<Wall>();
	}
	
	Board::Board(const Board& b) {
		this->bonus=std::vector<Bonus>();
		this->flame=std::vector<Flame>();
		this->box=std::vector<Box>();
		this->player=std::vector<Player>();
		this->explosive=std::vector<Explosive>();
		this->wall=std::vector<Wall>();
	}
	
	Board::~Board() {
		unsigned int i;
		
		//suppression de tous les objets contenus
		for (i=0; i<this->bonus.size(); i++) {
			this->bonus[i].~Bonus();
		}
		for (i=0; i<this->flame.size(); i++) {
			this->flame[i].~Flame();
		}
		for (i=0; i<this->box.size(); i++) {
			this->box[i].~Box();
		}
		for (i=0; i<this->player.size(); i++) {
			this->player[i].~Player();
		}
		for (i=0; i<this->explosive.size(); i++) {
			this->explosive[i].~Explosive();
		}
		for (i=0; i<this->wall.size(); i++) {
			this->wall[i].~Wall();
		}
		
		//suppression de tous les conteneurs
		this->bonus.~vector();
		this->flame.~vector();
		this->box.~vector();
		this->player.~vector();
		this->explosive.~vector();
		this->wall.~vector();
	}
	
	bool Board::caseIsFreeInitialisation(float x, float y) {
		bool toReturn;
		//test si c'est une coordonnee reservee
		if ((x==caseToPixel(0)&&y==caseToPixel(1))||(x==caseToPixel(1)&&y==caseToPixel(0))||(x==caseToPixel(17)&&y==caseToPixel(0))||(x==caseToPixel(18)&&y==caseToPixel(1))||(x==caseToPixel(18)&&y==caseToPixel(11))||(x==caseToPixel(17)&&y==caseToPixel(12))||(x==caseToPixel(0)&&y==caseToPixel(11))||(x==caseToPixel(1)&&y==caseToPixel(12))||(x==caseToPixel(8)&&y==caseToPixel(11))||(x==caseToPixel(8)&&y==caseToPixel(12))||(x==caseToPixel(10)&&y==caseToPixel(12))||(x==caseToPixel(10)&&y==caseToPixel(11))) {
			toReturn=false;
		} else {
			toReturn=caseIsFree(x,y);
		}
		return toReturn;
	}
	
	bool Board::caseIsFree(float x, float y) {
		bool toReturn = true;
		unsigned int i=0;;
		while (toReturn && i<bonus.size()) {//bonus
			if (pixelToCase(x)==pixelToCase(bonus[i].getLocationX()) && pixelToCase(y)==pixelToCase(bonus[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<flame.size()) {//flame
			if (pixelToCase(x)==pixelToCase(flame[i].getLocationX()) && pixelToCase(y)==pixelToCase(flame[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<box.size()) {//box
			if (pixelToCase(x)==pixelToCase(box[i].getLocationX()) && pixelToCase(y)==pixelToCase(box[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<player.size()) {//player
			if (pixelToCase(x)==pixelToCase(player[i].getLocationX()) && pixelToCase(y)==pixelToCase(player[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<explosive.size()) {//explosive
			if (pixelToCase(x)==pixelToCase(explosive[i].getLocationX()) && pixelToCase(y)==pixelToCase(explosive[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<wall.size()) {//wall
			if (pixelToCase(x)==pixelToCase(wall[i].getLocationX()) && pixelToCase(y)==pixelToCase(wall[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		return toReturn;
	}
	
	
	
	int Board::nbSurvivant() {
		int toReturn=0;
		for (unsigned int i=0; i<player.size(); i++) {
			if (player[i].getAlive()) {
				toReturn++;
			}
		}
		return toReturn;
	}
	
	int Board::getIdSurvivant() {
		int toReturn;
		unsigned int cpt;
		if (nbSurvivant()==1) {
			toReturn=1;
			while (cpt< player.size() && !player[cpt].getAlive()) {
				cpt++;
				toReturn++;
			}
		} else {
			toReturn=0;
		}
		return toReturn;
	}
	
	static EGameBonus intToEGameBonus(int i) {
		EGameBonus toReturn;
		switch (i) {
			case 0:
				toReturn=SPEEDUP;
				break;
				
			case 1:
				toReturn=SPEEDDOWN;
				break;
				
			case 2:
				toReturn=BOMBLINE;
				break;
				
			case 3:
				toReturn=DETONATOR;
				break;
				
			case 4:
				toReturn=BOMBUP;
				break;
				
			case 5:
				toReturn=BOMBDOWN;
				break;
				
			case 6:
				toReturn=RANGEUP;
				break;
				
			case 7:
				toReturn=RANGEDOWN;
				break;
				
			case 8:
				toReturn=RANGEUPMAX;
				break;
				
			case 9:
				toReturn=MINE;
				break;
				
			case 10:
				toReturn=INFINITYBOMB;
				break;
				
			case 11:
				toReturn=ATOMICBOMB;
				break;
				
			case 12:
				toReturn=CRANE;
				break;
				
			case 13:
				toReturn=HELL;
				break;
				
			case 14:
				toReturn=CONFUSION;
				break;
				
			case 15:
				toReturn=SPASME;
				break;
				
			case 16:
				toReturn=DILATATION;
				break;
				
			case 17:
				toReturn=RAGE;
				break;
				
			default:
				//erreur
				break;
		}
	}
	
}