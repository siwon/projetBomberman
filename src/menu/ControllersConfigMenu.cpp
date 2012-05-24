/*!
 * \file ControllersConfigMenu.cpp
 * \brief Gestionnaire du menu de configuration des contrôleurs
 * \author Maxime GUIHAL
 */

#include <sstream>

#include "menu/ControllersConfigMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	ControllersConfigMenu::ControllersConfigMenu() :
		title("Configuration des controleurs", TITLEFONT, 100),
		error("Aucun controleur detecte", TEXTFONT, 200),
		cancel("Annuler", 500, CONFIGMENU),
		save("Valider", 500, CONFIGMENU)
	{
		ISkin* skin = PolyBomberApp::getISkin();	
		title.setColor(skin->getColor(TITLECOLOR));
		error.setColor(skin->getColor(ERRORCOLOR));

		this->widgets.push_back(&title);
		this->widgets.push_back(&error);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&save);

		error.setVisible(false);

		for (int i=0; i<4; i++)
		{
			std::ostringstream text;
			text << "Joueur " << i+1 << " : ";
			playerText[i] = new TextWidget(text.str(), TEXTFONT, 250 + 50*i);
			playerText[i]->setColor(skin->getColor(TEXTCOLOR));
			playerText[i]->move(-100, 0);

			playerController[i] = new SelectionWidget(LINKFONT, 250 + 50*i);

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
		playerController[3]->setNext(&cancel);

		cancel.move(-100, 0);
		save.move(100, 0);

		cancel.setPrevious(playerController[3]);
		cancel.setNext(&save);
			
		save.setPrevious(playerController[3]);
		save.setNext(&cancel);

		cancel.setSelected(true);
	}

	ControllersConfigMenu::~ControllersConfigMenu()
	{
		for (int i=0; i<4; i++)
		{
			delete playerText[i];
			delete playerController[i];
		}
	}

	void ControllersConfigMenu::downPressed()
	{
		for (int i=3; i>=0; i--)
			playerController[i]->goNext();

		error.setVisible(false);
	}

	void ControllersConfigMenu::upPressed()
	{
		for (int i=1; i<4; i++)
			playerController[i]->goPrevious();

		cancel.goPrevious();
		save.goPrevious();

		error.setVisible(false);
	}

	void ControllersConfigMenu::leftPressed()
	{
		error.setVisible(false);
		changeController(false);
		save.goNext();		
	}

	void ControllersConfigMenu::rightPressed()
	{
		error.setVisible(false);
		changeController(true);
		cancel.goNext();
	}

	void ControllersConfigMenu::validPressed(EMenuScreen* nextScreen)
	{
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		for (int i=0; i<4; i++)
		{
			if (playerController[i]->getSelected())
				*nextScreen = static_cast<EMenuScreen>((int)KEYASSIGNMENU1 + i);
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

	void ControllersConfigMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}

	EMenuScreen ControllersConfigMenu::run(MainWindow& window, EMenuScreen previous)
	{
		initControllers();
		return IMenuScreen::run(window, previous);
	}

	void ControllersConfigMenu::initControllers()
	{
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		for (int i=0; i<4; i++)
		{
			SKeysConfig keys = controller->getConfig(i + 1);			
			playerController[i]->setCurrentItem(keys.controllerType);
		}
	}

	void ControllersConfigMenu::changeController(bool next)
	{
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		try
		{
			for (int i=0; i<4; i++)
			{
				if (next)
					playerController[i]->goNextItem();
				else
					playerController[i]->goPreviousItem();
					
				controller->setPlayerController(i+1, (EControllerType)playerController[i]->getCurrentItem());
			}
		}
		catch (...)
		{
			error.setVisible(true);

			// On inverse la sélection
			for (int i=0; i<4; i++)
			{
				if (playerController[i]->getSelected())
				{
					if (!next)
						playerController[i]->goNextItem();
					else
						playerController[i]->goPreviousItem();
				}
			}
		}
	}
}

