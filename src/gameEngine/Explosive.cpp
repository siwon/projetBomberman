/*!
 * \file Explosive.cpp
 * \brief Implémentation de la classe Explosive
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Explosive.hpp"

namespace PolyBomber;

Explosive(Player player) {
	this->player=player;
	this->range=player.getRange();
}

Explosive(Explosive expl) {
	this->player=expl.getPlayer();
	this->range=expl.getRange();
}

~Explosive() {
	
}