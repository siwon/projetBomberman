/*!
 * \file Player.cpp
 * \brief Implementation de la classe Player
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Player.hpp"

namespace PolyBomber {
	
	Player::Player(float x, float y, int id) : Location(x,y) {
		this->id=id;
		this->speed=VITESSEPARDEFAUT;
		this->capacity=NOMBREBOMBEDEFAUT;
		this->orientation=ORIENTATIONDEFAUT;
		this->range=RANGEDEFAUT;
		this->alive=true;
		this->step=0;
		
		this->bombBonus=std::vector<Bonus>();
		this->infection=std::vector<Bonus>();
	}
	
	Player::Player(const Player& pl) : Location(pl.getLocationX(),pl.getLocationY()) {
		this->id=pl.getId();
		this->speed=pl.getSpeed();
		this->capacity=pl.getCapacity();
		this->orientation=pl.getOrientation();
		this->range=pl.getRange();
		this->alive=getAlive();
		this->step=getStep();
		
		this->bombBonus=std::vector<Bonus>();
		this->infection=std::vector<Bonus>();
	}
	
	Player::~Player() {
		this->bombBonus.~vector();
		this->infection.~vector();
	}
	
}