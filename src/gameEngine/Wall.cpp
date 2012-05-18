/*!
 * \file Wall.cpp
 * \brief Implémentation de la classe Wall
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Wall.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Wall::Wall(int x, int y) : Location(x,y) {
	
}

Wall::Wall(const Location& loc) : Location(loc) {
	
}

Wall::Wall(const Wall& e) : Location(e.getLocation()) {
	
}

Wall::~Wall(){
	
}