/*!
 * \file MainMenu.cpp
 * \brief Gestionnaire du menu principal
 * \author Maxime GUIHAL
 */

#include "menu/MainMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	MainMenu::MainMenu()
	{}

	MainMenu::~MainMenu()
	{}

	EMenuScreen MainMenu::run(MainWindow& window, EMenuScreen previous)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		ImageWidget background(skin->loadImage(MENU_BACKGROUND));

		TextWidget title("Menu principal", TITLEFONT, 100);
		title.setColor(skin->getColor(TITLECOLOR));

		LinkWidget play("Jouer", 250, GAMEMENU);		
		LinkWidget options("Options", 300, CONFIGMENU);		
		LinkWidget quit("Quitter", 350, EXIT);

		play.setNext(&options);
		options.setNext(&quit);
		options.setPrevious(&play);
		quit.setPrevious(&options);

		play.setSelected(true);

		this->widgets.push_back(&background);
		this->widgets.push_back(&title);
		this->widgets.push_back(&play);
		this->widgets.push_back(&options);
		this->widgets.push_back(&quit);

		while (true)
		{				
			window.clear();
			window.display(this->widgets);

			if (window.listenCloseButton())
				return EXIT;
	
			EMenuKeys key = MENU_NONE;
			while ((key = controller->getKeyPressed()) == MENU_NONE);

			switch(key)
			{
				case MENU_DOWN:
					quit.goNext();
					options.goNext();
					play.goNext();
					break;
				case MENU_UP:
					play.goPrevious();
					options.goPrevious();
					quit.goPrevious();
					break;
				case MENU_VALID:
					if (play.getSelected())    return play.activate();
					if (options.getSelected()) return options.activate();
					if (quit.getSelected())    return quit.activate();
					break;
				default:
					break;
			}
		}

		return EXIT;
	}
}
