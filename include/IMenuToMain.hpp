#ifndef _IMENUTOMAIN
#define _IMENUTOMAIN

/*!
 * \file IMenuToMain.hpp
 * \brief Interface Entrée du programme - Menu
 * \author Maxime GUIHAL
 */

#include "EScreenSignal.hpp"

namespace PolyBomber
{
	/*!
	 * \class IMenuToMain
	 * \brief Interface Entrée du programme - Menu
	 */
	class IMenuToMain
	{
		public:
			/*!
			 * \brief Exécution du menu
			 * \return Signal de fin d'exécution, retourne EXITGAME si
			 * l'exécution s'est bien passée, EXITERROR sinon
			 */
			virtual EScreenSignal run() = 0;
	};
}

#endif
