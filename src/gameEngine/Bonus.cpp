/*!
 * \file Bonus.cpp
 * \brief Implementation de la classe Bonus
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
//#include <vector>

// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Bonus.hpp"


namespace PolyBomber {
	
	Bonus::Bonus(float x, float y, EGameBonus type, bool visible) : Location(x,y) {
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