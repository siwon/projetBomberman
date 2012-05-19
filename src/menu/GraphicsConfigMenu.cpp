/*!
 * \file GraphicsConfigMenu.cpp
 * \brief Gestionnaire du menu de configuration graphique
 * \author Maxime GUIHAL
 */

#include "menu/GraphicsConfigMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	GraphicsConfigMenu::GraphicsConfigMenu()
	{}

	GraphicsConfigMenu::~GraphicsConfigMenu()
	{}

	EMenuScreen GraphicsConfigMenu::run(MainWindow& window, EMenuScreen previous)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		IControllerToMenu* controller = PolyBomberApp::getIControllerToMenu();

		ImageWidget background(skin->loadImage(MENU_BACKGROUND));

		TextWidget title("Configuration graphique", TITLEFONT, 100);
		title.setColor(skin->getColor(TITLECOLOR));

		TextWidget fullscreen("Mode plein-ecran : ", TEXTFONT, 200);
		fullscreen.setColor(skin->getColor(TEXTCOLOR));
		fullscreen.move(-100, 0);

		TextWidget noFullscreen("Indisponible", ERRORFONT, 200);
		noFullscreen.setColor(skin->getColor(ERRORCOLOR));
		noFullscreen.move(100, 0);
		
		
		LinkWidget back("Retour", 450, CONFIGMENU);

		back.setSelected(true);

		this->widgets.push_back(&background);
		this->widgets.push_back(&fullscreen);
		this->widgets.push_back(&noFullscreen);
		this->widgets.push_back(&back);

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
					break;
				case MENU_UP:
					break;
				case MENU_VALID:
					if (back.getSelected())    return back.activate();
					break;
				default:
					break;
			}				
		}

		return EXIT;
	}
}
