/*!
 * \file KeyAssignMenu.cpp
 * \brief Gestionnaire du menu d'assignation des touches
 * \author Maxime GUIHAL
 */

#include <sstream>

#include "menu/KeyAssignMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	KeyAssignMenu::KeyAssignMenu(unsigned int player) :
		title("Configuration des touches", TITLEFONT, 50),
		subtitle("Joueur 1", TITLEFONT, 100),
		errorKey("La touche est deja utilisee", TEXTFONT, 170),
		cancel("Annuler", 550, CONTROLLERSCONFIGMENU),
		save("Valider", 550, CONTROLLERSCONFIGMENU),
		player(player)
	{
		ISkin* skin = PolyBomberApp::getISkin();	
		title.setColor(skin->getColor(TITLECOLOR));
		subtitle.setColor(skin->getColor(TEXTCOLOR));
		errorKey.setColor(skin->getColor(ERRORCOLOR));

		std::ostringstream text;
		text << "Joueur " << player;

		subtitle.setString(text.str());

		this->errorXPos = errorKey.getPosition().x;

		this->widgets.push_back(&title);
		this->widgets.push_back(&subtitle);
		this->widgets.push_back(&errorKey);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&save);

		std::string actions[7] = {"Haut :", "Bas :", "Gauche :", "Droite :",
								  "Action 1 :", "Action 2 :", "Pause :"};

		for (int i=0; i<7; i++)
		{
			actionText[i] = new TextWidget(actions[i], TEXTFONT, 220 + 45*i, RIGHT);
			actionText[i]->setColor(skin->getColor(TEXTCOLOR));	
			actionText[i]->move(-420, 0);

			keyText[i] = new LinkWidget("touche", 220 + 45*i, NONEMENU);
			keyText[i]->move(70, 0);

			if (i > 0)
				keyText[i]->setPrevious(keyText[i-1]);
			
			this->widgets.push_back(actionText[i]);
			this->widgets.push_back(keyText[i]);
		}

		cancel.move(-100, 0);
		save.move(100, 0);

		for (int i=0; i<6; i++)
			keyText[i]->setNext(keyText[i+1]);

		keyText[6]->setNext(&cancel);		

		cancel.setPrevious(keyText[6]);
		cancel.setNext(&save);
			
		save.setPrevious(keyText[6]);
		save.setNext(&cancel);

		cancel.setSelected(true);

		this->window = NULL;
	}

	KeyAssignMenu::~KeyAssignMenu()
	{
		for (int i=0; i<7; i++)
		{
			delete actionText[i];
			delete keyText[i];
		}
	}

	void KeyAssignMenu::downPressed()
	{
		for (int i=6; i>=0; i--)
			keyText[i]->goNext();
	}

	void KeyAssignMenu::upPressed()
	{
		for (int i=1; i<7; i++)
			keyText[i]->goPrevious();

		cancel.goPrevious();
		save.goPrevious();
	}

	void KeyAssignMenu::leftPressed()
	{
		save.goNext();
	}

	void KeyAssignMenu::rightPressed()
	{
		cancel.goNext();
	}

	void KeyAssignMenu::validPressed(EMenuScreen* nextScreen)
	{
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		for (int i=0; i<7; i++)
		{
			if (keyText[i]->getSelected())
			{
				keyText[i]->setString("...");
				errorKey.setPosition(this->errorXPos, -100);

				this->window->clear();
				this->window->display(this->widgets);
				
				SKeysConfig k = controller->setPlayerKey(this->player, (EGameKeys)i);

				for (int j=0; j<7; j++)					
				{
					if (k.errors[j].compare("") != 0)
						errorKey.setPosition(this->errorXPos, 170);
				}
				
				initKeys();
			}
		}

		if (cancel.getSelected())
		{
			controller->reloadConfig();
			*nextScreen = cancel.activate();
		}
		
		if (save.getSelected())
		{						
			controller->save();
			*nextScreen = save.activate();
		}
	}

	void KeyAssignMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}

	EMenuScreen KeyAssignMenu::run(MainWindow& window, EMenuScreen previous)
	{
		this->window = &window;

		errorKey.setPosition(this->errorXPos, -100);
		
		initKeys();

		return IMenuScreen::run(window, previous);
	}

	void KeyAssignMenu::initKeys()
	{
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		SKeysConfig keys = controller->getConfig(this->player);

		for(int i=0; i<7; i++)		
			keyText[i]->setString(keys.keys[i]);
	}
}

