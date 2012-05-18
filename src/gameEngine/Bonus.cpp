/*!
 * \file Bonus.cpp
 * \brief Implémentation de la classe Bonus
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards
#include <vector>

// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Bonus.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Bonus::Bonus(int x, int y, EGameBonus type) : Location(x,y) {
	this->type=type;
}

Bonus::Bonus(const Location& loc, EGameBonus type) : Location(loc) {
	this->type=type;
}

Bonus::Bonus(const Bonus& bonus) : Location(bonus.getLocation()) {
	this->visible=bonus.isVisible();
	this->type=bonus.getType();
}

Bonus::~Bonus() {
	
}