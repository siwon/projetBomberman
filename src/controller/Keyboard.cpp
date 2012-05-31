/*!
 * \file Keyboard.cpp
 * \brief Implémentation de la classe Keyboard
 * \author Alexandre BISIAUX
 */
 
/* Includes */

// Bibliothèques standards 
#include <iostream>
#include <vector>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Bibliothèques externes

// Headers
#include "../../include/EMenuKeys.hpp"
#include "../../include/SKeysConfig.hpp"
#include "../../include/EControllerType.hpp"
#include "../../include/controller/Keyboard.hpp"
#include "../../include/controller/GameAction.hpp"

namespace PolyBomber
{

	const std::string Keyboard::keysLabel[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", 
								 "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
								 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "echap",
								 "CTRL Gauche", "Shift Gauche", "Alt Gauche", "System Gauche",
								 "CTRL Droit", "Shift Droit", "Alt Droit", "System Droit", "Menu",
								 "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Espace",
								 "Entree", "Retour arrière", "Tabulation", "Page suiv.", "Page prec.",
								 "Fin", "Home", "Insert", "Suppr", "+", "-", "*", "/", "Gauche", "Droite", "Haut",
								 "Bas", "0 Numpad", "1 Numpad", "2 Numpad", "3 Numpad", "4 Numpad", "5 Numpad", "6 Numpad", "7 Numpad", "8 Numpad", "9 								 Numpad", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"};

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
						return MENU_LEFT;
					
					case sf::Keyboard::Right :
						return MENU_RIGHT;
					
					case sf::Keyboard::Up :
						return MENU_UP;
					
					case sf::Keyboard::Down :
						return MENU_DOWN;
					
					case sf::Keyboard::Return :
						return MENU_VALID;
					
					case sf::Keyboard::Escape :
						return MENU_BACK;
					
					default :
						return MENU_OTHER;
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

	char Keyboard::getCharPressed(sf::RenderWindow* window)
	{
		char c = '\0';
	
		if(window != NULL)
		{
			sf::Event event;
			window->pollEvent(event);
			if(event.type == sf::Event::KeyPressed)
			{
				c = 1;
				if(isAlphaNum(event.key.code))
				{
					c = getLabel((int)event.key.code)[0];
					if(event.key.shift) /* Gestion des majuscules */
						c = toupper(c);
				}
				else if(event.key.code == sf::Keyboard::Space) /* Gestion espace */
					c = ' ';
				else if(event.key.code == sf::Keyboard::Back) /* Gestion Retour arrière */
					c = 2;
				else if(event.key.code == sf::Keyboard::Period) /* Gestion du point '.' */
					c = '.';
			}
		}
		return c;
	}

	EControllerType Keyboard::getControllerType()
	{
		return KEYBOARD;
	}

	GameAction Keyboard::getAction(int keys[7],int, sf::RenderWindow*)
	{
		int i;
	
		GameAction gameAction;
		gameAction.init();
	
		for(i=0;i<7;i++)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(keys[i])) )
				gameAction.actions[i] = true;
		}
		return gameAction;
	}

	int Keyboard::getKeyPressed(int, sf::RenderWindow* window)
	{
		int k = -1;
	
		if(window != NULL)
		{
			sf::Event event;
			window->pollEvent(event);
			if(event.type == sf::Event::KeyPressed)
			{
				bool keyPressed = false;
				k = (int)(sf::Keyboard::A);
			
			
				while(k != (int)(sf::Keyboard::KeyCount) && !keyPressed)
				{
					if(event.key.code == (sf::Keyboard::Key)(k) )
						keyPressed = true;
					else
						k++;
				}
			
				if( !keyPressed )
					k = -1;
			}
		}
		return k;
	}

	void Keyboard::add(int){}

	void Keyboard::disconnect(int){}
}
