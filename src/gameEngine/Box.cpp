/*!
 * \file Box.cpp
 * \brief Implementation de la classe Box
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>

// Bibliotheques externes


// Headers

#include "gameEngine/DefineAndFunction.hpp"
#include "gameEngine/Box.hpp"

namespace PolyBomber {
	
	Box::Box(int x, int y) : Location(x,y) {
	}
	
	Box::Box(const Box& boite) : Location(boite.getLocationX(),boite.getLocationY()) {
	}
	
	Box::~Box() {
		
	}
	
}