#ifndef _INETWORKTOGAMEINTERFACE
#define _INETWORKTOGAMEINTERFACE

/*!
 * \file INetworkToGameInterface.hpp
 * \brief Interface r�seau - affichage
 * \author Brice GUILLERMIC
 */

#include "IGameEngineToGameInterface.hpp"
namespace PolyBomber
{
	/*!
	 * \class INetworkToGameInterface
	 * \brief Interface Interface r�seau - affichage
	 */
	class INetworkToGameInterface : public IGameEngineToGameInterface
	{
		public:
			/*!
			 * \brief Obtenir le joueur qui a mis le jeu en pause
			 * \return Num�ro du joueur
			 */
			virtual int isPaused() =0;

			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~INetworkToGameInterface() {};
};

#endif
