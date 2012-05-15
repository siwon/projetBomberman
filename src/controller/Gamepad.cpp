/*!
 * \file Gamepad.cpp
 * \brief Implémentation de la classe Gamepad
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

Gamepad::Gamepad()
{
	if(sf::Joystick::isConnected(nbGamepad))
	{
		this->noGamepad = nbGamepad;
		nbGamepad++;
	}
	else
	{
		std::stringstream ss;
		ss << "Aucun Joystick n'est disponible." << std::endl;
		
		throw new PolyBomberException(ss.str());
	}
}

Gamepad::~Gamepad()
{
	nbGamepad--;
}

EMenuKeys Gamepad::getMenuKey()
{
	if(sf::Joystick::getAxisPosition(noGamepad, sf::Joystick::X) < -10)
	{
		#if DEBUG
			std::cout << "LEFT on Gamepad" << std::endl;
		#endif
		return MENU_LEFT;
	}

	if(sf::Joystick::getAxisPosition(noGamepad, sf::Joystick::X) > 10)
	{
		#if DEBUG
			std::cout << "RIGHT on Gamepad" << std::endl;
		#endif
		return MENU_RIGHT;
	}

	if(sf::Joystick::getAxisPosition(noGamepad, sf::Joystick::Y) > 10)
	{
		#if DEBUG
			std::cout << "UP on Gamepad" << std::endl;
		#endif
		return MENU_UP;
	}

	if(sf::Joystick::getAxisPosition(noGamepad, sf::Joystick::Y) < -10)
	{
		#if DEBUG
			std::cout << "DOWN on Gamepad" << std::endl;
		#endif
		return MENU_DOWN;
	}

	if(sf::Joystick::isButtonPressed(noGamepad, 1))
	{
		#if DEBUG
			std::cout << "VALID on Gamepad" << std::endl;
		#endif
		return MENU_VALID;
	}

	if(sf::Joystick::isButtonPressed(noGamepad, 2))
	{
		#if DEBUG
			std::cout << "BACK on Gamepad" << std::endl;
		#endif
		return MENU_BACK;
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

int Gamepad::getKeyPressed()
{
	
	if(sf::Joystick::getAxisPosition(noGamepad, sf::Joystick::X) < -10)
		return GAME_LEFT;

	if(sf::Joystick::getAxisPosition(noGamepad, sf::Joystick::X) > 10)
		return GAME_RIGHT;

	if(sf::Joystick::getAxisPosition(noGamepad, sf::Joystick::Y) > 10)
		return GAME_UP;

	if(sf::Joystick::getAxisPosition(noGamepad, sf::Joystick::Y) < -10)
		return GAME_DOWN;
	
	int k = 0;
	
	bool buttonPressed = false;

	while(k < sf::Joystick::getButtonCount(noGamepad) && !buttonPressed)
	{
		if( sf::Joystick::isButtonPressed(noGamepad, k) )
		{
			buttonPressed = true;
		}
		else
		{
			k++;
		}
		
	}
	if( k == sf::Joystick::getButtonCount(noGamepad))
		k = -1;
	
	return k;
}