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
		#if DEBUG
			std::cout << "Fermeture du fichier de configuration : " << configFileName << std::endl;
		#endif
		configFile.close();
	}
}

void ConfigFileManager::setStringValue(std::string key, std::string value)
{
	if(contains(key))
		remove(key);
	
	std::string buffer = key + ":" + value;
	configFile << buffer << std::endl;
}

void ConfigFileManager::setIntValue(std::string key, int value)
{
	if(contains(key))
		remove(key);
	
	std::ostringstream ss;
	ss << value;
	
	std::string buffer = key + ":" + ss.str();
	configFile << buffer << std::endl;
}

std::string ConfigFileManager::getStringValue(std::string key)
{
	configFile.seekp(std::ios_base::beg);
	
	std::string k;
	std::string v;
	
	std::string line;
	size_t pos;
	bool found = false;
	
	configFile >> line;
	
	while(!configFile.eof() && !found)
	{
		pos = line.find(":");
		if(pos != std::string::npos)
		{
			k = line.substr(0,pos);
			if(k.compare(key) == 0)
			{
				found = true;
				v = line.substr(pos+1,line.length());
			}
		
		}
		configFile >> line;
	}
	
	return v;
}

int ConfigFileManager::getIntValue(std::string key)
{
	std::string v = getStringValue(key);
	
	std::istringstream iss(v);
	
	int value;
	
	iss >> value;
	
	return value;
}

void ConfigFileManager::remove(std::string key)
{
	std::string buffer;
	std::string line,k;
	size_t pos;
	
	configFile >> line;
	
	while(!configFile.eof())
	{
		pos = line.find(":");
		if(pos!= std::string::npos)
		{
			k = line.substr(0,pos);
			if(k.compare(key) != 0)
			{
				buffer.append(line+"\n");
			}
		
		}
		configFile >> line;
	}
	closeFile();
	configFile.open(configFileName.c_str(), std::ios::in | std::ios::out | std::ios::trunc);
	configFile << buffer;
	closeFile();
	openFile();
}
	
	
bool ConfigFileManager::contains(std::string key)
{
	configFile.seekp(std::ios_base::beg);
	
	std::string k,line;
	
	bool found = false;
	
	size_t pos;
	
	configFile >> line;
	
	while(!configFile.eof() && !found)
	{
		pos = line.find(":");
		if(pos != std::string::npos)
		{
			k = line.substr(0,pos);
			if(k.compare(key) == 0)
			{
				found = true;
			}
		
		}
		configFile >> line;
	}
	closeFile();
	openFile();
	return found;
}

int main()
{
	ConfigFileManager configFileManager;
	
	//ConfigFileManager configFileManager("/home/alex/Bureau/bombi.conf");
	
	configFileManager.setStringValue("controller.player1.type","keyboard");
	configFileManager.setIntValue("controller.player1.up",62);
	
	std::cout << configFileManager.getStringValue("controller.player1.type") << std::endl;
	
	std::cout << configFileManager.getIntValue("controller.player1.up") << std::endl;
	
	return 0;
}
