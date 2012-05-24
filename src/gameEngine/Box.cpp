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
#include "../../include/gameEngine/Box.hpp"

namespace PolyBomber {
	
	Box::Box(int x, int y) : Location(x,y) {
	}
	
	Box::Box(const Box& boite) : Location(boite.getLocationX(),boite.getLocationY()) {
	}
	
	Box::~Box() {
		
	}
	
}