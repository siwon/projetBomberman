#ifndef _KEYBOARD
#define _KEYBOARD

/*!
 * \file Keyboard.hpp
 * \brief Classe de gestion des périphériques de type clavier
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standarts 
#include <map>

// Headers
#include "Controller.hpp"
#include "../EMenuKeys.hpp"

namespace PolyBomber
{
  /*!
  * \class Keyboard
  * \brief Classe de gestion des périphériques de type clavier
  */
  class Keyboard : public Controller
  {
	  public :
		Keyboard();
		virtual ~Keyboard();
		virtual EMenuKeys getMenuKey();
		char getCharPressed(sf::RenderWindow* app);
		
		std::map<sf::Keyboard::Key, char> keys;

  };
}

#endif

