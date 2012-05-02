#ifndef _EGAMEKEYS
#define _EGAMEKEYS

/*!
 * \file EGameKeys.hpp
 * \brief Enumération des touches de jeu
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EGameKeys
	 * \brief Touches de jeu
	 */
	enum EGameKeys
	{
		UP, /*!< Aller vers le haut */
		DOWN, /*!< Aller vers le bas */
		LEFT, /*!< Aller vers la gauche */
		RIGHT, /*!< Aller vers la droite */
		ACTION1, /*!< Poser une bombe */
		ACTION2, /*!< Activer le détonateur */
		PAUSE /*!< Mettre le jeu en pause */
	};
}

#endif
