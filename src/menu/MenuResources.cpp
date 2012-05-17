/*!
 * \file MenuResources.cpp
 * \brief Gestionnaire des ressources du menu
 * \author Maxime GUIHAL
 */

#include "PolyBomberApp.hpp"
#include "menu/MenuResources.hpp"

namespace PolyBomber
{
	MenuResources::MenuResources() : window()
	{
		initInterfaces();
	}

	MenuResources::~MenuResources()
	{}

	MenuResources::MenuResources(const MenuResources& obj)
	{
		initInterfaces();
		this->window = obj.window;
	}

	MenuResources& MenuResources::operator=(const MenuResources& obj)
	{
		initInterfaces();
		this->window = obj.window;
		return *this;
	}

	void MenuResources::initInterfaces()
	{
		//this->gameInterfaceToMenu = PolyBomberApp::getIGameInterfaceToMenu();
		//this->networkToMenu = PolyBomberApp::getINetworkToMenu();
		this->skin = PolyBomberApp::getISkin();
		this->sound = PolyBomberApp::getISound();
	}

	MainWindow& MenuResources::getWindow()
	{
		return this->window;
	}

	IGameInterfaceToMenu* MenuResources::getGameInterfaceToMenu()
	{
		return this->gameInterfaceToMenu;
	}
	
	INetworkToMenu* MenuResources::getNetworkToMenu()
	{
		return this->networkToMenu;
	}
	
	ISkin* MenuResources::getSkin()
	{
		return this->skin;
	}
	
	ISound* MenuResources::getSound()
	{
		return this->sound;
	}
}

