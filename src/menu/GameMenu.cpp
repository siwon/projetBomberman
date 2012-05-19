/*!
 * \file GameMenu.cpp
 * \brief Gestionnaire du menu de jeu
 * \author Maxime GUIHAL
 */

#include "menu/GameMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	GameMenu::GameMenu()
	{}

	GameMenu::~GameMenu()
	{}

	EMenuScreen GameMenu::run(MainWindow& window, EMenuScreen previous)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		ImageWidget background(skin->loadImage(MENU_BACKGROUND));

		TextWidget title("Jouer", TITLEFONT, 100);
		title.setColor(skin->getColor(TITLECOLOR));

		LinkWidget create("Créer une partie", 250, CREATEGAMEMENU);		
		LinkWidget join("Rejoindre une partie", 300, JOINGAMEMENU);		
		LinkWidget back("Retour", 450, previous);

		create.setNext(&join);
		join.setNext(&back);
		join.setPrevious(&create);
		back.setPrevious(&join);

		create.setSelected(true);

		this->widgets.push_back(&background);
		this->widgets.push_back(&title);
		this->widgets.push_back(&create);
		this->widgets.push_back(&join);
		this->widgets.push_back(&back);

		sf::Clock clock;

		while (true)
		{
			if (window.listenCloseButton())
				return EXIT;

			EMenuKeys key = controller->getKeyPressed();

			if (clock.getElapsedTime().asMilliseconds() > 100)
			{
				clock.restart();

				switch(key)
				{
					case MENU_DOWN:
						back.goNext();
						join.goNext();
						create.goNext();
						break;
					case MENU_UP:
						create.goPrevious();
						join.goPrevious();
						back.goPrevious();
						break;
					case MENU_VALID:
						if (create.getSelected())   return create.activate();
						if (join.getSelected())		return join.activate();
						if (back.getSelected())     return back.activate();
						break;
					case MENU_BACK:
						return previous;
						break;
					default:
						break;
				}				
			}
				
			window.clear();
			window.display(this->widgets);
		}

		return EXIT;
	}
}

