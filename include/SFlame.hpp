#ifndef S_FLAME_HEADER
#define S_FLAME_HEADER

/*!
 * \file SFlame.hpp
 * \brief Structure de configuration d'une déflagration
 * \author Simon Rousseau
 */

//Bibliothèque SFML
#include <SFML/System/Vector2.hpp>

//Headers du projet
#include "EOrientation.hpp"
#include "EFlameLocation.hpp"

namespace PolyBomber {
	/*!
	 * \struct SFlame
	 * \brief Configuration d'une déflagration
	 * 
	 */
	struct SFlame {
		sf::Vector2<int> coords;	/*!< Coordonnées de la déflagration */
		EOrientation orientation;	/*!< Orientation de la déflagration */
		EFlameLocation location;	/*!< Position de la déflagration */
		unsigned int step;			/*!< Compteur pour l'animation de la flamme - Non implémenté */
	};
}

#endif
