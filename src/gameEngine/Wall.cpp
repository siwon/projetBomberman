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

namespace PolyBomber;

Wall(int x, int y) {
	super(x,y);
}

Wall(Location loc) {
	super(loc);
}

Wall(Wall e) {
	this(e.getLocation());
}

~Wall(){
	~super();
}