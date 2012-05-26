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
#include "../EControllerType.hpp"

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
		 * \param window : Fenêtre SFML
		 * \return L'action à effectuer sur le menu
		 */
		virtual EMenuKeys getMenuKey(sf::RenderWindow* window) = 0;
		
		/*!
		 * \brief Récupération d'un caractère tapé sur le clavier
		 * \param window : Fenêtre SFML
		 * \return Caractère tapé sur le clavier
		 */
		virtual char getCharPressed(sf::RenderWindow* window) = 0;
		
		/*!
		 * \brief Récupération d'une touche / bouton
		 * \param player : numéro de joueur pour la détermination de la wiimote
		 * \return Touche / bouton pressé
		 */
		virtual int getKeyPressed(int player,sf::RenderWindow* window) = 0;
		
		/*!
		 * \brief Récupération du type de contrôleur
		 * \return Type du contrôleur
		 */
		virtual EControllerType getControllerType() = 0;
		
		/*!
		 * \brief Obtenir le label d'une touche
		 * \param key : Touche dont on veut obtenir le label
		 * \return Label correspondant à key
		 */
		virtual std::string getLabel(int key) = 0;
	
		/**
		 * \brief Affecte un controleur disponible à un joueur
		 * Lance une exception PolyBomberException si aucune controleur n'est disponible
		 * \param player : joueur à qui affecter un controleur
		 */
		virtual void add(int player) = 0;
		
		/**
		 * \brief Déconnecte le controleur d'un joueur donné
		 * \param player : joueur à qui déconnecter le controleur
		 */
		virtual void disconnect(int player) = 0;
  };
}

#endif

