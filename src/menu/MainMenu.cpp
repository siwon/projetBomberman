/*!
 * \file MainMenu.cpp
 * \brief Gestionnaire du menu principal
 * \author Maxime GUIHAL
 */

#include "menu/MainMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	MainMenu::MainMenu() :
		title("Menu principal", TITLEFONT, 100),
		play("Jouer", 250, GAMEMENU),		
		options("Options", 300, CONFIGMENU),
		quit("Quitter", 350, EXIT)
	{
		ISkin* skin = PolyBomberApp::getISkin();

		title.setColor(skin->getColor(TITLECOLOR));

		play.setNext(&options);
		options.setNext(&quit);
		options.setPrevious(&play);
		quit.setPrevious(&options);

		play.setSelected(true);

		this->widgets.push_back(&title);
		this->widgets.push_back(&play);
		this->widgets.push_back(&options);
		this->widgets.push_back(&quit);
	}

	void MainMenu::downPressed()
	{
		quit.goNext();
		options.goNext();
		play.goNext();
	}

	void MainMenu::upPressed()
	{
		play.goPrevious();
		options.goPrevious();
		quit.goPrevious();
	}

	void MainMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (play.getSelected())
			*nextScreen = play.activate();
			
		if (options.getSelected())
			*nextScreen = options.activate();
			
		if (quit.getSelected())
			*nextScreen = quit.activate();
	}
}
