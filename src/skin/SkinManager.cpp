/*!
 * \file SkinManager.cpp
 * \brief Gestionnaire de skin
 * \author Maxime GUIHAL
 */

#include "PolyBomberException.hpp"

#include "skin/SkinManager.hpp"
#include "configFile/ConfigFileManager.hpp"

namespace PolyBomber
{
	SkinManager::SkinManager() throw(PolyBomberException) : PATH("resources/skins/")
	{
		this->files[SPLASH] = "splash.png";

		this->colors[TEXTCOLOR] = "text";

		reloadConfig();
	}

	SkinManager::~SkinManager()
	{
		destroyTextures();
	}

	std::vector<std::string> SkinManager::getSkinsList() const
	{
		IConfigFile* configFile = new ConfigFileManager(this->PATH + "skins.conf");

		std::vector<std::string> list;
		/*std::vector<std::string> keys = configFile->getKeys();
		std::vector<std::string>::iterator it;
		
		for (it = keys.begin(); it < keys.end(); it++)
			list.push_back(configFile.getStringValue());*/

		delete configFile;
		
		return list;
	}
	
	sf::Texture* SkinManager::loadImage(EImage name)
	{
		if (this->textures.find(name) == this->textures.end())
			insertTexture(name);

		return this->textures[name];
	}
	
	sf::Color SkinManager::getColor(EColorKey key)
	{
		sf::Color color(0,0,0);

		std::string path = this->PATH + this->folder + "/colors.conf";
		IConfigFile* configFile = new ConfigFileManager(path);

		getComponent(configFile, key, color.r, ".R");
		getComponent(configFile, key, color.g, ".G");
		getComponent(configFile, key, color.b, ".B");
		getComponent(configFile, key, color.a, ".A");

		delete configFile;

		return color;
	}
	
	void SkinManager::setSkin(std::string name)
	{
		std::map<EImage, std::string>::iterator it;

		// Recherche de la clé correspondant au nom
		for (it = this->files.begin(); it != this->files.end(); it++)
		{
			if (name.compare((*it).second) == 0)
			{
				this->folder = (*it).first;
				reloadTextures();
			}
		}
	}
	
	std::string SkinManager::getSkin() throw(PolyBomberException)
	{
		IConfigFile* configFile = new ConfigFileManager(this->PATH + "skins.conf");
		std::string name = "";

		try
		{
			name = configFile->getStringValue(this->folder);
		}
		catch (PolyBomberException& e)
		{
			throw PolyBomberException("Impossible d'accéder à la liste des skins");
		}		

		delete configFile;
		return name;
	}
	
	void SkinManager::saveConfig()
	{
		IConfigFile* configFile = new ConfigFileManager();
		configFile->setStringValue("skin.folder", this->folder);
		delete configFile;		
	}
	
	void SkinManager::reloadConfig() throw(PolyBomberException)
	{
		IConfigFile* configFile = new ConfigFileManager();
		
		try
		{
			this->folder = configFile->getStringValue("skin.folder");
		}
		catch (PolyBomberException& e)
		{
			throw PolyBomberException("Impossible de récupérer le chemin du skin");
		}
		
		delete configFile;

		reloadTextures();	
	}

	void SkinManager::destroyTextures()
	{
		std::map<EImage, sf::Texture*>::iterator it;

		for (it = this->textures.begin(); it != this->textures.end(); it++)
			delete (*it).second;
	}

	void SkinManager::insertTexture(EImage key)
	{
		sf::Texture* texture = new sf::Texture();
		std::string path = this->PATH + this->folder + "/" + this->files[key];			
		texture->loadFromFile(path);
		this->textures[key] = texture;
	}

	void SkinManager::reloadTextures()
	{
		destroyTextures();

		std::map<EImage, sf::Texture*>::iterator it;

		for (it = this->textures.begin(); it != this->textures.end(); it++)
			insertTexture((*it).first);		
	}

	void SkinManager::getComponent(IConfigFile* configFile, EColorKey key, sf::Uint8& component, std::string suffix)
	{
		try
		{
			component = configFile->getIntValue(this->colors[key] + suffix);
		}
		catch (PolyBomberException& e)
		{}
	}
}
