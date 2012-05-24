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
		typeText("Type de la partie : ", TEXTFONT, 225, RIGHT),
		playersText("Nombre de joueurs sur cet ordinateur : ", TEXTFONT, 300, RIGHT),
		type(TEXTFONT, 225),
		players(TEXTFONT, 300),
		options("Options de la partie", 375, GAMEOPTIONSMENU),
		cancel("Annuler", 450, GAMEMENU),
		next("Suivant", 450, SELECTNAMEMENU)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));
		typeText.setColor(skin->getColor(TEXTCOLOR));
		playersText.setColor(skin->getColor(TEXTCOLOR));

		type.push_back("locale");
		type.push_back("en reseau");

		players.push_back("1");
		players.push_back("2");
		players.push_back("3");
		players.push_back("4");

		typeText.move(-300, 0);
		playersText.move(-300, 0);
		type.move(200, 0);
		players.move(200, 0);
		cancel.move(-100, 0);
		next.move(100, 0);

		cancel.setSelected(true);

		type.setNext(&players);

		players.setPrevious(&type);
		players.setNext(&options);

		options.setPrevious(&players);
		options.setNext(&cancel);
		
		cancel.setPrevious(&options);
		cancel.setNext(&next);
			
		next.setPrevious(&options);
		next.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&typeText);
		this->widgets.push_back(&playersText);
		this->widgets.push_back(&type);
		this->widgets.push_back(&players);
		this->widgets.push_back(&options);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&next);
	}

	void CreateGameMenu::downPressed()
	{
		options.goNext();
		players.goNext();
		type.goNext();
	}

	void CreateGameMenu::upPressed()
	{
		players.goPrevious();
		options.goPrevious();
		cancel.goPrevious();
		next.goPrevious();
	}

	void CreateGameMenu::leftPressed()
	{
		type.goPreviousItem();
		players.goPreviousItem();
		next.goNext();
	}

	void CreateGameMenu::rightPressed()
	{
		type.goNextItem();
		players.goNextItem();
		cancel.goNext();
	}

	void CreateGameMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (cancel.getSelected())
			*nextScreen = cancel.activate();

		if (options.getSelected())
			*nextScreen = options.activate();
		
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
