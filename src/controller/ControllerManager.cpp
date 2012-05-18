/*!
 * \file ControllerManager.cpp
 * \brief Implémentation de classe ControllerManager
 * \author Alexandre BISIAUX
 */

#define DEBUG 1

/* Includes */

// Bibliothèques standards 
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
	if(this->controller != 	NULL && this->controller->getControllerType() == GAMEPAD)
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

void ControllerManager::ControllerAssignation::setDefaultWiimoteConfig()
{
	this->keys[GAME_UP] = CButtons::BUTTON_RIGHT;
	this->keys[GAME_DOWN] = CButtons::BUTTON_LEFT;
	this->keys[GAME_LEFT] = CButtons::BUTTON_UP;
	this->keys[GAME_RIGHT] = CButtons::BUTTON_DOWN;
	this->keys[GAME_ACTION1] = CButtons::BUTTON_TWO;
	this->keys[GAME_ACTION2] = CButtons::BUTTON_ONE;
	this->keys[GAME_PAUSE] = CButtons::BUTTON_HOME;
}

void ControllerManager::ControllerAssignation::setDefaultGamepadConfig()
{
	this->keys[GAME_UP] = Gamepad::Y;
	this->keys[GAME_DOWN] = Gamepad::Y;
	this->keys[GAME_LEFT] = Gamepad::Y;
	this->keys[GAME_RIGHT] = Gamepad::X;
	this->keys[GAME_ACTION1] = Gamepad::But1;
	this->keys[GAME_ACTION2] = Gamepad::But2;
	this->keys[GAME_PAUSE] = Gamepad::But3;
}

void ControllerManager::ControllerAssignation::setDefaultKeyboardConfig(int player)
{
	switch(player)
	{
		case 1 :
			this->keys[GAME_UP] = sf::Keyboard::Up;
			this->keys[GAME_DOWN] = sf::Keyboard::Down;
			this->keys[GAME_LEFT] = sf::Keyboard::Left;
			this->keys[GAME_RIGHT] = sf::Keyboard::Right;
			this->keys[GAME_ACTION1] = sf::Keyboard::RControl;
			this->keys[GAME_ACTION2] = sf::Keyboard::RShift;
			this->keys[GAME_PAUSE] = sf::Keyboard::Return;
			break;
			
		case 2 :
			this->keys[GAME_UP] = sf::Keyboard::Z;
			this->keys[GAME_DOWN] = sf::Keyboard::S;
			this->keys[GAME_LEFT] = sf::Keyboard::Q;
			this->keys[GAME_RIGHT] = sf::Keyboard::D;
			this->keys[GAME_ACTION1] = sf::Keyboard::LControl;
			this->keys[GAME_ACTION2] = sf::Keyboard::LShift;
			this->keys[GAME_PAUSE] = sf::Keyboard::Escape;
			break;
			
		case 3 :
			this->keys[GAME_UP] = sf::Keyboard::Numpad8;
			this->keys[GAME_DOWN] = sf::Keyboard::Numpad5;
			this->keys[GAME_LEFT] = sf::Keyboard::Numpad4;
			this->keys[GAME_RIGHT] = sf::Keyboard::Numpad6;
			this->keys[GAME_ACTION1] = sf::Keyboard::Numpad0;
			this->keys[GAME_ACTION2] = sf::Keyboard::Add;
			this->keys[GAME_PAUSE] = sf::Keyboard::Subtract;
			break;
			
		case 4 :
			this->keys[GAME_UP] = sf::Keyboard::I;
			this->keys[GAME_DOWN] = sf::Keyboard::K;
			this->keys[GAME_LEFT] = sf::Keyboard::J;
			this->keys[GAME_RIGHT] = sf::Keyboard::L;
			this->keys[GAME_ACTION1] = sf::Keyboard::Space;
			this->keys[GAME_ACTION2] = sf::Keyboard::M;
			this->keys[GAME_PAUSE] = sf::Keyboard::P;
			break;
			
		default :
			break;
	}
}
/************************************ Fin ControllerAssignation **********************************************/

