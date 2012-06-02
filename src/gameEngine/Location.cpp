/*!
 * \file Location.cpp
 * \brief Implementation de la classe Location
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/DefineAndFunction.hpp"
#include "gameEngine/Location.hpp"


namespace PolyBomber {
	
	Location::Location(int x, int y) {
		this->location=sf::Vector2<int>(x,y);
	}
	
	Location::Location(const Location& loc) {
		this->location=sf::Vector2<int>(loc.getLocationX(),loc.getLocationY());
	}
	
	Location::~Location() {
		
	}

	void Location::setLocation(int x, int y) {
		this->location.x=x;
		this->location.y=y;
	}
	
}