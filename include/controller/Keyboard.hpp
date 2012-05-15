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
		
		virtual EMenuKeys getMenuKey();
		
		virtual char getCharPressed();
		
		virtual EControllerType getControllerType();
		
		virtual int getKeyPressed();
		
		virtual std::string getLabel(int key);


  };
}

#endif

