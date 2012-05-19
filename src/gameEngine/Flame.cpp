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

namespace PolyBomber {
	
	Flame::Flame(float x, float y, EOrientation orientation, EFlameLocation step) : Location(x,y) {
		this->orientation=orientation;
		this->step=step;
	}
	
	Flame::Flame(const Flame& flamme) : Location(flamme.getLocationX(),flamme.getLocationY()) {
		this->orientation=flamme.getOrientation();
		this->step=flamme.getStep();
	}
	
	Flame::~Flame() {
		
	}
	
}