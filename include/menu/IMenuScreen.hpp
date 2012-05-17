#ifndef _IMENUSCREEN
#define _IMENUSCREEN

/*!
 * \file IMenuScreen.hpp
 * \brief Interface des ecrans du menu
 * \author Maxime GUIHAL
 */
 
#include <vector>

#include <SFML/Graphics.hpp>

#include "menu/EMenuScreen.hpp"
#include "menu/MenuResources.hpp"
#include "menu/IWidgetMenu.hpp"

namespace PolyBomber
{
	/*!
	 * \class IMenuScreen
	 * \brief Interface des ecrans du menu
	 */
	class IMenuScreen
	{
		public:
			/*!
			 * \brief Exécution du menu sélectionné
			 * \param resources : Ressources associées au menu
			 * \param previous : Menu précédent
			 * \return Menu suivant
			 */
			virtual EMenuScreen run(MenuResources& resources, EMenuScreen previous) = 0;

			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~IMenuScreen() {};

		protected:
			std::vector<IWidgetMenu*> widgets; /*!< Liste des widgets des écrans */
	};
}

#endif




