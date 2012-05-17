/*!
 * \file SplashScreen.cpp
 * \brief Gestionnaire de l'écran de démarrage
 * \author Maxime GUIHAL
 */

#include "menu/SplashScreen.hpp"
#include "menu/ImageWidget.hpp"
#include "EImage.hpp"

#include "EColorKey.hpp"
#include <iostream>

namespace PolyBomber
{
	SplashScreen::SplashScreen()
	{}

	SplashScreen::~SplashScreen()
	{}

	EMenuScreen SplashScreen::run(MenuResources& resources, EMenuScreen previous)
	{
		MainWindow w = resources.getWindow();

		sf::Texture* splash = resources.getSkin()->loadImage(SPLASH);

		ImageWidget background(splash);

		this->widgets.push_back(&background);

		sf::Color text = resources.getSkin()->getColor(TEXTCOLOR);

		bool running = true;

		while (running)
		{
			if (w.listenCloseButton())
				return EXIT;
				
			w.clear();
			w.display(this->widgets);
		}

		return EXIT;
	}
}
