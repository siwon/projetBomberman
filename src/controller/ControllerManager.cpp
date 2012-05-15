/*!
 * \file ControllerManager.cpp
 * \brief Implémentation de classe ControllerManager
 * \author Alexandre BISIAUX
 */

#define DEBUG 1

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
		
		try
		{
			ss.str("");
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
			configFileManager->setDefaultKeyboardConfig(i+1);
			std::cout << e->what();
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
	Controller* controller = controllerAssignation[player-1].getController();
	sKeysConfig.controllerType = controller->getControllerType();
	
	sKeysConfig.keys[GAME_UP] = controller->getLabel(controllerAssignation[player-1].getKeys(GAME_UP));
	sKeysConfig.keys[GAME_DOWN] = controller->getLabel(controllerAssignation[player-1].getKeys(GAME_DOWN));
	sKeysConfig.keys[GAME_LEFT] = controller->getLabel(controllerAssignation[player-1].getKeys(GAME_LEFT));
	sKeysConfig.keys[GAME_RIGHT] = controller->getLabel(controllerAssignation[player-1].getKeys(GAME_RIGHT));
	sKeysConfig.keys[GAME_ACTION1] = controller->getLabel(controllerAssignation[player-1].getKeys(GAME_ACTION1));
	sKeysConfig.keys[GAME_ACTION2] = controller->getLabel(controllerAssignation[player-1].getKeys(GAME_ACTION2));
	sKeysConfig.keys[GAME_PAUSE] = controller->getLabel(controllerAssignation[player-1].getKeys(GAME_PAUSE));
	
	return sKeysConfig;
}


SKeysConfig ControllerManager::setPlayerKey(int player, EGameKeys key)
{
	SKeysConfig sKeysConfig = this->getConfig(player);
	std::cout << "Appuyer sur une touche / bouton" << std::endl;
	int keyPressed = controllerAssignation[player-1].getController()->getKeyPressed();
	while( keyPressed == -1)
	{
		keyPressed = controllerAssignation[player-1].getController()->getKeyPressed();
	}
	/* Si le controleur est de type clavier, on vérifie que la touche voulu n'est pas déjà utilisée par autre joueur ou par lui-même */
	if(controllerAssignation[player-1].getController()->getControllerType() == KEYBOARD && keyUsed(keyPressed))
	{
		sKeysConfig.errors[key] = "Touche déjà utilisée.";
		#if DEBUG
			std::cout << sKeysConfig.errors[key] << std::endl;
		#endif
		return sKeysConfig;
	}
	
	controllerAssignation[player-1].setKeys(key, keyPressed);
	return sKeysConfig;
		
}

bool ControllerManager::keyUsed(int key)
{
	int i=0;
	int j=0;
	bool used = false;
	while(i<4 && !used)
	{
		if(controllerAssignation[i].getController()->getControllerType() == KEYBOARD)
		{
			while(j<4 && !used)
			{
				if(key == controllerAssignation[i].getKeys((EGameKeys)(j)))
					used = true;
				j++;
			}
		}
		i++;
	}
	return used;
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
				try
				{
					gamepad = new Gamepad();
					if(controllerType != KEYBOARD)
					{
						delete controllerAssignation[player-1].getController();
					}
					controllerAssignation[player-1].setController(gamepad);
				}
				catch(PolyBomberException* e)
				{
					#if DEBUG
						std::cout << e->what();
					#endif
				}	
				break;
			
			case WII:
				/*
				try
				{
					wiimote = new Wiimote();
					if(controllerType != KEYBOARD)
					{
						delete controllerAssignation[player-1].getController();
					}
					controllerAssignation[player-1].setController(gamepad);
				}
				catch(PolyBomberException* e)
				{
					#if DEBUG
						std::cout << e->what();
					#endif
				}*/
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

SKeyPressed ControllerManager::initSKeyPressed()
{
	SKeyPressed sKeyPressed;
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<7;j++)
		{
			sKeyPressed.keys[i][j] = false;
		}
	}
}


SKeyPressed ControllerManager::getKeysPressed()
{
	SKeyPressed sKeyPressed = initSKeyPressed();
	int i;
	Controller* controller;
	EGameKeys gameKeys;
	for(i=0; i<4; i++)
	{
		controller = controllerAssignation[i].getController();
		if(controller != NULL)
		{
			gameKeys = getAction(controller->getKeyPressed(),i+1);
			
			if(gameKeys == GAME_UP)
			{
				#if DEBUG
					std::cout << "Player " << i+1 << ": UP" << std::endl;
				#endif
				sKeyPressed.keys[i][GAME_UP] = true;
			}
			
			if(gameKeys == GAME_DOWN)
			{
				#if DEBUG
					std::cout << "Player " << i+1 << ": DOWN" << std::endl;
				#endif
				sKeyPressed.keys[i][GAME_DOWN] = true;
			}
			
			if(gameKeys == GAME_LEFT)
			{
				#if DEBUG
					std::cout << "Player " << i+1 << ": LEFT" << std::endl;
				#endif
				sKeyPressed.keys[i][GAME_LEFT] = true;
			}
			
			if(gameKeys == GAME_RIGHT)
			{
				#if DEBUG
					std::cout << "Player " << i+1 << ": RIGHT" << std::endl;
				#endif
				sKeyPressed.keys[i][GAME_RIGHT] = true;
			}
			
			if(gameKeys == GAME_ACTION1)
			{
				#if DEBUG
					std::cout << "Player " << i+1 << ": ACTION1" << std::endl;
				#endif
				sKeyPressed.keys[i][GAME_ACTION1] = true;
			}
			
			if(gameKeys == GAME_ACTION2)
			{
				#if DEBUG
					std::cout << "Player " << i+1 << ": ACTION2" << std::endl;
				#endif
				sKeyPressed.keys[i][GAME_ACTION2] = true;
			}
			
			if(gameKeys == GAME_PAUSE)
			{
				#if DEBUG
					std::cout << "Player " << i+1 << ": PAUSE" << std::endl;
				#endif
				sKeyPressed.keys[i][GAME_PAUSE] = true;
			}
		}
	}	
}

EGameKeys ControllerManager::getAction(int key, int player)
{
	if( key == (int)(controllerAssignation[player-1].getKeys(GAME_UP)) )
		return GAME_UP;
	
	if( key == (int)(controllerAssignation[player-1].getKeys(GAME_DOWN)) )
		return GAME_DOWN;
	
	if( key == (int)(controllerAssignation[player-1].getKeys(GAME_LEFT)) )
		return GAME_LEFT;
	
	if( key == (int)(controllerAssignation[player-1].getKeys(GAME_RIGHT)) )
		return GAME_RIGHT;
	
	if( key == (int)(controllerAssignation[player-1].getKeys(GAME_ACTION1)) )
		return GAME_ACTION1;
	
	if( key == (int)(controllerAssignation[player-1].getKeys(GAME_ACTION2)) )
		return GAME_ACTION2;
	
	if( key == (int)(controllerAssignation[player-1].getKeys(GAME_PAUSE)) )
		return GAME_PAUSE;
	
	return GAME_NONE;
}

void ControllerManager::printConfig(int player)
{
	std::cout << "Player" << player << std::endl;
	std::cout << "Type = " << controllerAssignation[player-1].getController()->getControllerType() << std::endl;
	for(int j=0; j< 7 ; j++)
	{
		if(controllerAssignation[player-1].getController() != NULL)
			std::cout << controllerAssignation[player-1].getController()->getLabel(controllerAssignation[player-1].getKeys((EGameKeys)(j))) << std::endl;
	}

}