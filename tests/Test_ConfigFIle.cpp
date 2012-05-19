/*!
 * \file Test_ConfigFile.cpp
 * \brief Test du module ConfigFile
 * \author Alexandre BISIAUX
 */

#include "../../include/configFile/ConfigFileManager.hpp"
#include "../../include/PolyBomberException.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace PolyBomber;


int main(void)
{
	ConfigFileManager* configFileManager = new ConfigFileManager("test.conf");

	std::vector<std::string> keys = configFileManager->getKeys();
	
	int i;
	for(i=0;i<keys.size();i++)
		std::cout << keys[i] << std::endl;
	
	configFileManager->setStringValue("skin2", "test avec espace");
	
	try
	{
		//std::cout << configFileManager->getStringValue("skin") << std::endl;
		std::cout << configFileManager->getStringValue("skin2") << std::endl;
	}
	catch(PolyBomberException e)
	{
		std::cout << e.what();
	}
	
	delete configFileManager;
	
	return 0;
}