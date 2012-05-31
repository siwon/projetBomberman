#ifndef _KEYBOARD
#define _KEYBOARD

/*!
 * \file Keyboard.hpp
 * \brief Classe de gestion des périphériques de type clavier
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standards 
#include <map>

// Bibliothèques SFML
#include <SFML/Window.hpp>

// Headers
#include "Controller.hpp"
#include "../EMenuKeys.hpp"
#include "GameAction.hpp"

namespace PolyBomber
{
  /*!
  * \class Keyboard
  * \brief Classe de gestion des périphériques de type clavier
  */
  class Keyboard : public Controller
  {
  
	private :
		
		static const std::string keysLabel[]; /*!< Labels des touches clavier */
		
		/**
		 * \brief Vérifie si une key SFML correspond à caractère alpha-numérique
		 * \param key : Valeur à vérifier
		 * \return Vrai si key correspond un caractère alpha-numérique, faux sinon.
		 */
		bool isAlphaNum(sf::Keyboard::Key key);
	  
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
		
		virtual EMenuKeys getMenuKey(sf::RenderWindow* window);

		/*!
		 * \brief Méthode de saisie de caractères
		 * \return Un caractère ou une valeur numérique ci-dessous :
		 * 0 : aucun caractère alphanumérique saisi
		 * 1 : autre touche appuyée
		 * 2 : retour arrière appuyé
		 */
		virtual char getCharPressed(sf::RenderWindow* window);
		
		virtual EControllerType getControllerType();
		
		virtual int getKeyPressed(int player,sf::RenderWindow* window);
		
		virtual std::string getLabel(int key);

		virtual void add(int player); /* Non disponible pour le clavier */
		
		virtual void disconnect(int player); /* Non disponible pour le clavier */
		
		virtual GameAction getAction(int keys[7],int, sf::RenderWindow*);

  };
}

#endif

