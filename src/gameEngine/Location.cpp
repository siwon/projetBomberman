/*!
 * \file Location.cpp
 * \brief Implémentation de la classe Location
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML


// Bibliothèques externes
#include <SFML/System/Vector2.hpp>

// Headers
#include "../../include/gameEngine/Location.hpp"

using namespace PolyBomber;

Location(sf::Vector2<int> location) {
	this->Board=new Board();
	this->location=location;
}

Location::Location(int x, int y) {
	this(new sf::Vector2(x,y));
}

Location::Location(Location loc) {
	this(loc.getLocation());
}