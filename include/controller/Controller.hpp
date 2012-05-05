#ifndef _CONTROLLER
#define _CONTROLLER

/*!
 * \file Controller.hpp
 * \brief Classe abstraite représentant un contrôleur de jeu
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques SFML
#include <SFML/Graphics.hpp>

// Headers
#include "../EMenuKeys.hpp"

namespace PolyBomber
{
  /*!
  * \class Controller
  * \brief Classe abstraite représentant un contrôleur de jeu
  */
  class Controller
  {
	  public :
		/*!
		 * \brief Constructeur de la classe Controller
		 */
		Controller();
		
		/*!
		 * \brief Destructeur de la classe Controller
		 */
		virtual ~Controller();
		
		/*!
		 * \brief Récupération de la touche appuyée sur le menu
		 * \param app : Fenêtre SFML
		 * \return L'action à effectuer sur le menu
		 */
		virtual EMenuKeys getMenuKey() = 0;
		
		virtual char getCharPressed(sf::RenderWindow* app) = 0;
	
  };
}

#endif

