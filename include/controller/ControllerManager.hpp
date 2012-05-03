#ifndef _CONTROLLERMANAGER
#define _CONTROLLERMANAGER

/*!
 * \file ControllerManager.hpp
 * \brief Classe de gestion des contrôleurs de jeu
 * \author Alexandre BISIAUX
 */

#include <string.h>

#include "../SKeysConfig.hpp"
#include "../EMenuKeys.hpp"
#include "../IControllerToMenu.hpp"
#include "../IControllerToNetwork.hpp"

namespace PolyBomber
{
	/*!
	 * \class ControllerManager
	 * \brief Classe de gestion des contrôleurs de jeu
	 */
	class ControllerManager : public IcontrollerToMenu
	{
		private:

			SKeysConfig[4] keysAssignation; /*!<  Tableau de configuration des touches pour chaque joueur */

	};
}

#endif

