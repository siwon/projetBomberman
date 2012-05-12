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
#include "../../include/PolyBomberException.hpp"

using namespace PolyBomber;

int main()
{
	ConfigFileManager configFileManager("controller1.conf"); // Création d'un fichier de configuration
	
	/* Récupération de valeurs */
	try
	{
		std::cout << configFileManager.getStringValue("controller.player1.type") << std::endl;
		std::cout << configFileManager.getIntValue("controller.player1.up") << std::endl;
		std::cout << configFileManager.getIntValue("controller.player2.up") << std::endl;
	}
	catch(PolyBomberException* e)
	{
		std::cout << e->what();
	}	
	
	return 0;
}
