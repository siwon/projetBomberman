/*!
 * \file Explosive.cpp
 * \brief Implementation de la classe Explosive
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/Explosive.hpp"
#include "gameEngine/Board.hpp"


namespace PolyBomber {
	
	Explosive::Explosive(int player, int range, int x, int y) : Location(x,y) {
		this->player=player;
		this->range=range;
	}
	
	Explosive::Explosive(const Player& player) : Location(Board::cranToCase(player.getLocationX()),Board::cranToCase(player.getLocationY())) {
		this->player=player.getId();
		this->range=player.getRange();
	}
	
	Explosive::Explosive(const Player& player, int x, int y) : Location(x,y) {// x et y sont en cases
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