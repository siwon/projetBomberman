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
	
}