/*!
 * \file JoinGameMenu.cpp
 * \brief Gestionnaire du menu pour rejoindre une partie
 * \author Maxime GUIHAL
 */

#include "menu/JoinGameMenu.hpp"
#include "PolyBomberApp.hpp"
#include "INetworkToMenu.hpp"

namespace PolyBomber
{
	JoinGameMenu::JoinGameMenu(SMenuConfig* menuConfig) :
		title("Rejoindre une partie", TITLEFONT, 100),
		error("Impossible de se connecter au serveur", TEXTFONT, 200),
		ipText("Adresse IP du serveur :", TEXTFONT, 250),
		ipInput(TEXTFONT, 300, CENTER, 190),
		cancel("Annuler", 450, GAMEMENU),
		next("Connexion", 450, SELECTSLOTSMENU),
		menuConfig(menuConfig)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));
		error.setColor(skin->getColor(ERRORCOLOR));
		ipText.setColor(skin->getColor(TEXTCOLOR));

		cancel.move(-100, 0);
		next.move(100, 0);

		error.setVisible(false);

		ipInput.setMaxLength(15);

		cancel.setSelected(true);

		ipInput.setNext(&cancel);
		cancel.setPrevious(&ipInput);
		next.setPrevious(&ipInput);
		cancel.setNext(&next);
		next.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&error);
		this->widgets.push_back(&ipText);
		this->widgets.push_back(&ipInput);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&next);
	}

	void JoinGameMenu::downPressed()
	{
		ipInput.goNext();
	}

	void JoinGameMenu::upPressed()
	{
		cancel.goPrevious();
		next.goPrevious();
		error.setVisible(false);
	}

	void JoinGameMenu::leftPressed()
	{
		next.goNext();
	}

	void JoinGameMenu::rightPressed()
	{
		cancel.goNext();
	}

	void JoinGameMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (cancel.getSelected())
			*nextScreen = cancel.activate();
		
		if (next.getSelected())
		{				
			try
			{
				INetworkToMenu* network = PolyBomberApp::getINetworkToMenu();
				network->joinGame(ipInput.getString());
				
				this->menuConfig->isServer = false;
				this->menuConfig->gameConfig.isLocal = false;
				*nextScreen = next.activate();
			}
			catch (PolyBomberException& e)
			{
				error.setVisible(true);
				std::cout << e.what() << std::endl;
			}			
		}
	}

	void JoinGameMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}

	void JoinGameMenu::loopAction(EMenuScreen*)
	{
		ipInput.writeChar();
	}
}
