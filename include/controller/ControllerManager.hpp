#ifndef _CONTROLLERMANAGER
#define _CONTROLLERMANAGER

/*!
 * \file ControllerManager.hpp
 * \brief Classe de gestion des contrôleurs de jeu
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standarts 
#include <string>
#include <vector>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>

// Bibliothèques externes

// Headers
#include "../EMenuKeys.hpp"
#include "../SKeysConfig.hpp"
#include "../IControllerToMenu.hpp"
#include "../IControllerToMenu.hpp"
//#include "../IControllerToNetwork.hpp"
#include "Controller.hpp"



namespace PolyBomber
{
  /*!
  * \class ControllerManager
  * \brief Classe de gestion des contrôleurs de jeu
  */
  class ControllerManager : public IControllerToMenu
  {
	private:
		
		static ControllerManager* controllerManager; /*!< Unique instance de la classe */
		
		vector<SKeysConfig> keysAssignation; /*!<  Tableau de configuration des touches pour chaque joueur */
		
		sf::RenderWindow* app; /*!< Fenetre SFML */
		
		vector<Controller*> controllers; /*!< Vecteur des contrôleurs de jeu disponible */
		
		//ConfigFileManager* configFileManager;
		
		/*!
		 * \brief Constructeur de la classe ControllerManager
		 */
		ControllerManager(sf::RenderWindow*);
		
		/*!
		 * \brief Destructeur de la classe ControllerManager
		 */
		~ControllerManager();
		
	public:
		/*!
		 * \brief Obtenir l'instance de la classe ControllerManager
		 * Cette méthode permet d'obtenir l'unique instance de la classe ControllerManager ou de la créer si celle-ci n'existe pas.
		 * Permet la mise en place du patron singleton
		 * \param app : Fenêtre SFML
		 * \return Instance de la classe ControllerManager
		 */
		static ControllerManager* getInstance(sf::RenderWindow* app);
		
		/* Méthodes de l'interface IControllerToMenu */
		
		virtual EMenuKeys getKeyPressed();
		
		virtual char getCharPressed();
		
		virtual SKeysConfig getConfig(int player);
	  
  };
}

#endif

