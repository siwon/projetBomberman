/*!
 * \file test_Controller.cpp
 * \brief Test du module controlleur de jeu
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standarts 
#include <iostream>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Bibliothèques externes

// Headers
#include "../../include/controller/ControllerManager.hpp"
#include "../../include/PolyBomberException.hpp"

using namespace PolyBomber;

int main()
{
    
	
     // Declare and create a new render-window
	sf::RenderWindow window(sf::VideoMode(300, 150), "Bomberman - Test ControllerDeJeu");
	
	ControllerManager* controllerManager = ControllerManager::getInstance();


	// Limit the framerate to 1 frames per second (this step is optional)
	window.setFramerateLimit(15);
	
	
	// The main loop - ends as soon as the window is closed
	while (window.isOpen())
	{
		controllerManager->getKeyPressed();
		controllerManager->getCharPressed();
		//controllerManager->setPlayerKey(1,UP);
		
		// Event processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed)
			{
				controllerManager->save();
				controllerManager->kill();
				window.close();
			}
		}

		// End the current frame and display its contents on screen
		window.display();
	}
	
	return 0;
}
