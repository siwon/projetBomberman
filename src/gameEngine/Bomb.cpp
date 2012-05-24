/*!
 * \file Bomb.cpp
 * \brief Implementation de la classe Bomb
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "../../include/gameEngine/Bomb.hpp"

namespace PolyBomber {
	
	Bomb::Bomb(int date, const Player& player, int type) : Explosive(player) {
		this->timeOfExplosion=date+BOMBTIMESTAMP;
		this->type=type;
	}
	
	Bomb::Bomb(const Bomb& bombe) : Explosive(bombe.getPlayer(), bombe.getRange(), bombe.getLocationX(), bombe.getLocationY()) {
		this->timeOfExplosion=bombe.getTimeOfExplosion();
	}
	
	Bomb::~Bomb() {
		
	}
	
}