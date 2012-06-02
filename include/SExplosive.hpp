#ifndef S_EXPLOSIVE_HEADER
#define S_EXPLOSIVE_HEADER

/*!
 * \file SExplosive.hpp
 * \brief Structure de configuration d'un explosif
 * \author Simon Rousseau
 */

//Bibliothèque SFML
#include <SFML/System/Vector2.hpp>

//Headers du projet
#include "EExplosiveType.hpp"

namespace PolyBomber {
  /*!
  * \struct SExplosive
  * \brief Configuration d'un explosif
  * 
  */
  struct SExplosive {
    sf::Vector2<int> coords;	/*!< Coordonnées de l'explosif */
    EExplosiveType type;		/*!< Type d'explosif */
  };
}

#endif
