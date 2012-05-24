/*!
 * \file Wall.cpp
 * \brief Implementation de la classe Wall
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "../../include/gameEngine/Wall.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	
	Wall::Wall(int x, int y) : Location(x,y) {
		
	}
	
	Wall::Wall(const Wall& e) : Location(e.getLocationX(), e.getLocationY()) {
		
	}
	
	Wall::~Wall(){
		
	}
	
}