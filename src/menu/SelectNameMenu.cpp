/*!
 * \file SelectNameMenu.cpp
 * \brief Gestionnaire du menu de sélection des noms des joueurs
 * \author Maxime GUIHAL
 */

#include <sstream>

#include "menu/SelectNameMenu.hpp"
#include "PolyBomberApp.hpp"
#include "INetworkToMenu.hpp"

namespace PolyBomber
{
	SelectNameMenu::SelectNameMenu(SMenuConfig* menuConfig) :
		title("Noms des joueurs", TITLEFONT, 100),
		error("Noms des joueurs invalides", TEXTFONT, 200),
		cancel("Annuler", 450, GAMEMENU),
		next("Suivant", 450, WAITINGMENU),
		menuConfig(menuConfig)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));

		cancel.move(-100, 0);
		next.move(100, 0);

		cancel.setSelected(true);
		
		cancel.setNext(&next);
		next.setNext(&cancel);

		error.setVisible(false);

		this->widgets.push_back(&title);
		this->widgets.push_back(&error);
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
			this->names[i]->move(100, 0);

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
		for (int i=3; i>=0; i--)
			this->names[i]->goNext();
	}

	void SelectNameMenu::upPressed()
	{
		for (int i=0; i<4; i++)
			this->names[i]->goPrevious();

		cancel.goPrevious();
		next.goPrevious();
		error.setVisible(false);
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
		INetworkToMenu* network = PolyBomberApp::getINetworkToMenu();

		if (cancel.getSelected())
		{
			for (int i=0; i<4; i++)
				this->names[i]->clear();
			
			network->cancel();
			*nextScreen = cancel.activate();
		}
		
		if (next.getSelected())
		{						
			try
			{
				std::string names[4] = {"", "", "", ""};
				bool error = false;
				
				for (unsigned int i=0; i<this->menuConfig->nbLocalPlayers; i++)
				{
					names[i] = this->names[i]->getString();
					if (names[i].compare("") == 0) error = true;
				}

				if (!error)
				{
					network->setPlayerName(names);				
					*nextScreen = next.activate();
				}
				else
					this->error.setVisible(true);
			}
			catch (PolyBomberException& e)
			{
				std::cerr << e.what() << std::endl;
				//FIXME: msg err
				network->cancel();
				*nextScreen = cancel.activate();
			}
		}
	}

	void SelectNameMenu::backPressed(EMenuScreen* nextScreen)
	{
		INetworkToMenu* network = PolyBomberApp::getINetworkToMenu();
		network->cancel();
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
		unsigned int nb = this->menuConfig->nbLocalPlayers;

		for (unsigned int i=0; i<nb; i++)
		{
			this->nameTexts[i]->setVisible(true);
			this->names[i]->setVisible(true);

			if (i < nb - 1)
				this->names[i]->setNext(this->names[i + 1]);
	
			if (i > 0)
				this->names[i]->setPrevious(this->names[i - 1]);
		}

		this->names[nb - 1]->setNext(&cancel);
		cancel.setPrevious(this->names[nb - 1]);
		next.setPrevious(this->names[nb - 1]);
	}

	void SelectNameMenu::loopAction()
	{
		for (int i=0; i<4; i++)
			this->names[i]->writeChar();
	}
}
