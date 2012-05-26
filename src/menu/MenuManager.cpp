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
#include "menu/SoundConfigMenu.hpp"
#include "menu/ControllersConfigMenu.hpp"
#include "menu/KeyAssignMenu.hpp"
#include "menu/CreateGameMenu.hpp"
#include "menu/GameOptionsMenu.hpp"
#include "menu/SelectNameMenu.hpp"
#include "menu/WaitingMenu.hpp"
#include "menu/JoinGameMenu.hpp"
#include "menu/SelectSlotsMenu.hpp"

#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	MenuManager::MenuManager() : window()
	{
		PolyBomberApp::getIControllerToMenu()->setWindow(window.getWindow());

		// Ajout des menus
		this->menuScreens[SPLASHSCREEN] = new SplashScreen();
		this->menuScreens[MAINMENU] = new MainMenu();
			this->menuScreens[GAMEMENU] = new GameMenu();
				this->menuScreens[CREATEGAMEMENU] = new CreateGameMenu(&gameConfig);
					this->menuScreens[GAMEOPTIONSMENU] = new GameOptionsMenu(&gameConfig);
					this->menuScreens[SELECTNAMEMENU] = new SelectNameMenu(&gameConfig);
					this->menuScreens[WAITINGMENU] = new WaitingMenu(&gameConfig);
				this->menuScreens[JOINGAMEMENU] = new JoinGameMenu();
					this->menuScreens[SELECTSLOTSMENU] = new SelectSlotsMenu();
				
			this->menuScreens[CONFIGMENU] = new ConfigMenu();
				this->menuScreens[GRAPHICSCONFIGMENU] = new GraphicsConfigMenu();
				this->menuScreens[SOUNDCONFIGMENU] = new SoundConfigMenu();
				this->menuScreens[CONTROLLERSCONFIGMENU] = new ControllersConfigMenu();
					this->menuScreens[KEYASSIGNMENU1] = new KeyAssignMenu(1);
					this->menuScreens[KEYASSIGNMENU2] = new KeyAssignMenu(2);
					this->menuScreens[KEYASSIGNMENU3] = new KeyAssignMenu(3);
					this->menuScreens[KEYASSIGNMENU4] = new KeyAssignMenu(4);
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
		// TODO: Coder la pause
		return EXITMENU;
	}
}
