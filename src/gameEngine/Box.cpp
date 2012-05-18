/*!
 * \file Box.cpp
 * \brief Implementation de la classe Box
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <vector>

// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Box.hpp"
#include "gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Box::Box(int x, int y, bool bonus) : Location(x,y) {
	this->bonus=bonus;
}

Box::Box(const Location& loc, bool bonus) : Location(loc) {
	this->bonus=bonus;
}

Box::Box(const Box& boite) : Location(boite.getLocation()) {
	this->bonus=boite.getBonus();
}