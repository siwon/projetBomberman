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
		this->files[WIISCREEN] = "wiiScreen.png";
		this->files[MENU_BACKGROUND] = "mback.png";
		this->files[PLAYER1] = "player1.png";
		this->files[PLAYER2] = "player2.png";
		this->files[PLAYER3] = "player3.png";
		this->files[PLAYER4] = "player4.png";
		this->files[GAME_BACKGROUND] = "gback.png";
		this->files[BOX] = "box.png";

		this->colors[TEXTCOLOR] = "text";
		this->colors[TITLECOLOR] = "title";
		this->colors[LINKCOLOR] = "link";
		this->colors[SELECTEDCOLOR] = "selected";
		this->colors[ERRORCOLOR] = "error";
		this->colors[BGCOLOR] = "bg";
		this->colors[SELECTEDBGCOLOR] = "selectedbg";

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
		std::vector<std::string> keys = configFile->getKeys();
		std::vector<std::string>::iterator it;
		
		for (it = keys.begin(); it < keys.end(); it++)
			list.push_back(configFile->getStringValue(*it));

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
		if (name.compare(this->name) != 0)
		{
			IConfigFile* configFile = new ConfigFileManager(this->PATH + "skins.conf");
			std::vector<std::string> keys = configFile->getKeys();
			std::vector<std::string>::iterator it;

			// Recherche de la clé correspondant au nom
			for (it = keys.begin(); it != keys.end(); it++)
			{
				try
				{
					std::string value = configFile->getStringValue(*it);
					if (name.compare(value) == 0)
					{
						this->folder = *it;
						std::cout << "setskin" << std::endl;
						reloadName();
						reloadTextures();
					}
				}
				catch (PolyBomberException& e) {}
			}

			delete configFile;
		}
	}
	
	std::string SkinManager::getSkin()
	{
		return this->name;
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

		reloadName();
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
		std::map<EImage, sf::Texture*>::iterator it;

		for (it = this->textures.begin(); it != this->textures.end(); it++)
		{
			std::string path = this->PATH + this->folder + "/" + this->files[(*it).first];			
			(*it).second->loadFromFile(path);
		}
	}

	void SkinManager::reloadName()
	{
		IConfigFile* configFile = new ConfigFileManager(this->PATH + "skins.conf");
		this->name = "";

		try
		{
			this->name = configFile->getStringValue(this->folder);
		}
		catch (PolyBomberException& e)
		{
			throw PolyBomberException("Impossible d'accéder à la liste des skins");
		}		

		delete configFile;
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
