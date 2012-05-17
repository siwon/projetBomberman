/*!
 * \file Bonus.cpp
 * \brief Implémentation de la classe Bonus
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards
#include <Vector>

// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Bonus.hpp"

using namespace PolyBomber;

Bonus::Bonus(int x, int y, EGameBonus type) {
	super(x,y);
	this->type=type;
}

Bonus(Location loc, EGameBonus type) {
	super(loc);
	this->type=type;
}

Bonus::Bonus(Bonus bonus) {
	this(bonus.getLocationX(), bonus.getLocationY(), bonus.getType());
}

Bonus::~Bonus() {
	~super();
}