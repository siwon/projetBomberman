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

namespace PolyBomber;

Bomb(int time, Player player) {
	super(player);
	sf::Clock horloge = sf::Clock();
	//TODO : Définir une horloge globale
	this.timeOfExplosion=horloge.getElapsedTime().asSeconds()+BOMBTIMESTAMP;
}

Bomb(Bomb bombe) {
	super(bombe.getPlayer());
	this->timeOfExplosion=bombe.getTimeOfExplosion();
}

~Bomb() {
	~super();
}