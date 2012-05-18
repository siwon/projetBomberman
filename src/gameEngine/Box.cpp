/*!
 * \file Box.cpp
 * \brief Implémentation de la classe Box
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards
#include <Vector>

// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Box.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

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