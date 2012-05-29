/*!
 * \file SelectSlotsMenu.cpp
 * \brief Gestionnaire du menu pour rejoindre une partie
 * \author Maxime GUIHAL
 */

#include "menu/SelectSlotsMenu.hpp"
#include "PolyBomberApp.hpp"
#include "INetworkToMenu.hpp"

namespace PolyBomber
{
	SelectSlotsMenu::SelectSlotsMenu(SMenuConfig* menuConfig) :
		title("Creation d'une partie", TITLEFONT, 100),
		error("Pas assez de place sur le serveur", TEXTFONT, 300),
		nbPlayersText("Nombre de joueurs sur cet ordinateur :", TEXTFONT, 250),
		nbPlayers(TEXTFONT, 300),
		cancel("Annuler", 450, NONEMENU),
		next("Valider", 450, SELECTNAMEMENU),
		menuConfig(menuConfig)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));
		error.setColor(skin->getColor(ERRORCOLOR));
		nbPlayersText.setColor(skin->getColor(TEXTCOLOR));

		cancel.move(-100, 0);
		next.move(100, 0);

		nbPlayers.push_back("1");
		nbPlayers.setCurrentItem(0);

		error.setVisible(false);

		cancel.setSelected(true);

		nbPlayers.setNext(&cancel);
		cancel.setPrevious(&nbPlayers);
		next.setPrevious(&nbPlayers);
		cancel.setNext(&next);
		next.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&error);
		this->widgets.push_back(&nbPlayersText);
		this->widgets.push_back(&nbPlayers);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&next);

		this->network = PolyBomberApp::getINetworkToMenu();
	}

	void SelectSlotsMenu::downPressed()
	{
		nbPlayers.goNext();
	}

	void SelectSlotsMenu::upPressed()
	{
		cancel.goPrevious();
		next.goPrevious();
		error.setVisible(false);
	}

	void SelectSlotsMenu::leftPressed()
	{
		nbPlayers.goPreviousItem();
		next.goNext();
	}

	void SelectSlotsMenu::rightPressed()
	{
		nbPlayers.goNextItem();
		cancel.goNext();
	}

	void SelectSlotsMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (cancel.getSelected())
		{
			this->network->cancel();
			*nextScreen = cancel.activate();
		}
		
		if (next.getSelected())
		{				
			if (this->network->getFreeSlots() <= (int)nbPlayers.getCurrentItem())
				error.setVisible(true);
			else
			{			
				this->network->setBookedSlots(nbPlayers.getCurrentItem() + 1);
				this->menuConfig->nbLocalPlayers = nbPlayers.getCurrentItem() + 1;
				*nextScreen = next.activate();
			}
		}
	}

	void SelectSlotsMenu::backPressed(EMenuScreen* nextScreen)
	{
		this->network->cancel();
		*nextScreen = cancel.activate();
	}

	EMenuScreen SelectSlotsMenu::run(MainWindow& window, EMenuScreen previous)
	{
		// Gestion d'une partie locale
		if (this->menuConfig->gameConfig.isLocal)
		{
			this->menuConfig->nbLocalPlayers = this->menuConfig->gameConfig.nbPlayers;
			this->network->setBookedSlots(this->menuConfig->nbLocalPlayers);
			return next.activate();
		}

		cancel.setTarget(previous);

		if (previous == CREATEGAMEMENU)
			title.setString("Creation d'une partie");
		else
			title.setString("Rejoindre une partie");

		return IMenuScreen::run(window, previous);
	}

	void SelectSlotsMenu::loopAction()
	{
		int nb = this->network->getFreeSlots();
		int sel = nbPlayers.getCurrentItem();

		std::cout << "free slots : " << nb << std::endl;

		nbPlayers.clear();

		error.setVisible(nb == 0);
		nbPlayers.setVisible(nb > 0);
		next.setVisible(nb > 0);
		
		if (nb > 0)
			nbPlayers.push_back("1");
		else
			cancel.setSelected(true);
			
		if (nb > 1)	nbPlayers.push_back("2");
		if (nb > 2)	nbPlayers.push_back("3");
		if (nb > 3)	nbPlayers.push_back("4");

		if (nb <= sel && nb > 0)
			nbPlayers.setCurrentItem(nb - 1);
		else
			nbPlayers.setCurrentItem(sel);
	}
}
