/*!
 * \file IMenuScreen.cpp
 * \brief Gestionnaire général des menus
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	IMenuScreen::IMenuScreen()
	{
		ISkin* skin = PolyBomberApp::getISkin();		
		background.setImage(skin->loadImage(MENU_BACKGROUND));
		this->widgets.push_back(&background);
	}

	EMenuScreen IMenuScreen::run(MainWindow& window, EMenuScreen previous)
	{		
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		EMenuScreen nextScreen = NONEMENU;
			
		while (nextScreen == NONEMENU && window.isOpen())
		{			
			window.clear();
			window.display(this->widgets);

			loopAction();

			EMenuKeys key = MENU_NONE;
			while ((key = controller->getKeyPressed()) == MENU_NONE && window.isOpen());

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
}

