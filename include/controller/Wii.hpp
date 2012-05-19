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

// Headers
#include "Controller.hpp"
#include "../EMenuKeys.hpp"
#include "../EControllerType.hpp"
#include "Wiicpp.hpp"

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
		
		/* Méthodes de la classe Controller */

		virtual EMenuKeys getMenuKey(sf::RenderWindow* window);

		virtual EControllerType getControllerType();

		virtual char getCharPressed(); /* Non disponible pour les wiimotes*/

		virtual int getKeyPressed(int player);

		virtual std::string getLabel(int key);
		
		virtual void addWiimote(int player);
		
		virtual void disconnectWiimote(int player);

  };
}

#endif
