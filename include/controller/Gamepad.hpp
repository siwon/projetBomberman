#ifndef _GAMEPAD
#define _GAMEPAD

/*!
 * \file Gamepad.hpp
 * \brief Classe de gestion des périphériques de type joystick
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standards 

// Bibliothèques SFML
#include <SFML/Window.hpp>

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
	public :
		/**
		 * \enum Keys
		 * \brief Enumération des touches disponibles pour un controleur de type Joystick
		 */
		enum Keys
		{
			X = sf::Joystick::X,
			Y = sf::Joystick::Y,
			But1,
			But2,
			But3,
			But4,
			But5,
			But6
		};
		static const std::string keysLabel[];
		
		
	private :
		std::map<int,int> gamepadsAssignation; /*!< Tableau d'assignation des joysticks aux différents joueurs */
		
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
		
		virtual EMenuKeys getMenuKey(sf::RenderWindow* window);
		
		virtual EControllerType getControllerType();
		
		virtual char getCharPressed(); /* Non disponible pour les joystick */
		
		virtual int getKeyPressed(int player);
		
		virtual std::string getLabel(int key);
		
		virtual void add(int player);
		
		virtual void disconnect(int player);
  };
}

#endif

