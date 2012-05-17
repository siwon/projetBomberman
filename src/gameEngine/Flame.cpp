/*!
 * \file Flame.cpp
 * \brief Implémentation de la classe Flame
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Flame.hpp"

namespace PolyBomber;

Flame(int x, int y, EOrientation orientation, EFlameLocation step) {
	super(x,y);
	this->orientation=orientation;
	this->step=step;
}

Flame(Location loc, EOrientation orientation, EFlameLocation step) {
	super(loc);
	this->orientation=orientation;
	this->step=step;
}

Flame(Flame flamme) {
	this(flamme.getLocation(), flamme.getOrientation(), flamme.getStep());
}

~Flame() {
	~super();
}