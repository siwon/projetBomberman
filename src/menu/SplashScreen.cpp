/*!
 * \file SplashScreen.cpp
 * \brief Gestionnaire de l'écran de démarrage
 * \author Maxime GUIHAL
 */

#include "menu/SplashScreen.hpp"
#include "PolyBomberApp.hpp"
#include "controller/ControllerManager.hpp"
#include "menu/ImageWidget.hpp"

namespace PolyBomber
{
	SplashScreen::SplashScreen()
	{
		ISkin* skin = PolyBomberApp::getISkin();
		splash.setImage(skin->loadImage(SPLASH));;
		wiiScreen.setImage(skin->loadImage(WIISCREEN));;
		this->widgets.push_back(&splash);
	}

	EMenuScreen SplashScreen::run(MainWindow& window, EMenuScreen previous)
	{
		sf::Clock clock;

		bool next = false;
		
		while (!next)
		{
			sf::Time elapsed = clock.getElapsedTime();

			// Fondu de sortie
			if (elapsed.asSeconds() > 2.f)
				splash.setColor(sf::Color(255,255,255, 765 - 255 * elapsed.asSeconds()));
			
			if (elapsed.asSeconds() > 3)
			{
				next = true;
				this->widgets.pop_back();
				this->widgets.push_back(&wiiScreen);
			}
			window.clear();
			window.display(this->widgets);
		}
		
		ControllerManager* controllerManager = ControllerManager::getInstance();
		controllerManager->setWii();
		
		clock.restart();
		
		while (true)
		{
			sf::Time elapsed = clock.getElapsedTime();

			// Fondu de sortie
			if (elapsed.asSeconds() > 3.f)
				wiiScreen.setColor(sf::Color(255,255,255, 765 - 255 * elapsed.asSeconds()));

			if (elapsed.asSeconds() > 4)
				return MAINMENU;
			
			window.clear();
			window.display(this->widgets);
		}

		return EXIT;
	}
}
