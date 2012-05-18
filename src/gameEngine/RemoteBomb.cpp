/*!
 * \file RemoteBomb.cpp
 * \brief Implémentation de la classe RemoteBomb
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

// Bibliothèques externes


// Headers
#include "../../include/gameEngine/RemoteBomb.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

RemoteBomb::RemoteBomb(const Player& player) : Explosive(player) {
	
}

RemoteBomb::RemoteBomb(const RemoteBomb& rb) : Explosive(rb.getLocation(),rb.getPlayer(),rb.getRange()) {
	
}

RemoteBomb::~RemoteBomb() {
	
}