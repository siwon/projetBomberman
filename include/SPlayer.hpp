#ifndef S_PLAYER_HEADER
#define S_PLAYER_HEADER

/*!
 * \file SPlayer.hpp
 * \brief Structure de configuration du joueur
 * \author Simon Rousseau
 */

/** Includes **/
//Bibliothèque standard
#include <vector>

//Bibliothèque SFML


//Bibliothèque externes


//Headers du projet
#include "./EOrientation.hpp"
#include "./EPlayerState.hpp"

namespace PolyBomber;

/*!
 * \struct SPlayer
 * \brief Configuration du joueur
 * 
 */
struct SPlayer {
  Vector<int> coords;		/*! Coordonnées du joueur */
  EOrientation orientation;	/*! Orientation du joueur */
  unsigned int number;		/*!  */
  EPlayerState state;		/*! Statistique du joueur */
  unsigned int step;		/*!  */
};

#endif