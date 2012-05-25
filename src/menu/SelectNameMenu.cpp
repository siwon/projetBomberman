/*!
 * \file SelectNameMenu.cpp
 * \brief Gestionnaire du menu de sélection des noms des joueurs
 * \author Maxime GUIHAL
 */

#include <sstream>

#include "menu/SelectNameMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	SelectNameMenu::SelectNameMenu(SGameConfig* gameConfig) :
		title("Noms des joueurs", TITLEFONT, 100),
		cancel("Annuler", 450, CREATEGAMEMENU),
		next("Suivant", 450, WAITINGMENU),
		gameConfig(gameConfig)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));

		cancel.move(-100, 0);
		next.move(100, 0);

		cancel.setSelected(true);
		
		cancel.setNext(&next);
		next.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&next);
		
		for (int i=0; i<4; i++)
		{
			std::ostringstream text;
			text << "Joueur " << (i+1) << " : ";

			this->nameTexts[i] = new TextWidget(text.str(), TEXTFONT, 200 + 60*i);		
			this->nameTexts[i]->setColor(skin->getColor(TEXTCOLOR));
			this->nameTexts[i]->move(-200, 0);

			this->names[i] = new InputWidget(TEXTFONT, 195 + 60*i);

			this->widgets.push_back(this->nameTexts[i]);
			this->widgets.push_back(this->names[i]);
		}
	}

	SelectNameMenu::~SelectNameMenu()
	{
		for (int i=0; i<4; i++)
		{
			delete nameTexts[i];
			delete names[i];
		}
	}

	void SelectNameMenu::downPressed()
	{

	}

	void SelectNameMenu::upPressed()
	{
		cancel.goPrevious();
		next.goPrevious();
	}

	void SelectNameMenu::leftPressed()
	{
		next.goNext();
	}

	void SelectNameMenu::rightPressed()
	{
		cancel.goNext();
	}

	void SelectNameMenu::validPressed(EMenuScreen* nextScreen)
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

	void SelectNameMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}

	EMenuScreen SelectNameMenu::run(MainWindow& window, EMenuScreen previous)
	{
		for (int i=0; i<4; i++)
		{
			nameTexts[i]->setVisible(false);
			names[i]->setVisible(false);
		}

		initWidgets();

		return IMenuScreen::run(window, previous);
	}

	void SelectNameMenu::initWidgets()
	{
		for (unsigned int i=0; i<this->gameConfig->nbPlayers; i++)
		{
			this->nameTexts[i]->setVisible(true);
			this->names[i]->setVisible(true);
		}
	}
}
