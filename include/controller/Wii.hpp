#ifndef _WII
#define _WII

/*!
 * \file Wii.hpp
 * \brief Classe de gestion des périphériques de type Wiimote
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standards 
#include <map>

// Bibliothèques SFML
#include <SFML/Window.hpp>

// Bibliothèques externes
#include "Wiicpp.hpp"

// Headers
#include "Controller.hpp"
#include "EMenuKeys.hpp"
#include "EControllerType.hpp"
#include "GameAction.hpp"

namespace PolyBomber
{
  /*!
  * \class Wii
  * \brief Classe de gestion des périphériques de type Wiimote
  */
  class Wii : public Controller
  {	  
	private :
		
		std::map<CButtons::ButtonDefs,std::string> keysLabel; /*!< Map de correspondance touche <=> label */
		
		std::map<int,CWiimote*> wiimotesAssignation; /*!< Tableau d'assignation des wiimotes aux différents joueurs */
		
		static int LED_MAP[4]; /*!< Leds des wiimotes */
		
		static int nbWiimotes; /*!< Nombre de wiimotes utilisées */
		
		std::vector<CWiimote> wiimotes; /*!< Tableau de wiimotes connectées */
		
		GameAction* gameActions;
		
		int numFound; /*!< Nombre de wiimotes connectées au pc */
		
		CWii* wii; /*!< Gestionnaire des périphériques wiimotes */
		
		/**
		 * \brief Rechargement des wiimotes
		 */
		void reload();
		
		/**
		 * \brief Effectue l'initialisation (leds,..) des wiimotes connectées
		 */
		void setupWiimotes();

	public :

		/**
		 * \brief Constructeur de la classe Wii
		 */
		Wii();
		
		/**
		 * \brief Destructeur de la classe Wii
		 */
		~Wii();
		
		/*!
		 * \see Controller#getMenuKey
		 */
		virtual EMenuKeys getMenuKey(sf::RenderWindow* window);
		
		/*!
		 * \see Controller#getControllerType
		 */
		virtual EControllerType getControllerType();

		/*!
		 * \see Controller#getCharPressed
		 */
		virtual char getCharPressed(sf::RenderWindow* window); /* Non disponible pour les wiimotes*/

		/*!
		 * \see Controller#getKeyPressed
		 */
		virtual int getKeyPressed(int player,sf::RenderWindow* window);

		/*!
		 * \see Controller#getLabel
		 */
		virtual std::string getLabel(int key);
		
		/*!
		 * \see Controller#add
		 */
		virtual void add(int player);
		
		/*!
		 * \see Controller#disconnect
		 */
		virtual void disconnect(int player);
		
		/*!
		 * \see Controller#getAction
		 */
		virtual GameAction getAction(int keys[7],int, sf::RenderWindow*);

  };
}

#endif
