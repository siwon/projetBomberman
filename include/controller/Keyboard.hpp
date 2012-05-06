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
	private :
		std::map<sf::Keyboard::Key, char> keys; /*!< Correspondance touches clavier <=> caractère */
	public :
		/*!
		 * \brief Constructeur de la classe Keyboard
		 * Initialise la map de correspondance des touches clavier
		 */
		Keyboard();
		
		/*!
		 * \brief Destructeur de la classe Keyboard
		 */
		virtual ~Keyboard();
		
		/* Méthodes de la classe Controller */
		
		virtual EMenuKeys getMenuKey();
		
		char getCharPressed();

		

  };
}

#endif

