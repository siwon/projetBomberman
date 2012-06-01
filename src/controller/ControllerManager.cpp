/*!
 * \file ControllerManager.cpp
 * \brief Implémentation de classe ControllerManager
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standards 
#include <iostream>
#include <sstream>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Bibliothèques externes

// Headers
#include "controller/ControllerManager.hpp"
#include "controller/Controller.hpp"
#include "controller/Keyboard.hpp"
#include "controller/Gamepad.hpp"
#include "controller/GameAction.hpp"

#include "SKeysConfig.hpp"
#include "EGameKeys.hpp"
#include "PolyBomberException.hpp"


namespace PolyBomber
{

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

	int ControllerManager::ControllerAssignation::getKey(EGameKeys key)
	{
		return this->keys[key];
	}
	
	int* ControllerManager::ControllerAssignation::getKeys()
	{
		return this->keys;
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
		this->keys[GAME_UP] = Gamepad::Y_UP;
		this->keys[GAME_DOWN] = Gamepad::Y_DOWN;
		this->keys[GAME_LEFT] = Gamepad::X_LEFT;
		this->keys[GAME_RIGHT] = Gamepad::X_RIGHT;
		this->keys[GAME_ACTION1] = Gamepad::BUT1;
		this->keys[GAME_ACTION2] = Gamepad::BUT2;
		this->keys[GAME_PAUSE] = Gamepad::BUT10;
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
		configFileManager = new ConfigFileManager();
	
		controllerAssignation = new ControllerAssignation[4];
	
		/* Allocation des périphériques de jeu */
	
		keyboard = new Keyboard();
	
		wii = NULL;
	
		gamepad = new Gamepad();
	
		window = NULL;
	}

	void ControllerManager::setWii()
	{
		wii = new Wii();
		reloadConfig();
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
						sf::Joystick::update();
						gamepad->add(i+1);
						controllerAssignation[i].setController(gamepad);
						break;
				
					case WII :
							if(wii == NULL)
								throw new PolyBomberException("");
							wii->add(i+1);
							controllerAssignation[i].setController(wii);
						break;
				}
			}
			catch(PolyBomberException* e) // Si une erreur d'assignation est provoquée, on réassigne la configuration clavier par défaut au joueur
			{
				controllerAssignation[i].setController(keyboard);
				configFileManager->setDefaultKeyboardConfig(i+1);
				std::cout << e->what() << std::flush;
				delete e;
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
	
		delete gamepad;
	
		delete keyboard;
	
		delete wii;
	
		delete configFileManager;
	
	}

	EMenuKeys ControllerManager::getKeyPressed()
	{
		EMenuKeys key = MENU_NONE;
	
		key = wii->getMenuKey(window);
	
		// Correction processeur à 100%...
		sf::sleep(sf::milliseconds(5));
		
		if(key == MENU_NONE)
			key = gamepad->getMenuKey(window);
	
		if(key == MENU_NONE)
			key = keyboard->getMenuKey(window);	
	
	
		return key;
	}

	char ControllerManager::getCharPressed()
	{
		return keyboard->getCharPressed(this->window);
	}


	SKeysConfig ControllerManager::getConfig(int player)
	{
		SKeysConfig sKeysConfig;
		Controller* controller = controllerAssignation[player-1].getController();
		sKeysConfig.controllerType = controller->getControllerType();
	
		sKeysConfig.keys[GAME_UP] = controller->getLabel(controllerAssignation[player-1].getKey(GAME_UP));
		sKeysConfig.keys[GAME_DOWN] = controller->getLabel(controllerAssignation[player-1].getKey(GAME_DOWN));
		sKeysConfig.keys[GAME_LEFT] = controller->getLabel(controllerAssignation[player-1].getKey(GAME_LEFT));
		sKeysConfig.keys[GAME_RIGHT] = controller->getLabel(controllerAssignation[player-1].getKey(GAME_RIGHT));
		sKeysConfig.keys[GAME_ACTION1] = controller->getLabel(controllerAssignation[player-1].getKey(GAME_ACTION1));
		sKeysConfig.keys[GAME_ACTION2] = controller->getLabel(controllerAssignation[player-1].getKey(GAME_ACTION2));
		sKeysConfig.keys[GAME_PAUSE] = controller->getLabel(controllerAssignation[player-1].getKey(GAME_PAUSE));
	
		return sKeysConfig;
	}


	SKeysConfig ControllerManager::setPlayerKey(int player, EGameKeys key)
	{
		SKeysConfig sKeysConfig = this->getConfig(player);

		int keyPressed;
	
		do
		{
			keyPressed = controllerAssignation[player-1].getController()->getKeyPressed(player,window);
		}while( keyPressed == -1);

		if(keyUsed(keyPressed,player))
		{
			sKeysConfig.errors[key] = "Touche/Bouton déjà utilisée.";
			return sKeysConfig;
		}
	
		controllerAssignation[player-1].setKeys(key, keyPressed);
		return sKeysConfig;
		
	}

	bool ControllerManager::keyUsed(int key, int player)
	{
		bool used = false;
		int i=0;
		int j=0;
		switch(controllerAssignation[player-1].getController()->getControllerType())
		{
			case KEYBOARD :
				/* Si c'est le clavier, on regarde si aucun autre joueur clavier n'utilise déjà la touche */
				while(i<4 && !used)
				{
					if(controllerAssignation[i].getController()->getControllerType() == KEYBOARD)
					{
						j = 0;
						while(j<7 && !used)
						{
							if(key == controllerAssignation[i].getKey((EGameKeys)(j)))
								used = true;
							j++;
						}
					}
					i++;
				}
				break;
			case GAMEPAD :
			case WII :
				j = 0;
				/* Si  c'est un joystick ou une wiimote, on regarde si le joueur n'utilise pas déjà cette touche */
				while(j<7 && !used)
				{
					if(key == controllerAssignation[player-1].getKey((EGameKeys)(j)))
						used = true;
					j++;
				}
				break;
			default :
				break;
		}
		return used;
	}

	SKeysConfig ControllerManager::setPlayerController(int player, EControllerType type)
	{	
		EControllerType controllerType = controllerAssignation[player-1].getController()->getControllerType();
	
		if( type != controllerType) // Si le type est différent du contrôleur déjà utilisé
		{
			switch(type)
			{
				case KEYBOARD:
					if(controllerType == WII)
					{
						wii->disconnect(player);
					}
					else // Type Joystick
					{
						gamepad->disconnect(player);
					}
					controllerAssignation[player-1].setController(keyboard);
					controllerAssignation[player-1].setDefaultKeyboardConfig(player);
					break;
				
				case GAMEPAD:
					try
					{
						sf::Joystick::update();
						gamepad->add(player);
						if(controllerType == WII)
						{
							wii->disconnect(player);
						}
						controllerAssignation[player-1].setController(gamepad);
						controllerAssignation[player-1].setDefaultGamepadConfig();
					}
					catch(PolyBomberException* e)
					{
						delete e;
						throw PolyBomberException("Aucun joystick n'est disponible."); // Renvoie de l'exception pour traitement graphique
					}	
					break;
			
				case WII:
					try
					{
						wii->add(player);
						if(controllerType == GAMEPAD)
						{
							gamepad->disconnect(player);
						}
						controllerAssignation[player-1].setController(wii);
						controllerAssignation[player-1].setDefaultWiimoteConfig();
					}
					catch(PolyBomberException* e)
					{
						delete e;
						throw PolyBomberException("Aucune wiimote n'est disponible."); // Renvoie de l'exception pour traitement graphique
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
			configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKey(GAME_UP));
		
			ss.str("");
			ss << "controller.player" << i+1 << ".down";
			configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKey(GAME_DOWN));
		
			ss.str("");
			ss << "controller.player" << i+1 << ".left";
			configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKey(GAME_LEFT));
		
			ss.str("");
			ss << "controller.player" << i+1 << ".right";
			configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKey(GAME_RIGHT));
		
			ss.str("");
			ss << "controller.player" << i+1 << ".action1";
			configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKey(GAME_ACTION1));
		
			ss.str("");
			ss << "controller.player" << i+1 << ".action2";
			configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKey(GAME_ACTION2));
		
			ss.str("");
			ss << "controller.player" << i+1 << ".pause";
			configFileManager->setIntValue(ss.str(),controllerAssignation[i].getKey(GAME_PAUSE));
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
		return sKeyPressed;
	}


	SKeyPressed ControllerManager::getKeysPressed()
	{
		SKeyPressed sKeyPressed = initSKeyPressed();
		int i,j;
		Controller* controller;
		GameAction gameAction;
	
		for(i=0; i<4; i++)
		{
			controller = controllerAssignation[i].getController();
			if(controller != NULL)
			{
				gameAction = controller->getAction(controllerAssignation[i].getKeys(),i+1,window);
				for(j=0;j<7;j++)
				{
					if(gameAction.actions[j])
						sKeyPressed.keys[i][(EGameKeys)j] = true;
				}

			}
		}
		return sKeyPressed;
	}

	void ControllerManager::setWindow(sf::RenderWindow* window)
	{
		this->window = window;
	}
}
