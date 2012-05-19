/*!
 * \file Flame.cpp
 * \brief Implementation de la classe Flame
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Flame.hpp"
#include "gameEngine/DefineAndFunction.hpp"

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