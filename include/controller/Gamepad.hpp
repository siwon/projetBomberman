#ifndef _GAMEPAD
#define _GAMEPAD

/*!
 * \file Gamepad.hpp
 * \brief Classe de gestion des périphériques de type joystick
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standarts 

// Headers
#include "Controller.hpp"
#include "../EMenuKeys.hpp"
#include "../SKeysConfig.hpp"

namespace PolyBomber
{
  /*!
  * \class Gamepad
  * \brief Classe de gestion des périphériques de type joystick
  */
  class Gamepad : public Controller
  {
	private :
		int noGamepad;
		
	public :
		static int nbGamepad;
		/*!
		 * \brief Constructeur de la classe Gamepad
		 */
		Gamepad();
		
		/*!
		 * \brief Destructeur de la classe Gamepad
		 */
		virtual ~Gamepad();
		
		/* Méthodes de la classe Controller */
		
		virtual EMenuKeys getMenuKey();
		
		virtual EControllerType getControllerType();
		
		virtual char getCharPressed(); /* Non disponible pour les joystick */
		
		virtual int getKeyPressed();

  };
}

#endif

