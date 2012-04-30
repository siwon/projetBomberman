#ifndef _ESCREENSIGNAL
#define _ESCREENSIGNAL

/*!
 * \file IMenuToMain.hpp
 * \brief Interface Entrée du programme - Menu
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EScreenSignal
	 * \brief Signal de sortie de menu
	 */
	enum EScreenSignal
	{
		EXITGAME, /*!< Fin du programme */
		EXITMENU, /*!< Fin du menu pour retourner au jeu */
		EXITERROR /*!< Fin avec erreur */
	};
}

#endif
