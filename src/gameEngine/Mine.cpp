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

namespace PolyBomber;

Mine(Player p) {
	super(p);
}

Mine(Mine mine) {
	super(mine.getPlayer());
}

~Mine() {
	~super();
}