/*!
 * \file Wall.cpp
 * \brief Implementation de la classe Wall
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/Wall.hpp"
#include "gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	
	Wall::Wall(int x, int y) : Location(x,y) {
		
	}
	
	Wall::Wall(const Wall& e) : Location(e.getLocationX(), e.getLocationY()) {
		
	}
	
	Wall::~Wall(){
		
	}
	
}