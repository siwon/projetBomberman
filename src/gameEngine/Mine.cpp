/*!
 * \file Mine.cpp
 * \brief Implementation de la classe Mine
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Mine.hpp"

namespace PolyBomber {
	
	Mine::Mine(const Player& p) : Explosive(p) {
		
	}
	
	Mine::Mine(const Mine& mine) : Explosive(mine.getPlayer(),mine.getRange(),mine.getLocationX(),mine.getLocationY()) {
		
	}
	
	Mine::~Mine() {
		
	}
	
}