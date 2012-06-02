/*!
 * \file PauseMenu.cpp
 * \brief Gestionnaire du menu pause
 * \author Maxime GUIHAL
 */

#include "menu/PauseMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	PauseMenu::PauseMenu() :
		title("Pause", TITLEFONT, 100),
		resume("Reprendre la partie", 250, RUNGAME),		
		quit("Quitter la partie", 350, EXIT)
	{
		ISkin* skin = PolyBomberApp::getISkin();

		title.setColor(skin->getColor(TITLECOLOR));

		resume.setNext(&quit);
		quit.setPrevious(&resume);

		resume.setSelected(true);

		this->network = PolyBomberApp::getINetworkToMenu();

		this->widgets.push_back(&title);
		this->widgets.push_back(&resume);
		this->widgets.push_back(&quit);
	}

	void PauseMenu::downPressed()
	{
		resume.goNext();
	}

	void PauseMenu::upPressed()
	{
		quit.goPrevious();
	}

	void PauseMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (this->clock.getElapsedTime().asMilliseconds() > 250)
		{
			if (resume.getSelected())
			{
				*nextScreen = resume.activate();
				this->network->resume();
				std::cout << "methode resume appelee" << std::endl;
			}
			
			if (quit.getSelected())
				*nextScreen = quit.activate();
		}
	}
	
	EMenuScreen PauseMenu::run(MainWindow& window, EMenuScreen previous)
	{
		this->resume.setSelected(true);
		this->quit.setSelected(false);
		this->clock.restart();

		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		EMenuScreen nextScreen = NONEMENU;
			
		while (nextScreen == NONEMENU)
		{			
			window.clear();
			window.display(this->widgets);

			EMenuKeys key = MENU_NONE;
			int pause = 0;
			
			while ((key = controller->getKeyPressed()) == MENU_NONE && window.isOpen())
			{
				pause = this->network->isPaused();
				if (pause == 0)
				{
					resume.activate();
					break;
				}
			}

			switch(key)
			{
				case MENU_DOWN:
					downPressed();
					break;
				case MENU_UP:
					upPressed();
					break;
				case MENU_VALID:
					validPressed(&nextScreen);
					break;
				default:
					break;
			}

			if (!window.isOpen())
				nextScreen = EXIT;
		}		

		return nextScreen;
	}
}
