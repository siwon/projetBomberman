/*!
 * \file SplashScreen.cpp
 * \brief Gestionnaire de l'écran de démarrage
 * \author Maxime GUIHAL
 */

#include "menu/SplashScreen.hpp"
#include "PolyBomberApp.hpp"
#include "menu/ImageWidget.hpp"
#include "sound/SoundManager.hpp"

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

	EMenuScreen SplashScreen::run(MainWindow& window, EMenuScreen)
	{
		sf::Clock clock;
		bool wiiSearch = false;
		
		ControllerManager* controllerManager = ControllerManager::getInstance();		
		
		clock.restart();
		
		ISound* sound = PolyBomberApp::getISound();
		sound->playSound(SPLASHSOUND);
		
		while (true)
		{
			sf::Time elapsed = clock.getElapsedTime();

			// Fondus de transition
			if (elapsed.asSeconds() > 3.f && elapsed.asSeconds() <= 4.f)
				splash.setColor(sf::Color(255,255,255, 765 - 255 * elapsed.asSeconds()));
				
			if (elapsed.asSeconds() > 7.f && elapsed.asSeconds() <= 8.f)
				wiiScreen.setColor(sf::Color(255,255,255, 2040 - 255 * elapsed.asSeconds()));

			// Recherche des Wii
			if (elapsed.asSeconds() > 4.f && !wiiSearch)
			{
				controllerManager->setWii();
				wiiSearch = true;
			}

			if (elapsed.asSeconds() > 8.f)
				return MAINMENU;
			
			window.clear();
			window.display(this->widgets);
		}

		return EXIT;
	}
}
