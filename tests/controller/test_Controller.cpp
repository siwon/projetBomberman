/*!
 * \file test_Controller.cpp
 * \brief Test du module controlleur de jeu
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standards 
#include <iostream>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Bibliothèques externes

// Headers
#include "controller/ControllerManager.hpp"
#include "PolyBomberException.hpp"
#include "EGameKeys.hpp"
#include "EControllerType.hpp"

namespace PolyBomber
{

	int main()
	{
		sf::RenderWindow window(sf::VideoMode(300, 150), "Bomberman - Test ControllerDeJeu");
		window.setFramerateLimit(1000);
		
		ControllerManager* controllerManager = ControllerManager::getInstance();
		controllerManager->setWii();
		controllerManager->setWindow(&window);
		
		try
		{
			controllerManager->setPlayerController(2,GAMEPAD);
			//controllerManager->setPlayerKey(2,GAME_UP);
		}
		catch(PolyBomberException e)
		{
			std::cout << e.what();
		}
		
		controllerManager->setPlayerController(3,WII);
		
		while (window.isOpen())
		{
			//controllerManager->getKeyPressed(); // Touches menu
			//controllerManager->getCharPressed(); // Saisie clavier
			controllerManager->getKeysPressed(); // Touches jeu

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					controllerManager->save();
					controllerManager->kill();
					window.close();
				}
			}
			window.display();
		}
		
		return 0;
	}
}
