/*!
 * \file Mine.cpp
 * \brief Implémentation de la classe Mine
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Mine.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Mine::Mine(const Player& p) : Explosive(p) {
	
}

Mine::Mine(const Mine& mine) : Explosive(mine.getLocation(),mine.getPlayer(),mine.getRange()) {
	
}

Mine::~Mine() {
	
}