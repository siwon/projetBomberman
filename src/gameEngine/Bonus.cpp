/*!
 * \file Bonus.cpp
 * \brief Implementation de la classe Bonus
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/Bonus.hpp"


namespace PolyBomber {
	
	Bonus::Bonus(int x, int y, EGameBonus type, bool visible) : Location(x,y) {
		this->type=type;
		this->visible=visible;
	}
	
	Bonus::Bonus(const Bonus& bonus) : Location(bonus.getLocationX(),bonus.getLocationY()) {
		this->type=bonus.getType();
		this->visible=bonus.isVisible();
	}
	
	Bonus::~Bonus() {
		
	}
	
}
