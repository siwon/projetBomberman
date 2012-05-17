/*!
 * \file Box.cpp
 * \brief Implémentation de la classe Box
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards
#include <Vector>

// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Box.hpp"

using namespace PolyBomber;

Box::Box(int x, int y, bool bonus) {
	super(x,y);
	this->bonus=bonus;
}

Box::Box(Location loc, bool bonus) {
	super(loc);
	this->bonus=bonus;
}

Box::Box(Box boite) {
	this(bonus.getLocationX(), bonus.getLocationY(), boite.getBonus());
}