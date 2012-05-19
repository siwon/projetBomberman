#ifndef _IMENUSCREEN
#define _IMENUSCREEN

/*!
 * \file IMenuScreen.hpp
 * \brief Interface des ecrans du menu
 * \author Maxime GUIHAL
 */

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "menu/EMenuScreen.hpp"
#include "menu/MainWindow.hpp"

#include "EImage.hpp"
#include "EColorKey.hpp"

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
			 * \param window : Fenêtre du programme
			 * \param previous : Menu précédent
			 * \return Menu suivant
			 */
			virtual EMenuScreen run(MainWindow& window, EMenuScreen previous) = 0;

			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~IMenuScreen() {};

		protected:
			std::vector<sf::Drawable*> widgets; /*!< Liste des widgets des écrans */
	};
}

#endif




