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

using namespace PolyBomber;

int Gamepad::nbGamepad = 0;

const std::string Gamepad::keysLabel[] = {"Axe X", "Axe Y", "Bouton 1", "Bouton 2", "Bouton 3", "Bouton 4", "Bouton 5", "Bouton 6"};

std::string Gamepad::getLabel(int key)
{
	return keysLabel[key];
}

void Gamepad::add(int player)
{
	if(sf::Joystick::isConnected(nbGamepad))
	{
		nbGamepad++;
		gamepadsAssignation.insert(std::pair<int,int>(player,nbGamepad));
	}
	else
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
			std::cout << "Joystick " << event.joystickButton.joystickId << std::endl;
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

char Gamepad::getCharPressed()
{
	return '\0';
}

int Gamepad::getKeyPressed(int player)
{
	
	if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::X) < -10)
		return GAME_LEFT;

	if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::X) > 10)
		return GAME_RIGHT;

	if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::Y) > 10)
		return GAME_UP;

	if(sf::Joystick::getAxisPosition(gamepadsAssignation[player], sf::Joystick::Y) < -10)
		return GAME_DOWN;
	
	unsigned int k = 0;
	
	bool buttonPressed = false;

	while(k < sf::Joystick::getButtonCount(gamepadsAssignation[player]) && !buttonPressed)
	{
		if( sf::Joystick::isButtonPressed(gamepadsAssignation[player], k) )
		{
			buttonPressed = true;
		}
		else
		{
			k++;
		}
		
	}
	if( k == sf::Joystick::getButtonCount(gamepadsAssignation[player]))
		k = -1;
	
	return k;
}
