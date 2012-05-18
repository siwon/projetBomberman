/*!
 * \file SplashScreen.cpp
 * \brief Gestionnaire de l'écran de démarrage
 * \author Maxime GUIHAL
 */

#include "menu/SplashScreen.hpp"

#include "menu/ImageWidget.hpp"

#include <iostream>

namespace PolyBomber
{
	SplashScreen::SplashScreen()
	{}

	SplashScreen::~SplashScreen()
	{}

	EMenuScreen SplashScreen::run(MenuResources* resources, EMenuScreen previous)
	{
		MainWindow* w = resources->getWindow();

		ImageWidget background(resources->getSkin()->loadImage(MENU_BACKGROUND));
		ImageWidget splash(resources->getSkin()->loadImage(SPLASH));

		this->widgets.push_back(&background);
		this->widgets.push_back(&splash);

		sf::Clock clock;

		while (true)
		{
			if (w->listenCloseButton())
				return EXIT;

			sf::Time elapsed = clock.getElapsedTime();

			// Fondu de sortie
			if (elapsed.asSeconds() > 2.f)
				splash.setColor(sf::Color(255,255,255, 765 - 255 * elapsed.asSeconds()));

			if (elapsed.asSeconds() > 3.f)
				return MAINMENU;
				
			w->clear();
			w->display(this->widgets);
		}

		return EXIT;
	}
}
