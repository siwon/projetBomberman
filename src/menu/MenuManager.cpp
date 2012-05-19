/*!
 * \file MenuManager.cpp
 * \brief Gestionnaire du menu
 * \author Maxime GUIHAL
 */

#include "menu/MenuManager.hpp"

#include "menu/SplashScreen.hpp"
#include "menu/MainMenu.hpp"
#include "menu/GameMenu.hpp"
#include "menu/ConfigMenu.hpp"
#include "menu/GraphicsConfigMenu.hpp"

namespace PolyBomber
{
	MenuManager::MenuManager() : window()
	{
		// Ajout des menus
		this->menuScreens[SPLASHSCREEN] = new SplashScreen();
		this->menuScreens[MAINMENU] = new MainMenu();
		this->menuScreens[GAMEMENU] = new GameMenu();
		this->menuScreens[CONFIGMENU] = new ConfigMenu();
		this->menuScreens[GRAPHICSCONFIGMENU] = new GraphicsConfigMenu();
	}

	MenuManager::~MenuManager()
	{
		// On parcourt la liste pour désallouer les menus
		std::map<EMenuScreen, IMenuScreen*>::iterator it;
		for (it = this->menuScreens.begin(); it != this->menuScreens.end(); it++)
			delete (*it).second;
	}

	EScreenSignal MenuManager::run()
	{
		EMenuScreen old = SPLASHSCREEN;
		EMenuScreen screen = SPLASHSCREEN;

		while (screen != EXIT)
		{			
			EMenuScreen next = this->menuScreens[screen]->run(this->window, old);
			old = screen;
			screen = next;
		}
		
		return EXITGAME;
	}

	
	EScreenSignal MenuManager::runPause(unsigned int player)
	{
		// TODO
		return EXITMENU;
	}
}
