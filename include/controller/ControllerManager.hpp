#ifndef _CONTROLLERMANAGER
#define _CONTROLLERMANAGER

/*!
 * \file ControllerManager.hpp
 * \brief Classe de gestion des contrôleurs de jeu
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standards 
#include <string>
#include <vector>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>

// Bibliothèques externes

// Headers
#include "EMenuKeys.hpp"
#include "EGameKeys.hpp"
#include "SKeysConfig.hpp"

#include "IControllerToMenu.hpp"
#include "IControllerToNetwork.hpp"

#include "configFile/ConfigFileManager.hpp"

#include "TSingleton.hpp"

#include "Controller.hpp"
#include "Wii.hpp"


namespace PolyBomber
{
  /*!
  * \class ControllerManager
  * \brief Classe de gestion des contrôleurs de jeu
  */
  class ControllerManager : public IControllerToMenu,
						public IControllerToNetwork,
								public Singleton<ControllerManager>
  {
	friend class Singleton<ControllerManager>; /* Utilisation du template singleton */
	
	private:
		/*!
		* \class ControllerAssignation
		* \brief Classe interne d'assignation des contrôleurs de jeu aux différents joueurs
		*/
		class ControllerAssignation
		{
			private :
				Controller* controller; /*!< Controleur assigné */
				int keys[7]; /*!< Touches / Boutons configurés */
				
			public :
				/*!
				* \brief Constructeur de la classe ControllerAssignation
				*/
				ControllerAssignation();
				
				/*!
				* \brief Destructeur de la classe ControllerAssignation
				*/
				~ControllerAssignation();
				
				/*!
				* \brief Obtenir le controller assigné
				* \return Controleur de jeu assigné
				*/
				Controller* getController();
				
				/*!
				* \brief Assigner un controleur
				* \return controleur : Controleur à assigner
				*/
				void setController(Controller* controller);
				
				/*!
				* \brief Assigner une touche / bouton pour une action donnée
				* \param key : Action donnée
				* \param value : Touche / Bouton correspondant
				*/
				void setKeys(EGameKeys key, int value);
				
				/*!
				* \brief Obtenir la touche / bouton associé à une action donnée
				* \param key : Action donnée
				* \return Touche / Bouton correspondant
				*/
				int getKey(EGameKeys key);
				
				/*!
				* \brief Obtenir les touches configurées
				* \return Tableau de touches configurées
				*/
				int* getKeys();
				
				/*!
				 * \brief Assigne la configuration par défaut pour une wiimote
				 */
				void setDefaultWiimoteConfig();
				
				/*!
				 * \brief Assigne la configuration par défaut pour un joystick
				 */
				void setDefaultGamepadConfig();
				
				/*!
				 * \brief Assigne la configuration par défaut clavier pour un joueur donné
				 */
				void setDefaultKeyboardConfig(int player);
				
		};
	
		Controller* keyboard; /*!< Controleur de type clavier */
		
		Controller* wii; /*!< Controleurs de type wiimote */
		
		Controller* gamepad; /*!< Controleurs de type joystick */
		
		ControllerAssignation* controllerAssignation; /*!< Tableau des controleur assigné pour chaque joueur */
		
		ConfigFileManager* configFileManager; /*!< Gestion du fichier de configuration */
		
		sf::RenderWindow* window; /*!< Fenetre SFML pour gérer les événements */
		
		/*!
		 * \brief Constructeur de la classe ControllerManager
		 */
		ControllerManager();
		
		/*!
		 * \brief Destructeur de la classe ControllerManager
		 */
		~ControllerManager();
		
		/*!
		 * \brief Initialise à faux une structure SKeyPressed
		 * \return Structure initialisée
		 */
		SKeyPressed initSKeyPressed();
		
		/*!
		 * \brief Vérifie si une touche n'est pas déjà assignée
		 * \param key : code touche
		 * \param player : joueur demandant l'assignation de la touche
		 * \return Vrai si la touche est déjà utilisée, faux sinon.
		 */
		bool keyUsed(int key, int player);
		
		/*!
		 * \brief Charge la configuration des contrôleurs
		 */
		void loadControllerConfig();
		
	public:
		
		/*!
		 * \brief Instancie le controleur wii
		 */
		void setWii();
		
		/*!
		 * \see IControllerToMenu::getKeyPressed
		 */
		virtual EMenuKeys getKeyPressed();
		
		/*!
		 * \see IControllerToMenu::getCharPressed
		 */
		virtual char getCharPressed();
		
		/*!
		 * \see IControllerToMenu::getConfig
		 */
		virtual SKeysConfig getConfig(int player);
		
		/*!
		 * \see IControllerToMenu::reloadConfig
		 */
		virtual void reloadConfig();
		
		/*!
		 * \see IControllerToMenu::setPlayerKey
		 */
		virtual SKeysConfig setPlayerKey(int player, EGameKeys key);
		
		/*!
		 * \see IControllerToMenu::setPlayerController
		 */
		virtual SKeysConfig setPlayerController(int player, EControllerType type);
		
		/*!
		 * \see IControllerToMenu::save
		 */
		virtual void save();
		
		/*!
		 * \see IControllerToMenu::setWindow
		 */
		virtual void setWindow(sf::RenderWindow* window);
		
		/*!
		 * \see IControllerToNetwork::getKeysPressed
		 */
		virtual SKeyPressed getKeysPressed();
	  
  };
}

#endif

