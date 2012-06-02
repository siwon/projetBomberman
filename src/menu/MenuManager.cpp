/*!
 * \file MenuManager.cpp
 * \brief Gestionnaire du menu
 * \author Maxime GUIHAL
 */

#include "menu/MenuManager.hpp"

#include "IGameInterfaceToMenu.hpp"

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
#include "menu/PauseMenu.hpp"

#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	MenuManager::MenuManager() : window()
	{
		PolyBomberApp::getIControllerToMenu()->setWindow(window.getWindow());

		for (int i=0; i<3; i++)
			this->scores[i] = 0;

		this->winner = -1;

		initMenuConfig();

		// Ajout des menus
		this->menuScreens[SPLASHSCREEN] = new SplashScreen();
		this->menuScreens[MAINMENU] = new MainMenu();
			this->menuScreens[GAMEMENU] = new GameMenu();
				this->menuScreens[CREATEGAMEMENU] = new CreateGameMenu(&menuConfig);
					this->menuScreens[GAMEOPTIONSMENU] = new GameOptionsMenu(&menuConfig);
				this->menuScreens[JOINGAMEMENU] = new JoinGameMenu(&menuConfig);
				this->menuScreens[SELECTSLOTSMENU] = new SelectSlotsMenu(&menuConfig);
				this->menuScreens[SELECTNAMEMENU] = new SelectNameMenu(&menuConfig);
				this->menuScreens[WAITINGMENU] = new WaitingMenu(&menuConfig);

			this->menuScreens[PAUSEMENU] = new PauseMenu();
				
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
		EMenuScreen next;
		EScreenSignal signal;

		IGameInterfaceToMenu* gameInterface = PolyBomberApp::getIGameInterfaceToMenu();
		
		while (screen != EXIT)
		{			
			if (screen != RUNGAME)
			{
				next = this->menuScreens[screen]->run(this->window, old);
				old = screen;
				screen = next;
			}
			else
			{
				signal = gameInterface->run(window.getWindow(), this->scores, this->winner);
				
				if (signal == EXITGAME)
					screen = EXIT;
			}
		}

		PolyBomberApp::getINetworkToMenu()->cancel();
		
		return EXITGAME;
	}

	
	EScreenSignal MenuManager::runPause(unsigned int player)
	{
		EMenuScreen signal = this->menuScreens[PAUSEMENU]->run(this->window, RUNGAME);

		if (signal == EXIT)
			return EXITGAME;
		else
			return EXITMENU;
	}

	void MenuManager::initMenuConfig()
	{
		this->menuConfig.isServer = false;
		this->menuConfig.nbLocalPlayers = 0;

		int nbBonus[18] = {5,3,5,3,1,4,4,1,   7,4,3,2,   3,1,2,2,2,2};
		//int nbBonus[18] =   {0,0,0,0,0,0,0,0,   0,30,0,0,   0,0,0,0,0,0};
		int i;

		this->menuConfig.gameConfig.isLocal = true;
		this->menuConfig.gameConfig.nbPlayers = 2;

		for (i=0; i<4; i++)		
			this->menuConfig.gameConfig.playersName[i] = "";

		for (i=0; i<18; i++)
			this->menuConfig.gameConfig.nbBonus[i] = nbBonus[i];
	}
}
