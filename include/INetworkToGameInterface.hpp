#ifndef _INETWORKTOGAMEINTERFACE
#define _INETWORKTOGAMEINTERFACE

/*!
 * \file INetworkToGameInterface.hpp
 * \brief Interface réseau - affichage
 * \author Brice GUILLERMIC
 */

#include "IGameEngineToGameInterface.hpp"
namespace PolyBomber
{
	/*!
	 * \class INetworkToGameInterface
	 * \brief Interface Interface réseau - affichage
	 */
	class INetworkToGameInterface : public IGameEngineToGameInterface
	{
		public:
			/*!
			 * \brief Obtenir le joueur qui a mis le jeu en pause
			 * \return Numéro du joueur
			 */
			virtual int isPaused() =0;
	};
}
#endif
