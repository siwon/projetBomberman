/*!
 * \file PolyBomberApp.cpp
 * \brief Classe contenant le programme
 * \author Maxime GUIHAL
 */

#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	MenuManager* PolyBomberApp::menuManager = NULL;
	GameInterfaceManager* PolyBomberApp::gameInterfaceManager = NULL;
	NetworkManager* PolyBomberApp::networkManager = NULL;
	//GameEngineManager* PolyBomberApp::gameEngineManager = NULL;
	ControllerManager* PolyBomberApp::controllerManager = NULL;
	SoundManager* PolyBomberApp::soundManager = NULL;
	SkinManager* PolyBomberApp::skinManager = NULL;

	PolyBomberApp::PolyBomberApp()
	{
		PolyBomberApp::menuManager = MenuManager::getInstance();
		PolyBomberApp::gameInterfaceManager = GameInterfaceManager::getInstance();
		PolyBomberApp::networkManager = NetworkManager::getInstance();
		//PolyBomberApp::gameEngineManager = GameEngineManager::getInstance();
		PolyBomberApp::controllerManager = ControllerManager::getInstance();
		PolyBomberApp::soundManager = SoundManager::getInstance();
		PolyBomberApp::skinManager = SkinManager::getInstance();
	}

	PolyBomberApp::~PolyBomberApp()
	{
		MenuManager::kill();
		GameInterfaceManager::kill();
		NetworkManager::kill();
		//GameEngineManager::kill();
		ControllerManager::kill();
		SoundManager::kill();
		SkinManager::kill();
	}

	IControllerToMenu* PolyBomberApp::getIControllerToMenu()
	{
		return static_cast<IControllerToMenu*>(PolyBomberApp::controllerManager);
	}
	
	IControllerToNetwork* PolyBomberApp::getIControllerToNetwork()
	{
		return static_cast<IControllerToNetwork*>(PolyBomberApp::controllerManager);
	}
	
	/*IGameEngineToNetwork* PolyBomberApp::getIGameEngineToNetwork()
	{
		return static_cast<IGameEngineToNetwork*>(PolyBomberApp::gameEngineManager);
	}*/
			
	INetworkToGameEngine* PolyBomberApp::getINetworkToGameEngine()
	{
		return static_cast<INetworkToGameEngine*>(PolyBomberApp::networkManager);
	}
	
	INetworkToGameInterface* PolyBomberApp::getINetworkToGameInterface()
	{
		return static_cast<INetworkToGameInterface*>(PolyBomberApp::networkManager);
	}
	
	INetworkToMenu* PolyBomberApp::getINetworkToMenu()
	{
		return static_cast<INetworkToMenu*>(PolyBomberApp::networkManager);
	}
		
	IMenuToGameInterface* PolyBomberApp::getIMenuToGameInterface()
	{
		return static_cast<IMenuToGameInterface*>(PolyBomberApp::menuManager);
	}

	IMenuToMain* PolyBomberApp::getIMenuToMain()
	{
		return static_cast<IMenuToMain*>(PolyBomberApp::menuManager);
	}
			
	IGameInterfaceToMenu* PolyBomberApp::getIGameInterfaceToMenu()
	{
		return static_cast<IGameInterfaceToMenu*>(PolyBomberApp::gameInterfaceManager);
	}
				
	ISkin* PolyBomberApp::getISkin()
	{
		return static_cast<ISkin*>(PolyBomberApp::skinManager);
	}
			
	ISound* PolyBomberApp::getISound()
	{
		return static_cast<ISound*>(PolyBomberApp::soundManager);
	}

	int PolyBomberApp::run()
	{
		IMenuToMain* menu = PolyBomberApp::getIMenuToMain();
		return menu->run();
	}	
}



