#ifndef S_BOARD_HEADER
#define S_BOARD_HEADER

/*!
 * \file SBoard.hpp
 * \brief Structure de configuration du plateau de jeu
 * \author Simon Rousseau
 */

/** Includes **/
//Bibliotheque standard
#include <vector>

//Bibliotheque SFML
#include <SFML/System/Vector2.hpp>

//Headers du projet
#include "SBonus.hpp"
#include "SExplosive.hpp"
#include "SPlayer.hpp"
#include "SFlame.hpp"

namespace PolyBomber {
  /*!
  * \struct SBoard
  * \brief Configuration du plateau de jeu
  * 
  */
  struct SBoard {
	std::vector<sf::Vector2<int> > boxes;	/*!< Liste des caisses du plateau de jeu */
    std::vector<SBonus> bonus;				/*!< Liste des bonus du plateau de jeu */
    std::vector<SExplosive> explosives;		/*!< Liste des explosifs du plateau de jeu */
    std::vector<SPlayer> players;			/*!< Liste des joueurs du plateau de jeu */
    std::vector<SFlame> flames;				/*!< Liste des déflagrations du plateau de jeu */
  };
}

#endif
