#ifndef _EMENUKEYS
#define _EMENUKEYS

/*!
 * \file EMenuKeys.hpp
 * \brief Enumération des touches de menu
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EMenuKeys
	 * \brief Touches de menu
	 */
	enum EMenuKeys
	{
		MENU_UP, /*!< Aller vers le haut */
		MENU_DOWN, /*!< Aller vers le bas */
		MENU_LEFT, /*!< Aller vers la gauche */
		MENU_RIGHT, /*!< Aller vers la droite */
		MENU_VALID, /*!< Valider la sélection */
		MENU_BACK, /*!< Allez en arrière */
		MENU_NONE /*!< Aucune touche appuyée */
	};
}

#endif

