#ifndef _IGAMEENGINETOGAMEINTERFACE
#define _IGAMEENGINETOGAMEINTERFACE

/*!
 * \file IGameEngineToGameInterface.hpp
 * \brief Interface générale entre le moteur de jeu et le plateau de jeu
 * \author Simon Rousseau
 */

#include "SBoard.hpp"

namespace PolyBomber {
  /*!
  * \class IGameEngineToGameInterface
  * \brief Interface en le moteur de jeu et le plateau de jeu
  */
  class IGameEngineToGameInterface {
    public :
		/*!
		* \brief Méthode permettant de retourner le plateau de jeu
		*
		* \return Retourne le plateau de jeu.
		*/
		virtual SBoard getBoard() =0;

		/*!
		* \brief Méthode qui signal si le jeu est terminé ou pas
		* Cette méthode permet de déterminer si le jeu est terminé ou pas.
		* \return Renvoie le numéro du joueur qui a gagné.
		*/
		virtual int isFinished() =0;

		/*!
		* \brief Destructeur virtuel
		*/
		virtual ~IGameEngineToGameInterface() {};
  };
}

#endif
