/*!
 * \file Explosive.cpp
 * \brief Implementation de la classe Explosive
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <vector>

// Bibliotheques SFML
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/Explosive.hpp"
#include "gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Explosive::Explosive(const Player& player) : Location(player.getLocation()) {
	this->player=player.getId();
	this->range=player.getRange();
}

Explosive::Explosive(const Location& loc, int player, int range) : Location(loc) {
	this->player=player;
	this->range=range;
}

Explosive::Explosive(const Explosive& expl) : Location(expl.getLocation()) {
	this->player=expl.getPlayer();
	this->range=expl.getRange();
}

Explosive::~Explosive() {
	
}