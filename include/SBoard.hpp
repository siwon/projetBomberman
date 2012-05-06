#ifndef S_BOARD_HEADER
#define S_BOARD_HEADER

/*!
 * \file SBoard.hpp
 * \brief Structure de configuration du plateau de jeu
 * \author Simon Rousseau
 */

/** Includes **/
//Bibliothèque standard
#include <vector>

//Bibliothèque SFML
#include <SFML/Vector2.hpp>

//Bibliothèque externes


//Headers du projet
#include "./SBonus.hpp"
#include "./SExplosive.hpp"
#include "./SPlayer.hpp"
#include "./SFlame.hpp"

namespace PolyBomber {
  /*!
  * \struct SBoard
  * \brief Configuration du plateau de jeu
  * 
  */
  struct SBoard {
    sf::Vector2<int> boxes;		/*!  */
    Vector<SBonus> bonus;			/*! Liste des bonus du plateau de jeu */
    Vector<SExplosive> explosives;	/*! Liste des explosifs du plateau de jeu */
    Vector<SPlayer> players;		/*! Liste des joueurs du plateau de jeu */
    Vector<SFlame> flames;		/*! Liste des déflagrations du plateau de jeu */
  };
}

#endif