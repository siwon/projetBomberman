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
#include "../../include/EGameKeys.hpp"



using namespace PolyBomber;


ControllerManager *ControllerManager::controllerManager = NULL; /*!< Initialisation du controllerManager */


ControllerManager::ControllerManager()
{
	Controller* keyboard = new Keyboard;
	this->controllers.push_back(keyboard);
	
	configFileManager = new ConfigFileManager("controller.conf");
	
	reloadConfig();
}

ControllerManager* ControllerManager::getInstance()
{
	if(controllerManager == NULL)
	{
		controllerManager = new ControllerManager();
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
	
	delete configFileManager;
}

EMenuKeys ControllerManager::getKeyPressed()
{
	EMenuKeys key = MENU_NONE;
	unsigned int i = 0;
	
	while(key == MENU_NONE && i < controllers.size() )
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
	switch(keysAssignation[player-1].controllerType)
	{
		case KEYBOARD:
			keysAssignation[player-1].keys[key] = controllers[0]->getCharPressed();
			break;
		default :
			break;
	}
	std::cout << keysAssignation[player-1].keys[key] << std::flush;
	return keysAssignation[player-1];
	
	
}
/*
SKeysConfig ControllerManager::setPlayerController(int player, EControllerType type)
{
	return NULL;
}

*/
void ControllerManager::save()
{
	int i = 0;
	/*for(i=0;i<4;i++)
	{*/
		configFileManager->setIntValue("controller.player1.type",keysAssignation[i].controllerType);
		configFileManager->setStringValue("controller.player1.up",keysAssignation[i].keys[0]);
		configFileManager->setStringValue("controller.player1.down",keysAssignation[i].keys[1]);
		configFileManager->setStringValue("controller.player1.left",keysAssignation[i].keys[2]);
		configFileManager->setStringValue("controller.player1.right",keysAssignation[i].keys[3]);
		configFileManager->setStringValue("controller.player1.action1",keysAssignation[i].keys[4]);
		configFileManager->setStringValue("controller.player1.action2",keysAssignation[i].keys[5]);
		configFileManager->setStringValue("controller.player1.pause",keysAssignation[i].keys[6]);
}

void ControllerManager::reloadConfig()
{
	SKeysConfig sKeysConfig;
	
	/* For Player 1 */
	sKeysConfig.controllerType = (EControllerType)(configFileManager->getIntValue("controller.player1.type"));
	sKeysConfig.keys[0] = char(configFileManager->getIntValue("controller.player1.up"));
	sKeysConfig.keys[1] = char(configFileManager->getIntValue("controller.player1.down"));
	sKeysConfig.keys[2] = char(configFileManager->getIntValue("controller.player1.left"));
	sKeysConfig.keys[3] = char(configFileManager->getIntValue("controller.player1.right"));
	sKeysConfig.keys[4] = char(configFileManager->getIntValue("controller.player1.action1"));
	sKeysConfig.keys[5] = char(configFileManager->getIntValue("controller.player1.action2"));
	sKeysConfig.keys[6] = char(configFileManager->getIntValue("controller.player1.pause"));
		
	keysAssignation.push_back(sKeysConfig);
	
	/* For Player 2 */
	sKeysConfig.controllerType = (EControllerType)(configFileManager->getIntValue("controller.player2.type"));
	sKeysConfig.keys[0] = char(configFileManager->getIntValue("controller.player2.up"));
	sKeysConfig.keys[1] = char(configFileManager->getIntValue("controller.player2.down"));
	sKeysConfig.keys[2] = char(configFileManager->getIntValue("controller.player2.left"));
	sKeysConfig.keys[3] = char(configFileManager->getIntValue("controller.player2.right"));
	sKeysConfig.keys[4] = char(configFileManager->getIntValue("controller.player2.action1"));
	sKeysConfig.keys[5] = char(configFileManager->getIntValue("controller.player2.action2"));
	sKeysConfig.keys[6] = char(configFileManager->getIntValue("controller.player2.pause"));
		
	keysAssignation.push_back(sKeysConfig);
}
/*
SKeyPressed ControllerManager::getKeysPressed()
{
	return NULL;
}*/
