/*!
 * \file CreateGameMenu.cpp
 * \brief Gestionnaire du menu de création d'une partie
 * \author Maxime GUIHAL
 */

#include <sstream>

#include "menu/CreateGameMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	CreateGameMenu::CreateGameMenu(SGameConfig* gameConfig) :
		title("Creation d'une partie", TITLEFONT, 100),
		typeText("Type de la partie : ", TEXTFONT, 225, RIGHT),
		playersText("Nombre de joueurs sur cet ordinateur : ", TEXTFONT, 300, RIGHT),
		type(TEXTFONT, 225),
		players(TEXTFONT, 300),
		options("Options de la partie", 375, GAMEOPTIONSMENU),
		cancel("Annuler", 450, GAMEMENU),
		next("Suivant", 450, SELECTNAMEMENU),
		gameConfig(gameConfig)
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

		initGameConfig();
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

		changePlayers();
	}

	void CreateGameMenu::rightPressed()
	{
		type.goNextItem();
		players.goNextItem();
		cancel.goNext();

		changePlayers();
	}

	void CreateGameMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (cancel.getSelected())
		{
			*nextScreen = cancel.activate();
			initGameConfig();
		}

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
		initWidgets();
		return IMenuScreen::run(window, previous);
	}

	void CreateGameMenu::changePlayers()
	{
		if (type.getSelected())
		{
			players.clear();
			players.push_back("1");
			players.push_back("2");
			players.push_back("3");
			
			if (!type.getCurrentItem())
				players.push_back("4");
		}

		this->gameConfig->isLocal = !type.getCurrentItem();
		this->gameConfig->nbPlayers = players.getCurrentItem() + 1;
	}

	void CreateGameMenu::initGameConfig()
	{
		int nbBonus[18] = {5,3,5,3,1,4,4,1,   7,4,3,2,   3,1,2,2,2,2};
		int i;

		this->gameConfig->isLocal = true;
		this->gameConfig->nbPlayers = 1;

		for (i=0; i<4; i++)
		{
			std::ostringstream text;
			text << "Joueur " << (i+1);
			this->gameConfig->playersName[i] = text.str();
		}

		for (i=0; i<18; i++)
			this->gameConfig->nbBonus[i] = nbBonus[i];
	}

	void CreateGameMenu::initWidgets()
	{
		type.setCurrentItem(!this->gameConfig->isLocal);
		changePlayers();
		players.setCurrentItem(this->gameConfig->nbPlayers - 1);
	}
}
