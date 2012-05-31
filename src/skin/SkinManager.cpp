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
		this->colors[TEXTCOLOR] = "text";
		this->colors[TITLECOLOR] = "title";
		this->colors[LINKCOLOR] = "link";
		this->colors[SELECTEDCOLOR] = "selected";
		this->colors[ERRORCOLOR] = "error";
		this->colors[BGCOLOR] = "bg";
		this->colors[SELECTEDBGCOLOR] = "selectedbg";

		this->files[SPLASH] = "splash.png";
		this->files[WIISCREEN] = "wiiScreen.png";
		this->files[MENU_BACKGROUND] = "mback.png";
		this->files[PLAYER1] = "player1.png";
		this->files[PLAYER2] = "player2.png";
		this->files[PLAYER3] = "player3.png";
		this->files[PLAYER4] = "player4.png";
		this->files[GAME_BACKGROUND] = "gback.png";
		this->files[EIMAGE_BOX] = "box.png";
		
		//BOMB
		this->files[EIMAGE_BOMB] = "bomb.png";
		this->files[EIMAGE_MINE] = "mine.png";
		this->files[EIMAGE_REMOTEBOMB] = "remoteBomb.png";
		
		//BONUS
		this->files[EIMAGE_BOMBPLUS] = "bombMore.png";
		this->files[EIMAGE_BOMBMOINS] = "bombLess.png";
		this->files[EIMAGE_VITESSEPLUS] = "vitesseMore.png";
		this->files[EIMAGE_VITESSEMOINS] = "vitesseLess.png";
		this->files[EIMAGE_RANGEPLUS] = "rangeMore.png";
		this->files[EIMAGE_RANGEMOINS] = "rangeLess.png";
		this->files[EIMAGE_RANGEMAX] = "rangeMax.png";
		
		this->files[EIMAGE_ATOMIC] = "atomicBonus.png";
		this->files[EIMAGE_BOMBLINE] = "bombLine.png";
		this->files[EIMAGE_INFINITY] = "infinityBonus.png";
		this->files[EIMAGE_MINEBONUS] = "mineBonus.png";
		this->files[EIMAGE_REMOTEBONUS] = "remote.png";

		this->files[EIMAGE_FLAME_UP] = "flame_middle_horizontal.png";
		
		//INFECTION
		this->files[EIMAGE_CONFUSION] = "confusion.png";
		this->files[EIMAGE_CRANE] = "crane.png";
		this->files[EIMAGE_DILATATION] = "dilatation.png";
		this->files[EIMAGE_HELL] = "hell.png";
		this->files[EIMAGE_RAGE] = "rage.png";
		this->files[EIMAGE_SPASME] = "spasme.png";
		
		//PLAYER1
		this->files[EIMAGE_PLAYER1LEFT] = "red_left.png";
		this->files[EIMAGE_PLAYER1RIGHT] = "red_right.png";
		this->files[EIMAGE_PLAYER1UP] = "red_back.png";
		this->files[EIMAGE_PLAYER1DOWN] = "red_front.png";
		//PLAYER2
		this->files[EIMAGE_PLAYER2LEFT] = "green_left.png";
		this->files[EIMAGE_PLAYER2RIGHT] = "green_right.png";
		this->files[EIMAGE_PLAYER2UP] = "green_back.png";
		this->files[EIMAGE_PLAYER2DOWN] = "green_front.png";
		//PLAYER3
		this->files[EIMAGE_PLAYER3LEFT] = "white_left.png";
		this->files[EIMAGE_PLAYER3RIGHT] = "white_right.png";
		this->files[EIMAGE_PLAYER3UP] = "white_back.png";
		this->files[EIMAGE_PLAYER3DOWN] = "white_front.png";
		//PLAYER4
		this->files[EIMAGE_PLAYER4LEFT] = "black_left.png";
		this->files[EIMAGE_PLAYER4RIGHT] = "black_right.png";
		this->files[EIMAGE_PLAYER4UP] = "black_back.png";
		this->files[EIMAGE_PLAYER4DOWN] = "black_front.png";
		
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
