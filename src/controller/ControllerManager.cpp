/*!
 * \file ControllerManager.cpp
 * \brief Implémentation de classe ControllerManager
 * \author Alexandre BISIAUX
 */

#define DEBUG 0

/* Includes */

// Bibliothèques standarts 
#include <iostream>
#include <sstream>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Bibliothèques externes

// Headers
#include "../../include/controller/ControllerManager.hpp"
#include "../../include/controller/Controller.hpp"
#include "../../include/controller/Keyboard.hpp"
#include "../../include/controller/Gamepad.hpp"
#include "../../include/SKeysConfig.hpp"
#include "../../include/EGameKeys.hpp"
#include "../../include/PolyBomberException.hpp"


using namespace PolyBomber;

/************************* Implémentation de la classe interne ControllerAssignation ******************************/

ControllerManager::ControllerAssignation::ControllerAssignation()
{
	this->controller = NULL;
}

ControllerManager::ControllerAssignation::~ControllerAssignation()
{
	if(this->controller != NULL && this->controller->getControllerType() != KEYBOARD)
	{		
		delete this->controller;
	}
}
	
Controller* ControllerManager::ControllerAssignation::getController()
{
	return controller;
}

void ControllerManager::ControllerAssignation::setController(Controller* controller)
{
	this->controller = controller;
}

void ControllerManager::ControllerAssignation::setKeys(EGameKeys key, int value)
{
	this->keys[key] = value;
}

int ControllerManager::ControllerAssignation::getKeys(EGameKeys key)
{
	return this->keys[key];
}
/************************************ Fin ControllerAssignation **********************************************/

ControllerManager::ControllerManager()
{
	keyboard = new Keyboard(); // Prise en charge du clavier
	
	configFileManager = new ConfigFileManager("PolyBomber.conf");
	
	controllerAssignation = new ControllerAssignation[4];
	
	reloadConfig(); // Chargement de la configuration des joueurs
}

void ControllerManager::reloadConfig()
{
	EControllerType type;
	stringstream ss;
	int i;
	for(i=0; i<4; i++)
	{
		ss.str("");
		try
		{
			ss << "controller.player" << i+1 << ".type";
			type = (EControllerType)(configFileManager->getIntValue(ss.str()));
			switch(type)
			{
				case KEYBOARD :
					controllerAssignation[i].setController(keyboard);
					break;
					
				case GAMEPAD :
					controllerAssignation[i].setController(new Gamepad());
					break;
				
				case WII :
					//controllerAssignation[i].setController(new Wiimote);
					break;
			}
		}
		catch(PolyBomberException* e) // Si une erreur d'assignation est provoquée, on réassigne la configuration clavier par défaut au joueur
		{
			controllerAssignation[i].setController(keyboard);
			configFileManager->setDefaultConfig(i+1);
		}
		
		ss.str("");
		ss << "controller.player" << i+1 << ".up";
		controllerAssignation[i].setKeys(GAME_UP,configFileManager->getIntValue(ss.str()));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".down";
		controllerAssignation[i].setKeys(GAME_DOWN,configFileManager->getIntValue(ss.str()));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".left";
		controllerAssignation[i].setKeys(GAME_LEFT,configFileManager->getIntValue(ss.str()));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".right";
		controllerAssignation[i].setKeys(GAME_RIGHT,configFileManager->getIntValue(ss.str()));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".action1";
		controllerAssignation[i].setKeys(GAME_ACTION1,configFileManager->getIntValue(ss.str()));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".action2";
		controllerAssignation[i].setKeys(GAME_ACTION2,configFileManager->getIntValue(ss.str()));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".pause";
		controllerAssignation[i].setKeys(GAME_PAUSE,configFileManager->getIntValue(ss.str()));
	}
}

ControllerManager::~ControllerManager()
{
	
	delete[] controllerAssignation;
	
	delete keyboard;
	
	delete configFileManager;
	
}

EMenuKeys ControllerManager::getKeyPressed()
{
	EMenuKeys key = MENU_NONE;
	unsigned int i = 0;
	
	while(key == MENU_NONE && i < 4 )
	{
		key = controllerAssignation[i].getController()->getMenuKey();
		i++;
	}
	
	return key;
}

char ControllerManager::getCharPressed()
{
	return keyboard->getCharPressed();
}


SKeysConfig ControllerManager::getConfig(int player)
{
	SKeysConfig sKeysConfig;
	sKeysConfig.controllerType = controllerAssignation[player-1].getController()->getControllerType();
	
	/* A compléter avec le libellé des touches et la gestion des erreurs */
	
	return sKeysConfig;
}


SKeysConfig ControllerManager::setPlayerKey(int player, EGameKeys key)
{
	controllerAssignation[player-1].setKeys(key, controllerAssignation[player-1].getController()->getKeyPressed());
	return this->getConfig(player);	
}

SKeysConfig ControllerManager::setPlayerController(int player, EControllerType type)
{	
	EControllerType controllerType = controllerAssignation[player-1].getController()->getControllerType();
	Gamepad* gamepad;
	//Wiimote* wiimote;
	
	if( type != controllerType) // Si le type est différent du contrôleur déjà utilisé
	{
		switch(type)
		{
			case KEYBOARD:
				delete controllerAssignation[player-1].getController();
				controllerAssignation[player-1].setController(keyboard);
				break;
				
			case GAMEPAD:
				if(controllerType != KEYBOARD)
				{
					delete controllerAssignation[player-1].getController();
				}
				gamepad = new Gamepad();
				controllerAssignation[player-1].setController(gamepad);
				break;
			
			case WII:
				std::cout << "WII" << std::endl;
				/*
				if(controllerType != KEYBOARD)
				{
					delete controllerAssignation[player-1].getController();
				}
				wiimote = new Wiimote();
				controllerAssignation[player-1].setController(wiimote);*/
				break;
				
			default:
				break;
		}
	}
	return this->getConfig(player);
}

void ControllerManager::save()
{
	stringstream ss;
	int i;
	for(i=0; i<4; i++)
	{
		ss.str("");
		ss << "controller.player" << i+1 << ".type";
		configFileManager->setIntValue(ss.str(),controllerAssignation[i].getController()->getControllerType());
		
		ss.str("");
		ss << "controller.player" << i+1 << ".up";
		configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKeys(GAME_UP));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".down";
		configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKeys(GAME_DOWN));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".left";
		configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKeys(GAME_LEFT));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".right";
		configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKeys(GAME_RIGHT));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".action1";
		configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKeys(GAME_ACTION1));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".action2";
		configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKeys(GAME_ACTION2));
		
		ss.str("");
		ss << "controller.player" << i+1 << ".pause";
		configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKeys(GAME_PAUSE));
	}
}

/*
SKeyPressed ControllerManager::getKeysPressed()
{
	return NULL;
}*/
