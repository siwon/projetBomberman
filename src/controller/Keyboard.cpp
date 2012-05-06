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

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// Bibliothèques externes

// Headers
#include "../../include/EMenuKeys.hpp"
#include "../../include/controller/Keyboard.hpp"

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

char Keyboard::getCharPressed(sf::RenderWindow* app)
{
	int i = 0;
	bool charPressed = false;
	char c = ' ';
	
	/*sf::Keyboard::Key keys[] = {sf::Keyboard::A,sf::Keyboard::B};
	
	while(i<2 && !charPressed)
	{
		if(sf::Keyboard::isKeyPressed(keys[i]))
		{
			c = char(keys[i]);
			charPressed = true;
		}
		
	}
	*/
	return c;
	/*sf::Event event;
	app->pollEvent(event);
	if (event.type == sf::Event::KeyPressed)
	{
		if((event.key.code == sf::Keyboard::A))
		{
			std::cout << event.key.code << std::endl;
			return event.key.code;
		}
	}*/
}


