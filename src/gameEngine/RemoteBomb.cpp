/*!
 * \file RemoteBomb.cpp
 * \brief Implementation de la classe RemoteBomb
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/RemoteBomb.hpp"
#include "gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	
	RemoteBomb::RemoteBomb(const Player& player) : Explosive(player) {
		
	}
	
	RemoteBomb::RemoteBomb(const RemoteBomb& rb) : Explosive(rb.getPlayer(),rb.getRange(),rb.getLocationX(), rb.getLocationY()) {
		
	}
	
	RemoteBomb::~RemoteBomb() {
		
	}
	
}