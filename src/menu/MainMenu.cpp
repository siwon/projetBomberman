/*!
 * \file MainMenu.cpp
 * \brief Gestionnaire du menu principal
 * \author Maxime GUIHAL
 */

#include "menu/MainMenu.hpp"

#include "menu/ImageWidget.hpp"

namespace PolyBomber
{
	MainMenu::MainMenu()
	{}

	MainMenu::~MainMenu()
	{}

	EMenuScreen MainMenu::run(MenuResources* resources, EMenuScreen previous)
	{
		MainWindow* w = resources->getWindow();

		ImageWidget background(resources->getSkin()->loadImage(MENU_BACKGROUND));

		this->widgets.push_back(&background);

		while (true)
		{
			if (w->listenCloseButton())
				return EXIT;
				
			w->clear();
			w->display(this->widgets);
		}

		return EXIT;
	}
}
