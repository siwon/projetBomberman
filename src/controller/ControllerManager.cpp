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
#include "../../include/SKeysConfig.hpp"



using namespace PolyBomber;


ControllerManager *ControllerManager::controllerManager = NULL; /*!< Initialisation du controllerManager */


ControllerManager::ControllerManager(sf::RenderWindow* app)
{
	this->app = app;
	Controller* keyboard = new Keyboard;
	this->controllers.push_back(keyboard);
	
	/* Initialisation de la structure keysAssignation */
	
	/* Par défault les 4 joueurs utilisent le clavier */
	SKeysConfig sKeysConfig;
	skeysCongig
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
	return controllers[0]->getCharPressed();
}


SKeysConfig ControllerManager::getConfig(int player)
{
	return keysAssignation[player-1];
}


SKeysConfig ControllerManager::setPlayerKey(int player, EGameKeys key)
{
	if( keysAssignation.size() >= player ) // Si la structure contient déjà le joueur
	
	
}
/*
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
	sf::RenderWindow window(sf::VideoMode(300, 150), "Bomberman - Test ControllerDeJeu");
	ControllerManager* controllerManager = ControllerManager::getInstance(&window);

	// Limit the framerate to 1 frames per second (this step is optional)
	window.setFramerateLimit(15);

	// The main loop - ends as soon as the window is closed
	while (window.isOpen())
	{
		controllerManager->getKeyPressed();
		controllerManager->getCharPressed();

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
