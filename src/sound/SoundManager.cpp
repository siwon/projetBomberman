/*!
 * \file SoundManager.cpp
 * \brief Gestionnaire de son
 * \author Maxime GUIHAL
 */

#include "sound/SoundManager.hpp"

namespace PolyBomber
{
	SoundManager::SoundManager()
	{
		
	}

	SoundManager::~SoundManager()
	{

	}

	void SoundManager::playSound(ESound sound)
	{

	}
	
	void SoundManager::playMusic(EMusic music)
	{

	}
	
	void SoundManager::stopMusic(EMusic music) 
	{

	}
	
	void SoundManager::setSoundVolume(unsigned int volume)
	{

	}
	
	unsigned int SoundManager::getSoundVolume()
	{
		return 70;
	}
	
	void SoundManager::setMusicVolume(unsigned int volume)
	{
		std::cout << "now volume at : " << volume << std::endl;
	}
	
	unsigned int SoundManager::getMusicVolume()
	{
		return 40;
	}
	
	void SoundManager::saveConfig()
	{

	}
	
	void SoundManager::reloadConfig()
	{

	}
}
