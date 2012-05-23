/*!
 * \file CreateGameMenu.cpp
 * \brief Gestionnaire du menu de création d'une partie
 * \author Maxime GUIHAL
 */

#include "menu/CreateGameMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	CreateGameMenu::CreateGameMenu() :
		title("Creation d'une partie", TITLEFONT, 100),
		cancel("Annuler", 450, GAMEMENU),
		next("Suivant", 450, SELECTSLOTSMENU)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));

		cancel.move(-100, 0);
		next.move(100, 0);

		cancel.setSelected(true);
		
		//cancel.setPrevious(&musicVolume);
		cancel.setNext(&next);
			
		//save.setPrevious(&musicVolume);
		next.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&next);
	}

	void CreateGameMenu::downPressed()
	{

	}

	void CreateGameMenu::upPressed()
	{
		cancel.goPrevious();
		next.goPrevious();
	}

	void CreateGameMenu::leftPressed()
	{
		
	}

	void CreateGameMenu::rightPressed()
	{
		
	}

	void CreateGameMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (cancel.getSelected())
		{
			*nextScreen = cancel.activate();
		}
		
		if (next.getSelected())
		{						
			*nextScreen = next.activate();
		}
	}

	void CreateGameMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}

	EMenuScreen CreateGameMenu::run(MainWindow& window, EMenuScreen previous)
	{
		return IMenuScreen::run(window, previous);
	}
}
