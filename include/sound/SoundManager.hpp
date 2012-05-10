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
			// TODO - A compléter

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


