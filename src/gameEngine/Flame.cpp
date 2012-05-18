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
#include "../../include/gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Flame::Flame(int x, int y, EOrientation orientation, EFlameLocation step) : Location(x,y) {
	this->orientation=orientation;
	this->step=step;
}

Flame::Flame(const Location& loc, EOrientation orientation, EFlameLocation step) : Location(loc) {
	this->orientation=orientation;
	this->step=step;
}

Flame::Flame(const Flame& flamme) : Location(flamme.getLocation()) {
	this->orientation=flamme.getOrientation();
	this->step=flamme.getStep();
}

Flame::~Flame() {
	
}