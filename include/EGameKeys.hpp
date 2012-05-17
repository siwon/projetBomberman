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
		GAME_UP, /*!< Aller vers le haut */
		GAME_DOWN, /*!< Aller vers le bas */
		GAME_LEFT, /*!< Aller vers la gauche */
		GAME_RIGHT, /*!< Aller vers la droite */
		GAME_ACTION1, /*!< Poser une bombe */
		GAME_ACTION2, /*!< Activer le détonateur */
		GAME_PAUSE, /*!< Mettre le jeu en pause */
		GAME_NONE /*!< Aucune touche pressée */
	};
}

#endif
