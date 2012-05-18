/*!
 * \file MenuManager.cpp
 * \brief Gestionnaire du menu
 * \author Maxime GUIHAL
 */

#include "menu/MenuManager.hpp"

#include "menu/SplashScreen.hpp"
#include "menu/MainMenu.hpp"

namespace PolyBomber
{
	MenuManager::MenuManager() : menuResources()
	{
		// Ajout des menus
		this->menuScreens.push_back(new SplashScreen());
		this->menuScreens.push_back(new MainMenu());
	}

	MenuManager::~MenuManager()
	{
		// On parcourt la liste pour désallouer les menus
		std::vector<IMenuScreen*>::iterator it;
		for (it = this->menuScreens.begin(); it < this->menuScreens.end(); it++)
			delete *it;
	}

	EScreenSignal MenuManager::run()
	{
		EMenuScreen screen = SPLASHSCREEN;

		while (screen != EXIT)
			screen = this->menuScreens[screen]->run(&(this->menuResources), SPLASHSCREEN);
		
		return EXITGAME;
	}

	
	EScreenSignal MenuManager::runPause(unsigned int player)
	{
		// TODO
		return EXITMENU;
	}
}
