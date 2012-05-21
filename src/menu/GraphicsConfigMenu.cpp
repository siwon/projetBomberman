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
#include "menu/SelectionWidget.hpp"

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

		TextWidget textFullscreen("Mode plein-ecran : ", TEXTFONT, 200);
		textFullscreen.setColor(skin->getColor(TEXTCOLOR));
		textFullscreen.move(-100, 0);

		SelectionWidget fullscreen(TEXTFONT, 200);
		fullscreen.push_back("non");
		fullscreen.push_back("oui");
		fullscreen.move(100, 0);

		fullscreen.setCurrentItem(window.getFullScreen());

		TextWidget noFullscreen("Indisponible", ERRORFONT, 200);
		noFullscreen.setColor(skin->getColor(ERRORCOLOR));
		noFullscreen.move(100, 0);

		TextWidget skinText("Skin choisi :", TEXTFONT, 300);
		skinText.setColor(skin->getColor(TEXTCOLOR));

		SelectionWidget skinList(TEXTFONT, 350);
		skinList.push_back("skin 1");
		skinList.push_back("skin 2");		
		skinList.push_back("skin 3");		
		skinList.push_back("skin super long");		
		
		LinkWidget cancel("Annuler", 450, CONFIGMENU);
		cancel.move(-100, 0);
		
		LinkWidget save("Valider", 450, CONFIGMENU);
		save.move(100, 0);

		cancel.setSelected(true);

		
		fullscreen.setNext(&skinList);

		if (window.canFullScreen())
			skinList.setPrevious(&fullscreen);
			
		skinList.setNext(&cancel);
		
		cancel.setPrevious(&skinList);
		cancel.setNext(&save);
			
		save.setPrevious(&skinList);
		save.setNext(&cancel);

		this->widgets.push_back(&background);
		this->widgets.push_back(&title);
		this->widgets.push_back(&textFullscreen);
		this->widgets.push_back(&skinText);
		this->widgets.push_back(&skinList);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&save);
		
		if (window.canFullScreen())
			this->widgets.push_back(&fullscreen);
		else
			this->widgets.push_back(&noFullscreen);

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
					skinList.goNext();
					fullscreen.goNext();
					break;
				case MENU_UP:
					skinList.goPrevious();
					cancel.goPrevious();
					save.goPrevious();
					break;
				case MENU_LEFT:
					save.goNext();
					fullscreen.goPreviousItem();
					skinList.goPreviousItem();
					break;
				case MENU_RIGHT:
					cancel.goNext();
					fullscreen.goNextItem();
					skinList.goNextItem();
					break;
				case MENU_VALID:
					if (cancel.getSelected())  return cancel.activate();
					
					if (save.getSelected())
					{
						if (window.canFullScreen())
							window.setFullScreen(fullscreen.getCurrentItem());
							
						return save.activate();
					}
					break;
				default:
					break;
			}			
		}

		return EXIT;
	}
}
