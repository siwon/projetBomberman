/*!
 * \file Bomb.cpp
 * \brief Implémentation de la classe Bomb
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Bomb.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Bomb::Bomb(int time, const Player& player) : Explosive(player) {
	sf::Clock horloge = sf::Clock();
	//TODO : Définir une horloge globale
	this->timeOfExplosion=horloge.getElapsedTime().asSeconds()+BOMBTIMESTAMP;
}

Bomb::Bomb(const Bomb& bombe) : Explosive(bombe.getLocation(), bombe.getPlayer(), bombe.getRange()) {
	this->timeOfExplosion=bombe.getTimeOfExplosion();
}

Bomb::~Bomb() {
	
}