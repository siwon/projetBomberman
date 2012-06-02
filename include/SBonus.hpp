#ifndef S_BONUS_HEADER
#define S_BONUS_HEADER

/*!
 * \file SBonus.hpp
 * \brief Structure de configuration d'un bonus
 * \author Simon Rousseau
 */

//Bibliothèque SFML
#include <SFML/System/Vector2.hpp>

//Headers du projet
#include "EGameBonus.hpp"

namespace PolyBomber {
	/*!
	 * \struct SBonus
	 * \brief Configuration d'un bonus
	 * 
	 */
	struct SBonus {
		sf::Vector2<int> coords;	/*!< Coordonnées du bonus */
		EGameBonus type;		/*!< Type de bonus */
	};
}

#endif
