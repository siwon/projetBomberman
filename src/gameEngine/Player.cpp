/*!
 * \file GameEngineManager.cpp
 * \brief Implémentation de la classe Player
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Player.hpp"

namespace PolyBomber;

void Player::die() {
	this.~Player();
}

void Player::applyBonus(Bonus bonus) {
  
}

void Player::move(EOrientation direction) {
  
}