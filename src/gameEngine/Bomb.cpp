/*!
 * \file Bomb.cpp
 * \brief Implementation de la classe Bomb
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <vector>

// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/DefineAndFunction.hpp"
#include "gameEngine/Bomb.hpp"

namespace PolyBomber {	
	Bomb::Bomb(int date, const Player& player, int type) : Explosive(player) {
		this->timeOfExplosion=date+BOMBTIMESTAMP;
		this->type=type;
	}
	
	Bomb::Bomb(int date, const Player& pl, int x, int y, int type) : Explosive(pl,x,y) {
		this->timeOfExplosion=date+BOMBTIMESTAMP;
		this->type=type;
	}
	
	Bomb::Bomb(const Bomb& bombe) : Explosive(bombe.getPlayer(), bombe.getRange(), bombe.getLocationX(), bombe.getLocationY()) {
		this->type=bombe.getType();
		this->timeOfExplosion=bombe.getTimeOfExplosion();
	}
	
	Bomb::~Bomb() {
		
	}
	
}