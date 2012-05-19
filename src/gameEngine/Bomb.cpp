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
#include "gameEngine/Bomb.hpp"

namespace PolyBomber {
	
	Bomb::Bomb(sf::Clock horloge, const Player& player) : Explosive(player) {
		this->timeOfExplosion=horloge.getElapsedTime().asSeconds()+BOMBTIMESTAMP;
	}
	
	Bomb::Bomb(const Bomb& bombe) : Explosive(bombe.getPlayer(), bombe.getRange(), bombe.getLocationX(), bombe.getLocationY()) {
		this->timeOfExplosion=bombe.getTimeOfExplosion();
	}
	
	Bomb::~Bomb() {
		
	}
	
}