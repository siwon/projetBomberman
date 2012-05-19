/*!
 * \file Box.cpp
 * \brief Implementation de la classe Box
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Box.hpp"

namespace PolyBomber {
	
	Box::Box(float x, float y, bool bonus) : Location(x,y) {
		this->bonus=bonus;
	}
	
	Box::Box(const Box& boite) : Location(boite.getLocationX(),boite.getLocationY()) {
		this->bonus=boite.getBonus();
	}
	
}