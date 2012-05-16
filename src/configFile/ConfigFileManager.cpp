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
#include <SFML/Window.hpp>

// Bibliothèques externes

// Headers
#include "../../include/configFile/ConfigFileManager.hpp"
#include "../../include/PolyBomberException.hpp"
#include "../../include/EControllerType.hpp"
#include "../../include/controller/Gamepad.hpp"

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

void ConfigFileManager::setDefaultGamepadConfig(int player)
{
	std::stringstream ss;
	ss << "controller.player" << player << "type";
	this->setIntValue(ss.str(), GAMEPAD);
	
	ss.str("");
	ss << "controller.player" << player << "up";
	this->setIntValue(ss.str(), Gamepad::X);
	
	ss.str("");
	ss << "controller.player" << player << "down";
	this->setIntValue(ss.str(), Gamepad::Y);
	
	ss.str("");
	ss << "controller.player" << player << "left";
	this->setIntValue(ss.str(), Gamepad::X);
	
	ss.str("");
	ss << "controller.player" << player << "right";
	this->setIntValue(ss.str(), Gamepad::X);
	
	ss.str("");
	ss << "controller.player" << player << "action1";
	this->setIntValue(ss.str(), Gamepad::But1);
	
	ss.str("");
	ss << "controller.player" << player << "action2";
	this->setIntValue(ss.str(), Gamepad::But2);
	
	ss.str("");
	ss << "controller.player" << player << "pause";
	this->setIntValue(ss.str(), Gamepad::But3);
}
	
	
void ConfigFileManager::setDefaultKeyboardConfig(int player)
{
	switch(player)
	{
		case 1 :
			this->setIntValue("controller.player1.type", KEYBOARD);
			this->setIntValue("controller.player1.up", sf::Keyboard::Up);
			this->setIntValue("controller.player1.down", sf::Keyboard::Down);
			this->setIntValue("controller.player1.left", sf::Keyboard::Left);
			this->setIntValue("controller.player1.right", sf::Keyboard::Right);
			this->setIntValue("controller.player1.action1", sf::Keyboard::RControl);
			this->setIntValue("controller.player1.action2", sf::Keyboard::RShift);
			this->setIntValue("controller.player1.pause",sf::Keyboard::Return);
			break;
			
		case 2 :
			this->setIntValue("controller.player2.type", KEYBOARD);
			this->setIntValue("controller.player2.up", sf::Keyboard::Z);
			this->setIntValue("controller.player2.down", sf::Keyboard::S);
			this->setIntValue("controller.player2.left", sf::Keyboard::Q);
			this->setIntValue("controller.player2.right", sf::Keyboard::D);
			this->setIntValue("controller.player2.action1", sf::Keyboard::LControl);
			this->setIntValue("controller.player2.action2", sf::Keyboard::LShift);
			this->setIntValue("controller.player2.pause", sf::Keyboard::Escape);
			break;
			
		case 3 :
			this->setIntValue("controller.player3.type", KEYBOARD);
			this->setIntValue("controller.player3.up", sf::Keyboard::Numpad8);
			this->setIntValue("controller.player3.down", sf::Keyboard::Numpad5);
			this->setIntValue("controller.player3.left", sf::Keyboard::Numpad4);
			this->setIntValue("controller.player3.right", sf::Keyboard::Numpad6);
			this->setIntValue("controller.player3.action1", sf::Keyboard::Numpad0);
			this->setIntValue("controller.player3.action2", sf::Keyboard::Add);
			this->setIntValue("controller.player3.pause", sf::Keyboard::Subtract);
			break;
			
		case 4 :
			this->setIntValue("controller.player4.type", KEYBOARD);
			this->setIntValue("controller.player4.up", sf::Keyboard::I);
			this->setIntValue("controller.player4.down", sf::Keyboard::K);
			this->setIntValue("controller.player4.left", sf::Keyboard::J);
			this->setIntValue("controller.player4.right", sf::Keyboard::L);
			this->setIntValue("controller.player4.action1", sf::Keyboard::Space);
			this->setIntValue("controller.player4.action2", sf::Keyboard::M);
			this->setIntValue("controller.player4.pause", sf::Keyboard::P);
			break;
			
		default :
			break;
	}
}

void ConfigFileManager::createDefault()
{
	/* Default player's configuration */
	for(int i=0; i<4; i++)
		this->setDefaultKeyboardConfig(i);
	
	// A compléter pour les skins,...
	
}

void ConfigFileManager::openFile()
{
	
	if(!configFile.is_open()) // si le fichier n'est pas déjà ouvert
	{
		
			
		configFile.open(configFileName.c_str(), std::fstream::in | std::fstream::out);
		
		if(configFile.fail()) // Le fichier n'existe pas 
		{
			#if DEBUG
				std::cout << "Création du fichier de configuration : " << configFileName << std::endl;
			#endif
			configFile.open(configFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
			this->createDefault();
		}		
		
		#if DEBUG
			std::cout << "Ouverture du fichier de configuration : " << configFileName << std::endl;
		#endif
			
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
		#if DEBUG
			std::cout << "Key already present => value changed" << std::endl;
		#endif
		std::map<std::string,std::string>::iterator it;
		it = fileContents.find(key);
		(*it).second = value;
	}
	else
	{
		#if DEBUG
			std::cout << "New key inserted" << std::endl;
		#endif
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
		std::stringstream ss;
		ss << "Clé " << key << " non présente.\n";
		throw new PolyBomberException(ss.str());
	}	
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
	if(contains(key))
		fileContents.erase(key);
}
	
	
bool ConfigFileManager::contains(std::string key)
{
	return fileContents.count(key);
}