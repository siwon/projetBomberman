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
		 * \return L'action à effectuer sur le menu
		 */
		virtual EMenuKeys getMenuKey() = 0;
		
		/*!
		 * \brief Récupération d'un caractère tapé sur le clavier
		 * \return Caractère tapé sur le clavier
		 */
		virtual char getCharPressed() = 0;
	
  };
}

#endif

