#ifndef _ESCREENSIGNAL
#define _ESCREENSIGNAL

/*!
 * \file EScreenSignal.hpp
 * \brief Enumération des signaux de sortie
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
		EXITMENU, /*!< Retour au menu */
		EXITERROR /*!< Fin avec erreur */
	};
}

#endif
