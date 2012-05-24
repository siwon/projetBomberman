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
#include "../../include/gameEngine/Location.hpp"


namespace PolyBomber {
	
	Location::Location(int x, int y) {
		this->location=sf::Vector2<int>(x,y);
	}
	
	Location::Location(const Location& loc) {
		this->location=sf::Vector2<int>(loc.getLocationX(),loc.getLocationY());
	}
	
	Location::~Location() {
		this->location.~Vector2();
	}

	void Location::setLocation(int x, int y) {
		this->location.x=x;
		this->location.y=y;
	}
	
}