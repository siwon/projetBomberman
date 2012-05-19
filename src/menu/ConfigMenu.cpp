/*!
 * \file ConfigMenu.cpp
 * \brief Gestionnaire du menu de jeu
 * \author Maxime GUIHAL
 */

#include "menu/ConfigMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	ConfigMenu::ConfigMenu()
	{}

	ConfigMenu::~ConfigMenu()
	{}

	EMenuScreen ConfigMenu::run(MainWindow& window, EMenuScreen previous)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		ImageWidget background(skin->loadImage(MENU_BACKGROUND));

		TextWidget title("Configuration", TITLEFONT, 100);
		title.setColor(skin->getColor(TITLECOLOR));

		LinkWidget keys("Controles", 250, CONTROLLERSCONFIGMENU);		
		LinkWidget audio("Audio", 300, SOUNDCONFIGMENU);		
		LinkWidget graphics("Graphisme", 350, GRAPHICSCONFIGMENU);		
		LinkWidget back("Retour", 450, MAINMENU);

		keys.setNext(&audio);
		audio.setNext(&graphics);
		graphics.setNext(&back);
		audio.setPrevious(&keys);
		graphics.setPrevious(&audio);
		back.setPrevious(&graphics);

		keys.setSelected(true);

		this->widgets.push_back(&background);
		this->widgets.push_back(&title);
		this->widgets.push_back(&keys);
		this->widgets.push_back(&audio);
		this->widgets.push_back(&graphics);
		this->widgets.push_back(&back);

		sf::Clock clock;

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
					back.goNext();
					graphics.goNext();
					audio.goNext();
					keys.goNext();
					break;
				case MENU_UP:
					keys.goPrevious();
					audio.goPrevious();
					graphics.goPrevious();
					back.goPrevious();
					break;
				case MENU_VALID:
					if (keys.getSelected())   	return keys.activate();
					if (audio.getSelected())	return audio.activate();
					if (graphics.getSelected())	return graphics.activate();
					if (back.getSelected())     return back.activate();
					break;
				case MENU_BACK:
					return previous;
					break;
				default:
					break;
			}				
		}

		return EXIT;
	}
}

