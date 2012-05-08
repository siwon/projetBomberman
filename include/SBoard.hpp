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
#include <SFML/System/Vector2.hpp>

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
    sf::Vector2<int> boxes;		        /*!  */
    std::vector<SBonus> bonus;			/*! Liste des bonus du plateau de jeu */
    std::vector<SExplosive> explosives;	/*! Liste des explosifs du plateau de jeu */
    std::vector<SPlayer> players;		/*! Liste des joueurs du plateau de jeu */
    std::vector<SFlame> flames;		    /*! Liste des déflagrations du plateau de jeu */
  };
}

#endif
