#ifndef _MAINMENU
#define _MAINMENU

/*!
 * \file MainMenu.hpp
 * \brief Classe de gestion du menu principal
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

namespace PolyBomber
{
	/*!
	 * \class MainMenu
	 * \brief Classe de gestion du menu principal
	 */
	class MainMenu : public IMenuScreen
	{
		public:
			MainMenu();
			~MainMenu();
		
			EMenuScreen run(MainWindow& window, EMenuScreen previous);
	};
}

#endif

