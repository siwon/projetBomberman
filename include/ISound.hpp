#ifndef _ISOUND
#define _ISOUND

/*!
 * \file ISound.hpp
 * \brief Interface de sortie du composant Son
 * \author Maxime GUIHAL
 */

#include "ESound.hpp"
#include "EMusic.hpp"

namespace PolyBomber
{
	/*!
	 * \class ISound
	 * \brief Interface de sortie du composant Son
	 *
	 * Cette interface permet de lire les sons et les musiques du jeu
	 */
	class ISound
	{
		public:
			/*!
			 * \brief Lecture d'un son
			 *
			 * Si le libellé n'existe pas, une exception est lancée
			 * 
			 * \param sound Libellé du son
			 */
			virtual void playSound(ESound sound) = 0;

			/*!
			 * \brief Lecture d'une musique
			 *
			 * Si le libellé n'existe pas, une exception est lancée
			 * 
			 * \param music Libellé de la musique
			 */
			virtual void playMusic(EMusic music) = 0;

			/*!
			 * \brief Arrêt d'une musique
			 *
			 * Si le libellé n'existe pas, une exception est lancée
			 * 
			 * \param music Libellé de la musique
			 */
			virtual void stopMusic(EMusic music) = 0; 
		
			/*!
			 * \brief Modification du volume des sons 
			 * \param volume Nouveau volume
			 */
			virtual void setSoundVolume(unsigned int volume) = 0;

			/*!
			 * \brief Récupération du volume des sons
			 * \return Volume des sons
			 */
			virtual unsigned int getSoundVolume() = 0;

			/*!
			 * \brief Modification du volume des musiques 
			 * \param volume Nouveau volume
			 */
			virtual void setMusicVolume(unsigned int volume) = 0;

			/*!
			 * \brief Récupération du volume des musiques
			 * \return Volume des musiques
			 */
			virtual unsigned int getMusicVolume() = 0;

			/*!
			 * \brief Sauvegarde de la configuration
			 *
			 * Ecriture des paramètres son actuels dans le fichier de
			 * configuration
			 */
			virtual void saveConfig() = 0;

			/*!
			 * \brief Rechargement de la configuration
			 *
			 * En cas d'annulation des changements effectués,
			 * rechargement entier des paramètres du son.
			 */
			virtual void reloadConfig() = 0;
	};
}

#endif

