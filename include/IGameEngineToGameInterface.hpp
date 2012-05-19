#ifndef _IGAMEENGINETOGAMEINTERFACE
#define _IGAMEENGINETOGAMEINTERFACE

/*!
 * \file IGameEngineToGameInterface.hpp
 * \brief Interface generale entre le moteur de jeu et le plateau de jeu
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
		* \brief Methode permettant de retourner le plateau de jeu
		*
		* \return Retourne le plateau de jeu.
		*/
		virtual SBoard getBoard() =0;

		/*!
		* \brief Methode qui signal si le jeu est termine ou pas
		* Cette methode permet de determiner si le jeu est termine ou pas.
		* \return Renvoie 1 si le jeu est termine, renvoie 0 sinon.
		*/
		virtual int isFinished() =0;

		/*!
		* \brief Destructeur virtuel
		*/
		virtual ~IGameEngineToGameInterface() {};
  };
}

#endif
