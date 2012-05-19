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
#include "gameEngine/Wall.hpp"
#include "gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Wall::Wall(int x, int y) : Location(x,y) {
	
}

Wall::Wall(const Location& loc) : Location(loc) {
	
}

Wall::Wall(const Wall& e) : Location(e.getLocation()) {
	
}

Wall::~Wall(){
	
}