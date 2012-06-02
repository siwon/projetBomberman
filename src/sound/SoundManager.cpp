/*!
 * \file SoundManager.cpp
 * \brief Gestionnaire de son
 * \author Maxime GUIHAL
 */

#include "sound/SoundManager.hpp"
#include "configFile/ConfigFileManager.hpp"

#include "PolyBomberException.hpp"

#include <iostream>

namespace PolyBomber
{
	SoundManager::SoundManager() :
		PATH("resources/audio/")
	{
		// Initialisation des listes de fichiers
		this->soundFiles[CLICKSOUND] = this->PATH + "click.wav";
		this->soundFiles[SPLASHSOUND] = this->PATH + "explosion.ogg";
		this->soundFiles[PAUSESOUND] = this->PATH + "pauseExtract.ogg";
		this->musicFiles[PAUSEMUSIC] = this->PATH + "pause.ogg";
		
		buffer =  new sf::SoundBuffer();
		reloadConfig();
	}

	SoundManager::~SoundManager()
	{
		std::map<EMusic, sf::Music*>::iterator it;

		for (it=this->musicPlayers.begin(); it!=this->musicPlayers.end(); it++)
			delete (*it).second;
			
		delete buffer;
	}

	void SoundManager::playSound(ESound sound)
	{
		try
		{
			if(buffer != NULL)
				delete buffer;
				
			buffer = new sf::SoundBuffer();
			
			buffer->loadFromFile(this->soundFiles[sound]);
			
			so.setBuffer(*buffer);
			so.setVolume(this->soundVolume);
			so.play();
		}
		catch (...) {}
	}
	
	void SoundManager::playMusic(EMusic music)
	{
		try
		{
			this->musicPlayers[music] = new sf::Music();

			this->musicPlayers[music]->openFromFile(this->musicFiles[music]);
			this->musicPlayers[music]->setVolume(this->musicVolume);
			this->musicPlayers[music]->setLoop(true);
			this->musicPlayers[music]->play();
		}
		catch (...) {}
	}
	
	void SoundManager::stopMusic(EMusic music) 
	{
		try
		{
			this->musicPlayers[music]->stop();
		}
		catch (...) {}
	}
	
	void SoundManager::setSoundVolume(unsigned int volume)
	{
		if (volume <= 100)
			this->soundVolume = volume;
		this->playSound(CLICKSOUND);
	}
	
	void SoundManager::setMusicVolume(unsigned int volume)
	{
		if (volume <= 100)
			this->musicVolume = volume;
			
		unsigned int tmpVol = this->soundVolume;
		this->soundVolume = this->musicVolume;
		this->playSound(PAUSESOUND);
		this->soundVolume = tmpVol;
	}
	
	void SoundManager::saveConfig()
	{
		IConfigFile* configFile = new ConfigFileManager();

		configFile->setIntValue("audio.sound", this->soundVolume);
		configFile->setIntValue("audio.music", this->musicVolume);

		delete configFile;
	}
	
	void SoundManager::reloadConfig()
	{
		IConfigFile* configFile = new ConfigFileManager();

		this->soundVolume = 50;
		this->musicVolume = 50;

		try
		{
			this->soundVolume = configFile->getIntValue("audio.sound");
			this->musicVolume = configFile->getIntValue("audio.music");
		}
		catch (PolyBomberException& e)
		{}

		delete configFile;
	}
}
