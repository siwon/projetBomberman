/*!
 * \file WaitingMenu.cpp
 * \brief Gestionnaire du menu d'attente de début de partie
 * \author Maxime GUIHAL
 */

#include "menu/WaitingMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	WaitingMenu::WaitingMenu(SMenuConfig* menuConfig) :
		title("Resume de la partie", TITLEFONT, 50),
		ip("Adresse IP du serveur : ", TEXTFONT, 150),
		cancel("Annuler", 500, GAMEMENU),
		start("Jouer !", 500, RUNGAME),
		menuConfig(menuConfig)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));
		ip.setColor(skin->getColor(TEXTCOLOR));

		this->network = PolyBomberApp::getINetworkToMenu();
		ip.setString(ip.getString() + this->network->getIpAddress());
		
		ip.move(-80, 0);
		
		cancel.move(-100, 0);
		start.move(100, 0);

		cancel.setSelected(true);
		cancel.setNext(&start);
		start.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&ip);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&start);

		for (int i=0; i<4; i++)
		{
			this->pictures[i] = new ImageWidget();
			this->pictures[i]->setPosition(300, 200 + 60*i);				
			this->pictures[i]->setImage(skin->loadImage((EImage)(PLAYER1 + i)));				

			this->names[i] = new TextWidget("...", TEXTFONT, 210 + 60*i);
			this->names[i]->setColor(skin->getColor(TEXTCOLOR));
			this->names[i]->move(100, 0);

			this->widgets.push_back(this->pictures[i]);
			this->widgets.push_back(this->names[i]);
		}
	}

	void WaitingMenu::leftPressed()
	{
		start.goNext();
	}

	void WaitingMenu::rightPressed()
	{
		cancel.goNext();
	}

	void WaitingMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (cancel.getSelected())
		{
			this->network->cancel();
			*nextScreen = cancel.activate();
		}
		
		if (start.getSelected())
		{						
			//this->network->startGame();
			*nextScreen = start.activate();
		}
	}

	void WaitingMenu::backPressed(EMenuScreen* nextScreen)
	{
		this->network->cancel();
		*nextScreen = cancel.activate();
	}

	void WaitingMenu::update()
	{
		try
		{
			std::string names[4] = {"", "", "", ""};
			this->network->getPlayersName(names);

			for (unsigned int i=0; i<this->menuConfig->gameConfig.nbPlayers; i++)
			{
				if (names[i].compare("None") == 0 || names[i].compare("") == 0)
					this->names[i]->setString("...");
				else
					this->names[i]->setString(names[i]);
			}
		}
		catch (PolyBomberException& e)
		{
			std::cerr << e.what() << std::endl;
		}

	}

	EMenuScreen WaitingMenu::run(MainWindow& window, EMenuScreen)
	{
		initWidgets();

		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		EMenuScreen nextScreen = NONEMENU;
			
		while (nextScreen == NONEMENU)
		{			
			window.clear();
			window.display(this->widgets);

			EMenuKeys key = MENU_NONE;
			while ((key = controller->getKeyPressed()) == MENU_NONE && window.isOpen())
			{
				update();
				window.clear();
				window.display(this->widgets);
			}

			switch(key)
			{
				case MENU_DOWN:
					downPressed();
					break;
				case MENU_UP:
					upPressed();
					break;
				case MENU_LEFT:
					leftPressed();
					break;
				case MENU_RIGHT:
					rightPressed();
					break;
				case MENU_VALID:
					validPressed(&nextScreen);
					break;
				case MENU_BACK:
					backPressed(&nextScreen);
					break;
				default:
					break;
			}

			if (!window.isOpen())
				nextScreen = EXIT;
		}

		return nextScreen;
	}

	void WaitingMenu::initWidgets()
	{
		// On récupère le nombre de joueurs sur la partie si on est client
		if (!menuConfig->isServer)
		{
			unsigned int nb = 0;

			try
			{
				std::string names[4] = {"", "", "", ""};
				this->network->getPlayersName(names);
				while (names[nb].compare("") != 0)
					nb++;
			}
			catch (PolyBomberException& e)
			{
				std::cerr << e.what() << std::endl;
				this->network->cancel();
				// FIXME: Changer de menu
			}

			this->menuConfig->gameConfig.nbPlayers = nb;
		}

		for (unsigned int i=0; i<4; i++)
		{
			this->pictures[i]->setVisible(i < this->menuConfig->gameConfig.nbPlayers);
			this->names[i]->setVisible(i < this->menuConfig->gameConfig.nbPlayers);
		}

		ip.setVisible(this->menuConfig->isServer && !this->menuConfig->gameConfig.isLocal);
		start.setVisible(this->menuConfig->isServer);

		if (this->menuConfig->isServer && !this->menuConfig->gameConfig.isLocal)
			cancel.setNext(&start);
		else
			cancel.setNext(NULL);
	}
}
