#ifndef E_PLAYER_STATE_HEADER
#define E_PLAYER_STATE_HEADER

/*!
 * \file EPlayerState.hpp
 * \brief Enumération des différents états possible d'un joueur
 * \author Simon ROUSSEAU
 */

namespace PolyBomber {
  /*!
  * \enum EPlayerState
  * \brief Enumération des différents états possible d'un joueur
  */
  enum EPlayerState {
    ALIVE =0,	/*!< Joueur vivant */
    DEAD		/*!< Joueur mort */
  };
}

#endif