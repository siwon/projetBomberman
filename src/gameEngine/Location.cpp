/*!
 * \file Location.cpp
 * \brief Implémentation de la classe Location
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML
#include <SFML/System/Vector2.hpp>

// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Location.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Location::Location(const sf::Vector2<int>& loc) {
	this->location=loc;
}

Location::Location(int x, int y) {
	this->location= sf::Vector2<int>::Vector2(x,y);
}

Location::Location(const Location& loc) {
	this->location= sf::Vector2<int>::Vector2(loc.getLocationX(),loc.getLocationY());
}

Location::~Location() {
	
}