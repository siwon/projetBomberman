/*!
 * \file Bomb.cpp
 * \brief Implementation de la classe Bomb
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/Bomb.hpp"
#include "gameEngine/DefineAndFunction.hpp"

using namespace PolyBomber;

Bomb::Bomb(int time, const Player& player) : Explosive(player) {
	sf::Clock horloge = sf::Clock();
	//TODO : Definir une horloge globale
	this->timeOfExplosion=horloge.getElapsedTime().asSeconds()+BOMBTIMESTAMP;
}

Bomb::Bomb(const Bomb& bombe) : Explosive(bombe.getLocation(), bombe.getPlayer(), bombe.getRange()) {
	this->timeOfExplosion=bombe.getTimeOfExplosion();
}

Bomb::~Bomb() {
	
}