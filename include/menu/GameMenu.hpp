#ifndef _GAMEMENU
#define _GAMEMENU

/*!
 * \file GameMenu.hpp
 * \brief Classe de gestion du menu de jeu
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

namespace PolyBomber
{
	/*!
	 * \class GameMenu
	 * \brief Classe de gestion du menu de jeu
	 */
	class GameMenu : public IMenuScreen
	{
		public:
			GameMenu();
			~GameMenu();
		
			EMenuScreen run(MainWindow& window, EMenuScreen previous);
	};
}

#endif

