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
#include "../SKeysConfig.hpp"
#include "KeyboardKeys.hpp"
namespace PolyBomber
{
  /*!
  * \class Keyboard
  * \brief Classe de gestion des périphériques de type clavier
  */
  class Keyboard : public Controller
  {
	  
	public :
		KeyboardKeys keys;
		
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
		
		virtual char getCharPressed();
		
		virtual EControllerType getControllerType();
		
		virtual int getKeyPressed();
		

		

  };
}

#endif

