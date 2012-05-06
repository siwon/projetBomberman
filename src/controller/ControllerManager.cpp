/*!
 * \file ControllerManager.cpp
 * \brief Implémentation de classe ControllerManager
 * \author Alexandre BISIAUX
 */

#define DEBUG 1

/* Includes */

// Bibliothèques standarts 
#include <iostream>
#include <vector>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// Bibliothèques externes

// Headers
#include "../../include/controller/ControllerManager.hpp"
#include "../../include/controller/Controller.hpp"
#include "../../include/controller/Keyboard.hpp"




using namespace PolyBomber;


ControllerManager *ControllerManager::controllerManager = NULL; /*!< Initialisation du controllerManager */


ControllerManager::ControllerManager(sf::RenderWindow* app)
{
	this->app = app;
	Controller* keyboard = new Keyboard;
	this->controllers.push_back(keyboard);
}

ControllerManager* ControllerManager::getInstance(sf::RenderWindow* app)
{
	if(controllerManager == NULL)
	{
		controllerManager = new ControllerManager(app);
		#if DEBUG
			std::cout << "Creation of a new instance of ControllerManager" << std::endl;
		#endif
	}
	else
	{
		#if DEBUG
			std::cout << "Instance already created!" << std::endl;
		#endif
	}
	
	
	return controllerManager;
}

ControllerManager::~ControllerManager()
{
	unsigned int i;
	
	for(i=0;i<controllers.size();i++)
		delete controllers[i];
	
	if (controllerManager != NULL)
	{
		delete controllerManager;
		controllerManager = NULL;
	}
}

EMenuKeys ControllerManager::getKeyPressed()
{
	EMenuKeys key = NONE;
	int i = 0;
	
	while(key == NONE && i < controllers.size() )
	{
		key = controllers[i]->getMenuKey();
		i++;
	}
	
	return key;
}

char ControllerManager::getCharPressed()
{
	return controllers[0]->getCharPressed(this->app);
}

/*
SKeysConfig ControllerManager::getConfig(int player)
{
	return NULL;
}


SKeysConfig ControllerManager::setPlayerKey(int player, EGameKeys key)
{
	return NULL;
}

SKeysConfig ControllerManager::setPlayerController(int player, EControllerType type)
{
	return NULL;
}


void ControllerManager::save()
{
}

void ControllerManager::reloadConfig()
{
}*/


int main()
{
    
     // Declare and create a new render-window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bomberman - Test ControllerDeJeu");
	ControllerManager* controllerManager = ControllerManager::getInstance(&window);

	// Limit the framerate to 1 frames per second (this step is optional)
	window.setFramerateLimit(1);

	// The main loop - ends as soon as the window is closed
	while (window.isOpen())
	{
		//controllerManager->getKeyPressed();
		std::cout << controllerManager->getCharPressed() << std::flush;
		// Event processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// End the current frame and display its contents on screen
		window.display();
	}
	
	return 0;
}
