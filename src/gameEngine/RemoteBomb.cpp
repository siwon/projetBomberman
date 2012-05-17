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

namespace PolyBomber;

RemoteBomb(Player player) {
	super(player);
}

RemoteBomb(RemoteBomb rb) {
	super(rb.getPlayer());
}

~RemoteBomb() {
	~super();
}