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
		cancel("Annuler", 450, CONTROLLERSCONFIGMENU),
		save("Valider", 450, CONTROLLERSCONFIGMENU)
	{
		ISkin* skin = PolyBomberApp::getISkin();	
		title.setColor(skin->getColor(TITLECOLOR));
		subtitle.setColor(skin->getColor(TEXTCOLOR));

		std::ostringstream text;
		text << "Joueur " << player;

		subtitle.setString(text.str());

		this->widgets.push_back(&title);
		this->widgets.push_back(&subtitle);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&save);

		/*for (int i=0; i<4; i++)
		{
			std::ostringstream text;
			text << "Joueur " << i+1 << " : ";
			playerText[i] = new TextWidget(text.str(), TEXTFONT, 200 + 50*i);
			playerText[i]->setColor(skin->getColor(TEXTCOLOR));	
			playerText[i]->move(-100, 0);

			playerController[i] = new SelectionWidget(LINKFONT, 200 + 50*i);

			playerController[i]->push_back("Clavier");
			playerController[i]->push_back("Gamepad");
			playerController[i]->push_back("Wii");

			playerController[i]->move(100, 0);

			if (i > 0)
				playerController[i]->setPrevious(playerController[i-1]);			

			this->widgets.push_back(playerText[i]);
			this->widgets.push_back(playerController[i]);
		}

		playerController[0]->setNext(playerController[1]);
		playerController[1]->setNext(playerController[2]);
		playerController[2]->setNext(playerController[3]);
		playerController[3]->setNext(&cancel);*/

		cancel.move(-100, 0);
		save.move(100, 0);

		//cancel.setPrevious(playerController[3]);
		cancel.setNext(&save);
			
		//save.setPrevious(playerController[3]);
		save.setNext(&cancel);

		cancel.setSelected(true);
	}

	KeyAssignMenu::~KeyAssignMenu()
	{
		/*for (int i=0; i<4; i++)
		{
			delete playerText[i];
			delete playerController[i];
		}*/
	}

	void KeyAssignMenu::downPressed()
	{
		//for (int i=3; i>=0; i--)
		//	playerController[i]->goNext();
	}

	void KeyAssignMenu::upPressed()
	{
		//for (int i=1; i<4; i++)
		//	playerController[i]->goPrevious();

		cancel.goPrevious();
		save.goPrevious();
	}

	void KeyAssignMenu::leftPressed()
	{
		//IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		for (int i=0; i<4; i++)
		{
			//playerController[i]->goPreviousItem();
			//controller->setPlayerController(i+1, (EControllerType)playerController[i]->getCurrentItem());
		}

		save.goNext();
	}

	void KeyAssignMenu::rightPressed()
	{
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		for (int i=0; i<4; i++)
		{
			//playerController[i]->goNextItem();
			//controller->setPlayerController(i+1, (EControllerType)playerController[i]->getCurrentItem());
		}

		cancel.goNext();
	}

	void KeyAssignMenu::validPressed(EMenuScreen* nextScreen)
	{
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		/*for (int i=0; i<4; i++)
		{
			if (playerController[i]->getSelected())
			{
				*nextScreen = static_cast<EMenuScreen>((int)KEYASSIGNMENU1 + i);
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
		}*/
	}

	void KeyAssignMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}

	EMenuScreen KeyAssignMenu::run(MainWindow& window, EMenuScreen previous)
	{
		initKeys();

		return IMenuScreen::run(window, previous);
	}

	void KeyAssignMenu::initKeys()
	{
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		/*for (int i=0; i<4; i++)
		{
			SKeysConfig keys = controller->getConfig(i + 1);			
			playerController[i]->setCurrentItem(keys.controllerType);
		}*/
	}
}

