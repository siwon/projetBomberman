#ifndef _IMENUTOGAMEINTERFACE
#define _IMENUTOGAMEINTERFACE

/*!
 * \file IMenuToGameInterface.hpp
 * \brief Interface fournie par le menu pour l'interface de jeu
 * \author Maxime GUIHAL
 */

#include "EScreenSignal.hpp"

namespace PolyBomber
{
	/*!
	 * \class IMenuToGameInterface
	 * \brief Interface fournie par le menu pour l'interface de jeu
	 */
	class IMenuToGameInterface
	{
		public:
			/*!
			 * \brief Exécution du menu de pause
			 * \param player Numéro du joueur ayant appuyé sur pause
			 * \return Signal de fin d'exécution, retourne EXITGAME si
			 * l'exécution s'est bien passée, EXITERROR sinon
			 */
			virtual EScreenSignal runPause(unsigned int player) = 0;
	};
}

#endif
