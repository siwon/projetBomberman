#ifndef _CONFIGMENU
#define _CONFIGMENU

/*!
 * \file ConfigMenu.hpp
 * \brief Classe de gestion du menu de configuration
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

namespace PolyBomber
{
	/*!
	 * \class GameMenu
	 * \brief Classe de gestion du menu de configuration
	 */
	class ConfigMenu : public IMenuScreen
	{
		public:
			ConfigMenu();
			~ConfigMenu();
		
			EMenuScreen run(MainWindow& window, EMenuScreen previous);
	};
}

#endif

