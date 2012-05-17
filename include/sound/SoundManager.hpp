#ifndef _SOUNDMANAGER
#define _SOUNDMANAGER

/*!
 * \file SoundManager.hpp
 * \brief Classe de gestion du son
 * \author Maxime GUIHAL
 */

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

			unsigned int getSoundVolume();

			void setMusicVolume(unsigned int volume);

			unsigned int getMusicVolume();

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
	};
}

#endif


