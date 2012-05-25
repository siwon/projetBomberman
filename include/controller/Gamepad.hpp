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
			Y_UP = 0,
			Y_DOWN,
			X_LEFT,
			X_RIGHT,
			BUT1,
			BUT2,
			BUT3,
			BUT4,
			BUT5,
			BUT6,
			BUT7,
			BUT8,
			BUT9,
			BUT10
		};
		static const std::string keysLabel[];
		
		
	private :
		std::map<int,int> gamepadsAssignation; /*!< Tableau d'assignation des joysticks aux différents joueurs */
		int nbGamepad;
		
		bool gamepadUsed(int numGamepad);
		
	public :
		
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
		
		virtual int getKeyPressed(int player,sf::RenderWindow* window);
		
		virtual std::string getLabel(int key);
		
		virtual void add(int player);
		
		virtual void disconnect(int player);
  };
}

#endif

