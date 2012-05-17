/*!
 * \file SkinManager.cpp
 * \brief Gestionnaire de skin
 * \author Maxime GUIHAL
 */

#include "skin/SkinManager.hpp"

namespace PolyBomber
{
	SkinManager::SkinManager()
	{}

	SkinManager::~SkinManager()
	{}

	std::vector<std::string> SkinManager::getSkinsList()
	{
		std::vector<std::string> v;
		return v;
	}
	
	sf::Texture* SkinManager::loadImage(EImage name)
	{
		sf::Texture* t = new sf::Texture();
		t->loadFromFile("logo.png");
		return t;
	}
	
	sf::Color SkinManager::getColor(EColorKey key)
	{
		sf::Color c;
		return c;
	}
	
	void SkinManager::setSkin(std::string name)
	{

	}
	
	std::string SkinManager::getSkin()
	{
		return 0;
	}
	
	void SkinManager::saveConfig()
	{

	}
	
	void SkinManager::reloadConfig()
	{

	}
}
