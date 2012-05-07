/*!
 * \file ConfigFileManager.cpp
 * \brief Implémentation de la classe ConfigFileManager
 * \author Alexandre BISIAUX
 */

#define DEBUG 0

/* Includes */

// Bibliothèques standarts 
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

// Bibliothèques SFML

// Bibliothèques externes

// Headers
#include "../../include/IConfigFile.hpp"
#include "../../include/configFile/ConfigFileManager.hpp"


using namespace PolyBomber;

ConfigFileManager::ConfigFileManager()
{
	configFileName = "polyBomber.conf";
	this->openFile();
}

ConfigFileManager::ConfigFileManager(std::string path)
{
	configFileName.erase();
	configFileName.assign(path);
	
	this->openFile();
	
}

ConfigFileManager::~ConfigFileManager()
{
	closeFile();
}

void ConfigFileManager::createDefault()
{
	
}

void ConfigFileManager::openFile()
{
	
	if(!configFile.is_open()) // si le fichier n'est pas déjà ouvert
	{
		#if DEBUG
			std::cout << "Ouverture du fichier de configuration : " << configFileName << std::endl;
		#endif
		configFile.open(configFileName.c_str(), std::ios::in | std::ios::out | std::ios::app);
		
		/* Stockage du contenu du fichier dans la map */
		std::string buffer;
		std::string line,k,v;
		size_t pos;
	
		configFile >> line;
	
		while(!configFile.eof())
		{
			pos = line.find(":");
			if(pos!= std::string::npos)
			{
				k = line.substr(0,pos);
				v = line.substr(pos+1,line.length());
				fileContents.insert(std::pair<std::string,std::string>(k,v));
			}
			configFile >> line;
		}
	}
	else
	{
		#if DEBUG
			std::cout << "Fichier de configuration déjà ouvert!" << std::endl;
		#endif
	}
}

void ConfigFileManager::closeFile()
{
	if(configFile.is_open())
	{
		configFile.close();
		#if DEBUG
			std::cout << "Fermeture du fichier de configuration : " << configFileName << std::endl;
			std::cout << "Ouverture du fichier de configuration : " << configFileName << std::endl;
		#endif	
		configFile.open(configFileName.c_str(), std::ios::in | std::ios::out | std::ios::trunc);
		std::map<std::string,std::string>::iterator it;
		
		/* Recopie du contenu de la map dans le fichier */
		for(it = fileContents.begin(); it != fileContents.end(); it++)
		{
			configFile << (*it).first << ":" << (*it).second << std::endl;
		}
			
		#if DEBUG
			std::cout << "Fermeture du fichier de configuration : " << configFileName << std::endl;
		#endif
		configFile.close();
	}
}

void ConfigFileManager::setStringValue(std::string key, std::string value)
{
	if(contains(key))
	{
		std::map<std::string,std::string>::iterator it;
		it = fileContents.find(key);
		(*it).second = value;
	}
	else
	{
		fileContents.insert(std::pair<std::string,std::string>(key,value));
	}
}

void ConfigFileManager::setIntValue(std::string key, int value)
{
	std::ostringstream ss;
	ss << value;
	
	this->setStringValue(key,ss.str());
}

std::string ConfigFileManager::getStringValue(std::string key)
{
	if(contains(key))
	{
		std::map<std::string,std::string>::iterator it;
		it = fileContents.find(key);
		return (*it).second;
	}
	else
	{
		return "";
	}	
}

int ConfigFileManager::getIntValue(std::string key)
{
	if(contains(key))
	{
		std::string v = getStringValue(key);
		
		std::istringstream iss(v);
		
		int value;
		
		iss >> value;
		
		return value;
	}
	else
	{
		return -1;
	}
}

void ConfigFileManager::remove(std::string key)
{
	if(contains(key))
		fileContents.erase(key);
}
	
	
bool ConfigFileManager::contains(std::string key)
{
	return fileContents.count(key);
}

int main()
{
	ConfigFileManager configFileManager;
	
	//ConfigFileManager configFileManager("/home/alex/Bureau/bombi.conf");
	
	configFileManager.setStringValue("controller.player1.type","keyboard");
	configFileManager.setIntValue("controller.player1.up",62);
	
	//configFileManager.setStringValue("controller.player1.type","wiimote");
	
	std::cout << configFileManager.getStringValue("controller.player1.type") << std::endl;
	
	std::cout << configFileManager.getIntValue("controller.player1.up") << std::endl;
	
	return 0;
}
