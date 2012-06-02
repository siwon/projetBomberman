#ifndef S_PLAYER_HEADER
#define S_PLAYER_HEADER

/*!
 * \file SPlayer.hpp
 * \brief Structure de configuration du joueur
 * \author Simon Rousseau
 */

//Bibliothèque SFML
#include <SFML/System/Vector2.hpp>

//Headers du projet
#include "EOrientation.hpp"
#include "EPlayerState.hpp"

namespace PolyBomber {
  /*!
  * \struct SPlayer
  * \brief Configuration du joueur
  * 
  */
  struct SPlayer {
    sf::Vector2<int> coords;	/*! Coordonnées du joueur */
    EOrientation orientation;	/*! Orientation du joueur */
    unsigned int number;		/*! Numéro du joueur (1-4) */
    EPlayerState state;		/*! Etat du joueur (vivant ou pas) */
    unsigned int step;		/*! Compteur incrémentant les pas du joueur */
  };
}

#endif
