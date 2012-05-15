#ifndef _CONFIGFILEMANAGER
#define _CONFIGFILEMANAGER

/*!
 * \file ConfigFileManager.hpp
 * \brief Classe de gestion du fichier de configuration
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standarts 
#include <string>
#include <fstream>
#include <map>

// Bibliothèques SFML

// Bibliothèques externes

// Headers
#include "../IConfigFile.hpp"



namespace PolyBomber
{
  /*!
  * \class ConfigFileManager
  * \brief Classe de gestion du fichier de configuration
  */
  class ConfigFileManager : public IConfigFile
  {
	private :

		std::fstream configFile; /*!< Fichier de configuration */
		
		std::string configFileName; /*!< Nom du fichier de configuration */
		
		std::map<std::string,std::string> fileContents; /*!< Map permettant de stocker le contenu du fichier permettant de limiter
											le nombre d'accès au fichier */

	public :
		
		/*!
		 * \brief Constructeur de la classe ConfigFileManager
		 */
		ConfigFileManager();
		
		/*!
		 * \brief Constructeur de la classe ConfigFileManager
		 * \param Chemin du fichier de configuration
		 */
		ConfigFileManager(std::string path);
		
		/*!
		 * \brief Destructeur de la classe ConfigFileManager
		 */
		virtual ~ConfigFileManager();
		
		/* Méthodes de IConfigFile */

		virtual void setStringValue(std::string key, std::string value);

		virtual void setIntValue(std::string key, int value);

		virtual std::string getStringValue(std::string key);

		virtual int getIntValue(std::string key);
		
		/*!
		 * \brief Ecriture de la configuration clavier par défaut du joueur donné
		 */
		void setDefaultKeyboardConfig(int player);
		
		/*!
		 * \brief Ecriture de la configuration joystick par défaut du joueur donné
		 */
		void setDefaultGamepadConfig(int player);
		
		/*!
		 * \brief Ecriture de la configuration wiimote par défaut du joueur donné
		 */
		void setDefaultWiimoteConfig(int player);
		
	private :
		
		/*!
		 * \brief Ouvre le fichier de configuration
		 */
		void openFile();
		
		/*!
		 * \brief Ferme le fichier de configuration
		 */
		void closeFile();
		
		/*!
		 * \brief Vérifie la présence d'une clé dans le fichier de configuration
		 * \param Clé recherchée
		 * \return Vrai si la clé est présente, Faux sinon
		 */
		bool contains(std::string key);
		
		/*!
		 * \brief Supprime l'entrée clé,valeur dont la clé correspond à key
		 * \param Clé de l'entrée à supprimer
		 */
		void remove(std::string key);
		
		/*!
		 * \brief Création d'un fichier de configuration par défaut si celui-ci n'existe pas
		 */
		void createDefault();
		

  };
}

#endif
