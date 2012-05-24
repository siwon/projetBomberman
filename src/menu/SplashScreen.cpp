/*!
 * \file SplashScreen.cpp
 * \brief Gestionnaire de l'écran de démarrage
 * \author Maxime GUIHAL
 */

#include "menu/SplashScreen.hpp"
#include "PolyBomberApp.hpp"
#include "menu/ImageWidget.hpp"

namespace PolyBomber
{
	SplashScreen::SplashScreen()
	{
		ISkin* skin = PolyBomberApp::getISkin();
		splash.setImage(skin->loadImage(SPLASH));
		wiiScreen.setImage(skin->loadImage(WIISCREEN));
		
		this->widgets.push_back(&wiiScreen);
		this->widgets.push_back(&splash);
	}

	EMenuScreen SplashScreen::run(MainWindow& window, EMenuScreen previous)
	{
		sf::Clock clock;
		
		ControllerManager* controllerManager = ControllerManager::getInstance();
		controllerManager->setWii();
		
		clock.restart();
		
		while (true)
		{
			sf::Time elapsed = clock.getElapsedTime();

			// Fondus de transition
			if (elapsed.asSeconds() > 3.f && elapsed.asSeconds() <= 4.f)
				splash.setColor(sf::Color(255,255,255, 765 - 255 * elapsed.asSeconds()));

			if (elapsed.asSeconds() > 6.f && elapsed.asSeconds() <= 7.f)
				wiiScreen.setColor(sf::Color(255,255,255, 1785 - 255 * elapsed.asSeconds()));

			if (elapsed.asSeconds() > 7.f)
				return MAINMENU;
			
			window.clear();
			window.display(this->widgets);
		}

		return EXIT;
	}
}
