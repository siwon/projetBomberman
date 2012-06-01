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
#include "../../include/gameEngine/Flame.hpp"

namespace PolyBomber {
	
	Flame::Flame(int x, int y, EOrientation orientation, EFlameLocation flameLocation, int date) : Location(x,y) {
		this->orientation=orientation;
		this->flameLocation=flameLocation;
		this->dateDebutFlame=date;
	}
	
	Flame::Flame(const Flame& flamme) : Location(flamme.getLocationX(),flamme.getLocationY()) {
		this->orientation=flamme.getOrientation();
		this->flameLocation=flamme.getFlameLocation();
		this->dateDebutFlame=flamme.getDateDebutFlame();;
	}
	
	Flame::~Flame() {
		
	}
	
}