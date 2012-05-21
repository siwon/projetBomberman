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
#include "../../include/controller/ControllerManager.hpp"
#include "../../include/PolyBomberException.hpp"
#include "../../include/SKeysConfig.hpp"
#include "../../include/EGameKeys.hpp"
#include "../../include/EControllerType.hpp"

using namespace PolyBomber;



int main()
{
    
	
     // Declare and create a new render-window
	sf::RenderWindow window(sf::VideoMode(300, 150), "Bomberman - Test ControllerDeJeu");
	
	ControllerManager* controllerManager = ControllerManager::getInstance();


	// Limit the framerate to 1 frames per second (this step is optional)
	window.setFramerateLimit(300);
	
	controllerManager->setWindow(&window);
	//controllerManager->setPlayerKey(2,GAME_UP);

	//controllerManager->printConfig(1);
	controllerManager->setPlayerController(2,GAMEPAD);
	//controllerManager->setPlayerController(3,WII);
	controllerManager->printConfig(2);
	//controllerManager->printConfig(3);
	//controllerManager->setPlayerController(3,KEYBOARD);
	/*controllerManager->printConfig(4);*/
	
	// The main loop - ends as soon as the window is closed
	while (window.isOpen())
	{
		controllerManager->getKeyPressed();
		//controllerManager->getCharPressed();
		//controllerManager->getKeysPressed();

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
