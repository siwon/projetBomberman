/*!
 * \file Location.cpp
 * \brief Implementation de la classe Location
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Location.hpp"


namespace PolyBomber {
	
	Location::Location(float x, float y) {
		this->location=sf::Vector2f(x,y);
	}
	
	Location::Location(const Location& loc) {
		this->location=sf::Vector2f(loc.getLocationX(),loc.getLocationY());
	}
	
	Location::~Location() {
		this->location.~Vector2();
	}
	
}