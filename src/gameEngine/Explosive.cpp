/*!
 * \file Explosive.cpp
 * \brief Implementation de la classe Explosive
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "../../include/gameEngine/Explosive.hpp"


namespace PolyBomber {
	
	Explosive::Explosive(int player, int range, int x, int y) : Location(x,y) {
		this->player=player;
		this->range=range;
	}
	
	Explosive::Explosive(const Player& player) : Location(player.getLocationX(),player.getLocationY()) {
		this->player=player.getId();
		this->range=player.getRange();
	}
	
	Explosive::Explosive(const Explosive& expl) : Location(expl.getLocationX(),expl.getLocationY()) {
		this->player=expl.getPlayer();
		this->range=expl.getRange();
	}
	
	Explosive::~Explosive() {
		
	}
	
}