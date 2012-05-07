/*!
 * \file test_ConfigFile.cpp
 * \brief Test du module fichier de configuration
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standarts 
#include <iostream>

// Bibliothèques SFML

// Bibliothèques externes

// Headers
#include "../../include/configFile/ConfigFileManager.hpp"

using namespace PolyBomber;

int main()
{
	ConfigFileManager configFileManager("controller.conf"); // Création d'un fichier de configuration
	
	/* Ajout de quelques valeurs */
	configFileManager.setStringValue("controller.player1.type","keyboard");
	configFileManager.setIntValue("controller.player1.up",62);
	configFileManager.setIntValue("controller.player1.down",63);
	configFileManager.setIntValue("controller.player1.left",64);
	configFileManager.setIntValue("controller.player1.right",65);
	configFileManager.setIntValue("controller.player1.action1",95);
	configFileManager.setIntValue("controller.player1.action2",78);
	configFileManager.setIntValue("controller.player1.pause",89);
	
	/* Modification de valeurs */
	configFileManager.setStringValue("controller.player1.type","wiimote");
	
	/* Récupération de valeurs */
	std::cout << configFileManager.getStringValue("controller.player1.type") << std::endl;
	std::cout << configFileManager.getIntValue("controller.player1.up") << std::endl;
	
	return 0;
}
