/*!
 * \file Keyboard.cpp
 * \brief Implémentation de la classe Keyboard
 * \author Alexandre BISIAUX
 */

#define DEBUG 1

/* Includes */

// Bibliothèques standarts 
#include <iostream>
#include <vector>
#include <map>
#include <ctype.h>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// Bibliothèques externes

// Headers
#include "../../include/EMenuKeys.hpp"
#include "../../include/SKeysConfig.hpp"
#include "../../include/EControllerType.hpp"
#include "../../include/controller/Keyboard.hpp"
#include "../../include/controller/Keys.hpp"

using namespace PolyBomber;

Keyboard::Keyboard()
{
	
}

Keyboard::~Keyboard()
{
}

EMenuKeys Keyboard::getMenuKey()
{
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		#if DEBUG
			std::cout << "LEFT pressed on Keyboard" << std::endl;
		#endif
		return MENU_LEFT;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		#if DEBUG
			std::cout << "RIGHT pressed on Keyboard" << std::endl;
		#endif
		return MENU_RIGHT;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		#if DEBUG
			std::cout << "UP pressed on Keyboard" << std::endl;
		#endif
		return MENU_UP;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		#if DEBUG
			std::cout << "DOWN pressed on Keyboard" << std::endl;
		#endif
		return MENU_DOWN;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		#if DEBUG
			std::cout << "VALID pressed on Keyboard" << std::endl;
		#endif
		return MENU_VALID;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		#if DEBUG
			std::cout << "BACK pressed on Keyboard" << std::endl;
		#endif
		return MENU_BACK;
	}

	return MENU_NONE;
		
}

char Keyboard::getCharPressed()
{
	std::map<sf::Keyboard::Key, Keys::KeyValue*> ::iterator it;
	it = keys.keyMap.begin(); /* Création d'un itérateur pour parcourir la map */
	
	bool charPressed = false;
	char c = '\0';

	while((it != keys.keyMap.end()) && !charPressed)
	{
		if(sf::Keyboard::isKeyPressed((*it).first))
		{
			c = (*it).second->getCharValue();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) /*!< Gestion des majuscules */
				c = char(toupper(c));
			charPressed = true;
			#if DEBUG
				std::cout << c << " pressed on Keyboard" << std::endl;
			#endif
		}
		it++;
		
	}
	
	return c;
}

/*
SKeysConfig Keyboard::getDefaultConfig(int player)
{
	SKeysConfig sKeysConfig;
	sKeysConfig.controllerType = KEYBOARD;
	
	switch(player)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
	}
	
	return sKeysConfig;
}*/