ControllerManager::ControllerManager()
{
	keyboard = new Keyboard(); // Prise en charge du clavier
	std::stringstream ss;
	ss << "../../" << DEFAULT_FILENAME;
	configFileManager = new ConfigFileManager(ss.str());
	
	controllerAssignation = new ControllerAssignation[4];
	
	wii = new Wii();
	
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
					wii->addWiimote(i+1);
					controllerAssignation[i].setController(wii);
					break;
			}
		}
		catch(PolyBomberException* e) // Si une erreur d'assignation est provoquée, on réassigne la configuration clavier par défaut au joueur
		{
			controllerAssignation[i].setController(keyboard);
			configFileManager->setDefaultKeyboardConfig(i+1);
			std::cout << e->what() << std::flush;
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
	
	delete wii;
	
	delete configFileManager;
	
}

EMenuKeys ControllerManager::getKeyPressed()
{
	EMenuKeys key = MENU_NONE;
	unsigned int i = 0;
	
	key = keyboard->getMenuKey();
	
	if(key == MENU_NONE)
		key = wii->getMenuKey();
	
	if(key == MENU_NONE)
	{
		Controller* c = controllerAssignation[i].getController();
		
		while(key == MENU_NONE && i < 4 && c->getControllerType() == GAMEPAD )
		{
			key = c->getMenuKey();
			i++;
		}
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
	int keyPressed = controllerAssignation[player-1].getController()->getKeyPressed(player);
	while( keyPressed == -1)
	{
		keyPressed = controllerAssignation[player-1].getController()->getKeyPressed(player);
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
	
	if( type != controllerType) // Si le type est différent du contrôleur déjà utilisé
	{
		switch(type)
		{
			case KEYBOARD:
				if(controllerType == WII)
				{
					wii->disconnectWiimote(player);
				}
				else // Type Joystick
				{
					delete controllerAssignation[player-1].getController();
				}
				controllerAssignation[player-1].setController(keyboard);
				controllerAssignation[player-1].setDefaultKeyboardConfig(player);
				break;
				
			case GAMEPAD:
				try
				{
					gamepad = new Gamepad();
					if(controllerType == WII)
					{
						wii->disconnectWiimote(player);
					}
					controllerAssignation[player-1].setController(gamepad);
					controllerAssignation[player-1].setDefaultGamepadConfig();
				}
				catch(PolyBomberException* e)
				{
					#if DEBUG
						std::cout << e->what();
					#endif
				}	
				break;
			
			case WII:
				try
				{
					wii->addWiimote(player);
					if(controllerType == GAMEPAD)
					{
						delete controllerAssignation[player-1].getController();
					}
					controllerAssignation[player-1].setController(wii);
					controllerAssignation[player-1].setDefaultWiimoteConfig();
				}
				catch(PolyBomberException* e)
				{
					#if DEBUG
						std::cout << e->what();
					#endif
				}
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
			gameKeys = getAction(controller->getKeyPressed(i+1),i+1);
			
			switch(gameKeys)
			{
				case GAME_UP :
					#if DEBUG
						std::cout << "Player " << i+1 << ": UP" << std::endl;
					#endif
					sKeyPressed.keys[i][GAME_UP] = true;
					break;
				case GAME_DOWN :
					#if DEBUG
						std::cout << "Player " << i+1 << ": DOWN" << std::endl;
					#endif
					sKeyPressed.keys[i][GAME_DOWN] = true;
					break;
				case GAME_LEFT :
					#if DEBUG
						std::cout << "Player " << i+1 << ": LEFT" << std::endl;
					#endif
					sKeyPressed.keys[i][GAME_LEFT] = true;
					break;
				case GAME_RIGHT :
					#if DEBUG
						std::cout << "Player " << i+1 << ": RIGHT" << std::endl;
					#endif
					sKeyPressed.keys[i][GAME_RIGHT] = true;
					break;
				case GAME_ACTION1 :
					#if DEBUG
						std::cout << "Player " << i+1 << ": ACTION1" << std::endl;
					#endif
					sKeyPressed.keys[i][GAME_ACTION1] = true;
					break;
				case GAME_ACTION2 :
					#if DEBUG
						std::cout << "Player " << i+1 << ": ACTION2" << std::endl;
					#endif
					sKeyPressed.keys[i][GAME_ACTION2] = true;
					break;
				case GAME_PAUSE :
					#if DEBUG
						std::cout << "Player " << i+1 << ": PAUSE" << std::endl;
					#endif
					sKeyPressed.keys[i][GAME_PAUSE] = true;
					break;
				default :
					break;
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
