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
#include "../EMenuKeys.hpp"
#include "../EGameKeys.hpp"
#include "../SKeysConfig.hpp"
#include "../IControllerToMenu.hpp"
#include "../configFile/ConfigFileManager.hpp"
#include "../IControllerToNetwork.hpp"
#include "Controller.hpp"
#include "../TSingleton.hpp"
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
				int getKeys(EGameKeys key);
				
				void setDefaultWiimoteConfig();
				void setDefaultGamepadConfig();
				void setDefaultKeyboardConfig(int player);
		};
	
		Controller* keyboard; /*!< Controleur de type clavier toujours instancié */
		
		Controller* wii;
		
		ControllerAssignation* controllerAssignation; /*!< Tableau des controleur assigné pour chaque joueur */
		
		ConfigFileManager* configFileManager; /*!< Gestion du fichier de configuration */
		
		sf::RenderWindow* window;
		
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
		 * \brief Obtenir l'action de jeu à effectuer suivant un code touche / bouton appuyé
		 * \param key : code touche / bouton
		 * \param player : joueur courant
		 * \return Action à effectuer
		 */
		EGameKeys getAction(int key, int player);
		
		/*!
		 * \brief Vérifie si une touche n'est pas déjà assignée
		 * \param key : code touche
		 * \return Vrai si la touche est déjà utilisée, faux sinon.
		 */
		bool keyUsed(int key);
		
	public:
		
		/* Méthodes de l'interface IControllerToMenu */
		
		virtual EMenuKeys getKeyPressed();
		
		virtual char getCharPressed();
		
		virtual SKeysConfig getConfig(int player);
		
		virtual void reloadConfig();
		
		virtual SKeysConfig setPlayerKey(int player, EGameKeys key);
		
		virtual SKeysConfig setPlayerController(int player, EControllerType type);
		
		virtual void save();
		
		virtual void setWindow(sf::RenderWindow* window);
		
		/* Méthodes de l'interface IControllerToNetwork */
		
		virtual SKeyPressed getKeysPressed();
		
		void printConfig(int player);
	  
  };
}

#endif

