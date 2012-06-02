#ifndef _SOUNDMANAGER
#define _SOUNDMANAGER

/*!
 * \file SoundManager.hpp
 * \brief Classe de gestion du son
 * \author Maxime GUIHAL
 */

#include <map>
#include <string>

#include <SFML/Audio.hpp>

#include "ISound.hpp"
#include "TSingleton.hpp"

namespace PolyBomber
{
	/*!
	 * \class SoundManager
	 * \brief Classe de gestion du son
	 */
	class SoundManager : public ISound,
						        public Singleton<SoundManager>
	{
		friend class Singleton<SoundManager>;

		public:
			void playSound(ESound sound);

			void playMusic(EMusic music);

			void stopMusic(EMusic music); 
		
			void setSoundVolume(unsigned int volume);

			unsigned int getSoundVolume() {return this->soundVolume;}

			void setMusicVolume(unsigned int volume);

			unsigned int getMusicVolume() {return this->musicVolume;}

			void saveConfig();

			void reloadConfig();

		private:
			/*!
			 * \brief Constructeur
			 */
			SoundManager();

			/*!
			 * \brief Destructeur
			 */
			~SoundManager();

			unsigned int soundVolume; /*!< Volume des sons */
			unsigned int musicVolume; /*!< Volume des musiques */

			std::map<ESound, std::string> soundFiles; /*!< Fichiers associés aux sons */
			std::map<EMusic, std::string> musicFiles; /*!< Fichiers associés aux musiques */

			std::map<EMusic, sf::Music*> musicPlayers; /*!< Ressources pour les musiques */

			const std::string PATH; /*!< Chemin d'accès aux fichiers */
			
			sf::SoundBuffer* buffer;
			sf::Sound so;
	};
}

#endif


