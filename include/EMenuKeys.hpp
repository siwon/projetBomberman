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
		UP, /*!< Aller vers le haut */
		DOWN, /*!< Aller vers le bas */
		LEFT, /*!< Aller vers la gauche */
		RIGHT, /*!< Aller vers la droite */
		VALID, /*!< Valider la sélection */
		BACK, /*!< Allez en arrière */
		NONE /*!< Aucune touche appuyée */
	};
}

#endif

