/*!
 * \file Mine.cpp
 * \brief Implementation de la classe Mine
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <vector>

// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/Mine.hpp"

namespace PolyBomber {
	
	Mine::Mine(const Player& p) : Explosive(p) {
		this->active=false;
	}
	
	Mine::Mine(const Mine& mine) : Explosive(mine.getPlayer(),mine.getRange(),mine.getLocationX(),mine.getLocationY()) {
		this->active=false;
	}
	
	Mine::~Mine() {
		
	}
	
}
