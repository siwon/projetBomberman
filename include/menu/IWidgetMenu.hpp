#ifndef _IWIDGETMENU
#define _IWIDGETMENU

/*!
 * \file IWidgetMenu.hpp
 * \brief Interface des widgets du menu
 * \author Maxime GUIHAL
 */

#include <SFML/Graphics.hpp>

namespace PolyBomber
{
	/*!
	 * \class IWidgetMenu
	 * \brief Interface des widgets du menu
	 */
	class IWidgetMenu : public sf::Sprite
	{
		public:
			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~IWidgetMenu() {};
	};
}

#endif





