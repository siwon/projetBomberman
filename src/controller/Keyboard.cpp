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

using namespace PolyBomber;

Keyboard::Keyboard()
{
	
	/*!< Initialisation de la map avec les touches disponibles */
	
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::A, 'a'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::B, 'b'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::C, 'c'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::D, 'd'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::E, 'e'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::F, 'f'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::G, 'g'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::H, 'h'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::I, 'i'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::J, 'j'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::K, 'k'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::L, 'l'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::M, 'm'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::N, 'n'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::O, 'o'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::P, 'p'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Q, 'q'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::R, 'r'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::S, 's'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::T, 't'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::U, 'u'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::V, 'v'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::W, 'w'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::X, 'x'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Y, 'y'));
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Z, 'z'));
	
	keys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Back, 0x8));
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
		return LEFT_MENU;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		#if DEBUG
			std::cout << "RIGHT pressed on Keyboard" << std::endl;
		#endif
		return RIGHT_MENU;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		#if DEBUG
			std::cout << "UP pressed on Keyboard" << std::endl;
		#endif
		return UP_MENU;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		#if DEBUG
			std::cout << "DOWN pressed on Keyboard" << std::endl;
		#endif
		return DOWN_MENU;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		#if DEBUG
			std::cout << "VALID pressed on Keyboard" << std::endl;
		#endif
		return VALID;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		#if DEBUG
			std::cout << "BACK pressed on Keyboard" << std::endl;
		#endif
		return BACK;
	}

	return NONE;
		
}

char Keyboard::getCharPressed()
{
	
	std::map<sf::Keyboard::Key, char>::iterator it = keys.begin(); /* Création d'un itérateur pour parcourir la map */
	
	bool charPressed = false;
	char c = '\0';

	while((it != keys.end()) && !charPressed)
	{
		if(sf::Keyboard::isKeyPressed((*it).first))
		{
			c = (*it).second;
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