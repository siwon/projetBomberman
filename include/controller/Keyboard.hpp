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
		
		/*!
		 * @see Controller#getMenuKey
		 */
		virtual EMenuKeys getMenuKey(sf::RenderWindow* window);

		/*!
		 * @see Controller#getCharPressed
		 * \brief Méthode de saisie de caractères
		 * \return Un caractère ou une valeur numérique ci-dessous :
		 * 0 : aucun caractère alphanumérique saisi
		 * 1 : autre touche appuyée
		 * 2 : retour arrière appuyé
		 */
		virtual char getCharPressed(sf::RenderWindow* window);
		
		/*!
		 * @see Controller#getControllerType
		 */
		virtual EControllerType getControllerType();
		
		/*!
		 * @see Controller#getKeyPressed
		 */
		virtual int getKeyPressed(int player,sf::RenderWindow* window);
		
		/*!
		 * @see Controller#getLabel
		 */
		virtual std::string getLabel(int key);
		
		/*!
		 * @see Controller#add
		 */
		virtual void add(int player); /* Non disponible pour le clavier */
		
		/*!
		 * @see Controller#disconnect
		 */
		virtual void disconnect(int player); /* Non disponible pour le clavier */
		
		/*!
		 * @see Controller#getAction
		 */
		virtual GameAction getAction(int keys[7],int, sf::RenderWindow*);

  };
}

#endif

