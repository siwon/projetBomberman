/*!
 * \file Keyboard.cpp
 * \brief Implémentation de la classe Keyboard
 * \author Alexandre BISIAUX
 */
 
 #define DEBUG 1

/* Includes */

// Bibliothèques standards 
#include <iostream>
#include <vector>
#include <map>

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

const std::string Keyboard::keysLabel[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", 
							 "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
							 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "echap",
							 "CTRL Gauche", "Shift Gauche", "Alt Gauche", "System Gauche",
							 "CTRL Droit", "Shift Droit", "Alt Droit", "System Droit", "Menu",
							 "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Espace",
							 "Entree", "Retour arrière", "Tabulation", "Page suiv.", "Page prec.",
							 "Fin", "Home", "Insert", "Suppr", "+", "-", "*", "/", "Gauche", "Droite", "Haut",
							 "Bas", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "F1", "F2",
							 "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"};

std::string Keyboard::getLabel(int key)
{
	return keysLabel[key];
}


Keyboard::Keyboard()
{
	
}

Keyboard::~Keyboard()
{
}

EMenuKeys Keyboard::getMenuKey(sf::RenderWindow* window)
{
	if(window != NULL)
	{
		sf::Event event;
		window->pollEvent(event);
		if(event.type == sf::Event::KeyReleased)
		{
			switch(event.key.code)
			{
				case sf::Keyboard::Left :
					#if DEBUG
						std::cout << "LEFT on Keyboard" << std::endl;
					#endif
					return MENU_LEFT;
					
				case sf::Keyboard::Right :
					#if DEBUG
						std::cout << "RIGHT on Keyboard" << std::endl;
					#endif
					return MENU_RIGHT;
					
				case sf::Keyboard::Up :
					#if DEBUG
						std::cout << "UP on Keyboard" << std::endl;
					#endif
					return MENU_UP;
					
				case sf::Keyboard::Down :
					#if DEBUG
						std::cout << "DOWN on Keyboard" << std::endl;
					#endif
					return MENU_DOWN;
					
				case sf::Keyboard::Return :
					#if DEBUG
						std::cout << "VALID on Keyboard" << std::endl;
					#endif
					return MENU_VALID;
					
				case sf::Keyboard::Escape :
					#if DEBUG
						std::cout << "BACK on Keyboard" << std::endl;
					#endif
					return MENU_BACK;
					
				default :
					return MENU_NONE;
			}
		}
		if(event.type == sf::Event::Closed)
			window->close();
	}
	return MENU_NONE;
		
}

bool Keyboard::isAlphaNum(sf::Keyboard::Key key)
{
	
	if( key >= sf::Keyboard::A && key <= sf::Keyboard::Z ) // Si c'est un caractère alphabétique
		return true;
	
	if( key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9 ) // Si c'est un chiffre
		return true;
	
	if( key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9 ) // idem mais pour pad numérique
		return true;
	
	return false;
}

char Keyboard::getCharPressed()
{
	
	int k = (int)(sf::Keyboard::A);
	
	bool charPressed = false;
	char c = '\0';

	while(k != (int)(sf::Keyboard::KeyCount) && !charPressed)
	{
		if( sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(k)) && isAlphaNum((sf::Keyboard::Key)(k)) )
		{
			c = getLabel(k)[0];
			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) /* Gestion des majuscules */
				c = char(toupper(c));
			charPressed = true;
			
			if(k == (int)(sf::Keyboard::Space)) /* Gestion espace */
				c = ' ';
			
			if(k == (int)(sf::Keyboard::Back)) /* Gestion Retour arrière */
				c = (char)(0x08);
			
			if(k == (int)(sf::Keyboard::Delete)) /* Gestion Suppr */
				c = (char)(0x7F);
			
			#if DEBUG
				std::cout << c << std::flush;
			#endif
		}
		k++;
		
	}
	
	return c;
}

EControllerType Keyboard::getControllerType()
{
	return KEYBOARD;
}

int Keyboard::getKeyPressed(int player,sf::RenderWindow* window)
{
	int k = (int)(sf::Keyboard::A);
	
	bool keyPressed = false;

	while(k != (int)(sf::Keyboard::KeyCount) && !keyPressed)
	{
		if( sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(k)) )
		{
			keyPressed = true;
		}
		else
		{
			k++;
		}
		
	}
	if( k == (int)(sf::Keyboard::KeyCount) )
		k = -1;
	
	return k;
}

void Keyboard::add(int player){}

void Keyboard::disconnect(int player){}
