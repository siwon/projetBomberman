/*!
 * \file Gamepad.cpp
 * \brief Implémentation de la classe Gamepad
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
#include "../../include/EMenuKeys.hpp"
#include "../../include/EGameKeys.hpp"
#include "../../include/SKeysConfig.hpp"
#include "../../include/EControllerType.hpp"
#include "../../include/controller/Gamepad.hpp"
#include "../../include/PolyBomberException.hpp"
#include "../../include/controller/GameAction.hpp"

using namespace PolyBomber;

const std::string Gamepad::keysLabel[] = {"Haut", "Bas", "Gauche", "Droite", "Bouton 1", "Bouton 2", "Bouton 3", "Bouton 4", "Bouton 5", "Bouton 6", "Bouton 7", "Bouton 8", "Bouton 9", "Bouton 10"};

std::string Gamepad::getLabel(int key)
{
	return keysLabel[key];
}

bool Gamepad::gamepadUsed(int numGamepad)
{
	unsigned int i = 0;
	bool find = false;
	
	while (i<gamepadsAssignation.size() && !find)
	{
		if(gamepadsAssignation[i] == numGamepad)
			find = true;
		i++;
	}
	
	return find;
}

void Gamepad::add(int player)
{
	bool assignated = false;
	int i = 0;
	while( i < sf::Joystick::Count && !assignated )
	{
		if(!gamepadUsed(i) && sf::Joystick::isConnected(i))
		{
			gamepadsAssignation.insert(std::pair<int,int>(player,nbGamepad));
			nbGamepad++;
			assignated = true;
		}
		i++;
	}
	if(!assignated)
	{
		std::stringstream ss;
		ss << "Aucun Joystick n'est disponible." << std::endl;
	
		throw new PolyBomberException(ss.str());
	}
}

void Gamepad::disconnect(int player)
{
	nbGamepad--;
	gamepadsAssignation.erase(player);
}

Gamepad::Gamepad()
{
	nbGamepad = 0;
}

Gamepad::~Gamepad()
{

}

EMenuKeys Gamepad::getMenuKey(sf::RenderWindow* window)
{
	
	if(window != NULL)
	{
		sf::Event event;
		
		window->pollEvent(event);
		
		if(event.type == sf::Event::JoystickButtonReleased)
		{
			switch(event.joystickButton.button)
			{
				case 0 :
					#if DEBUG
						std::cout << "VALID on Gamepad" << std::endl;
					#endif
					return MENU_VALID;
					
				case 1 :
					#if DEBUG
						std::cout << "BACK on Gamepad" << std::endl;
					#endif
					return MENU_BACK;
			}
		}		
		else if(event.type == sf::Event::JoystickMoved)
		{
			switch(event.joystickMove.axis)
			{
				case sf::Joystick::X :
					if(event.joystickMove.position < -50)
					{			
						#if DEBUG
							std::cout << "LEFT on Gamepad" << std::endl;
						#endif
						return MENU_LEFT;
					}
					else if(event.joystickMove.position > 50)
					{
						#if DEBUG
							std::cout << "RIGHT on Gamepad" << std::endl;
						#endif
						return MENU_RIGHT;
					}
					break;
					
				case sf::Joystick::Y :
					if(event.joystickMove.position > 50)
					{			
						#if DEBUG
							std::cout << "DOWN on Gamepad" << std::endl;
						#endif
						return MENU_DOWN;
					}
					else if(event.joystickMove.position < -50)
					{
						#if DEBUG
							std::cout << "UP on Gamepad" << std::endl;
						#endif
						return MENU_UP;
					}
					break;
					
				default :
					return MENU_NONE;
			}
		}
		else if(event.type == sf::Event::Closed)
			window->close();
	}
	return MENU_NONE;
}

EControllerType Gamepad::getControllerType()
{
	return GAMEPAD;
}

char Gamepad::getCharPressed(sf::RenderWindow*)
{
	return '\0';
}

int Gamepad::getKeyPressed(int player,sf::RenderWindow* window)
{
	sf::Event event;
	window->pollEvent(event);
	
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 0))
		return BUT1;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 1))
		return BUT2;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 2))
		return BUT3;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 3))
		return BUT4;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 4))
		return BUT5;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 5))
		return BUT6;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 6))
		return BUT7;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 7))
		return BUT8;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 8))
		return BUT9;
	if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 9))
		return BUT10;
	if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::X) < -50)
		return X_LEFT;
	if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::X) > 50)
		return X_RIGHT;
	if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::Y) < -50)
		return Y_UP;
	if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::Y) > 50)
		return Y_DOWN;
	
	return -1;
}
		
GameAction Gamepad::getAction(int keys[7],int player, sf::RenderWindow*)
{
	int i;	
	
	GameAction gameAction;
	gameAction.init();
	
	for(i=0;i<7;i++)
	{
		switch((Keys)keys[i])
		{
			case BUT1:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 0))
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT2:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 1))
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT3:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 2))
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT4:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 3))
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT5:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 4))
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT6:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 5))
				{	
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT7:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 6))
				{	
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT8:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 7))
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT9:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 8))
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case BUT10:
				if(sf::Joystick::isButtonPressed(gamepadsAssignation[player], 9))
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			case X_LEFT:
				if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::X) < -50)
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;	
			case X_RIGHT:
				if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::X) > 50)
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;	
			case Y_UP:
				if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::Y) < -50)
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;	
			case Y_DOWN:
				if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::Y) > 50)
				{
					gameAction.actions[i] = true;
					std::cout << "Player " << player << " : " << keys[i] << std::endl;
				}
				break;
			default:
				break;
		}
	}
	return gameAction;
}
