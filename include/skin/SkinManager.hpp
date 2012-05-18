#ifndef _SKINMANAGER
#define _SKINMANAGER

/*!
 * \file SkinManager.hpp
 * \brief Classe de gestion du skin
 * \author Maxime GUIHAL
 */

#include <map>

#include "PolyBomberException.hpp"

#include "ISkin.hpp"
#include "TSingleton.hpp"
#include "IConfigFile.hpp"

namespace PolyBomber
{
	/*!
	 * \class SkinManager
	 * \brief Classe de gestion du skin du jeu
	 */
	class SkinManager : public ISkin,
						       public Singleton<SkinManager>
	{
		friend class Singleton<SkinManager>;

		public:
			/*!
			 * \see ISkin::getSkinsList
			 */
			std::vector<std::string> getSkinsList() const;

			/*!
			 * \see ISkin::loadImage
			 */
			sf::Texture* loadImage(EImage name);

			/*!
			 * \see ISkin::getColor
			 */
			sf::Color getColor(EColorKey key);

			/*!
			 * \see ISkin::setSkin
			 */
			void setSkin(std::string name);

			/*!
			 * \see ISkin::getSkin
			 */
			std::string getSkin() throw(PolyBomberException);

			/*!
			 * \see ISkin::saveConfig
			 */
			void saveConfig();

			/*!
			 * \see ISkin::reloadConfig
			 */
			void reloadConfig() throw(PolyBomberException);

		private:
			/*!
			 * \brief Constructeur
			 */
			SkinManager() throw(PolyBomberException);

			/*!
			 * \brief Destructeur
			 */
			~SkinManager();

			/*!
			 * \brief Méthode pour supprimer toutes les textures
			 */
			void destroyTextures();

			/*!
			 * \brief Méthode pour créer et insérer une texture
			 * \param key : Clé associée à la texture
			 */
			void insertTexture(EImage key);

			/*!
			 * \brief Méthode pour recharger les textures chargées
			 */
			void reloadTextures();

			void getComponent(IConfigFile* configFile, EColorKey key, sf::Uint8& component, std::string suffix);

			std::string folder; /*!< Dossier du skin */
			std::map<EImage, std::string> files; /*!< Fichiers associés */
			std::map<EImage, sf::Texture*> textures; /*!< Textures associées */
			std::map<EColorKey, std::string> colors; /*!< Intitulés associés aux couleurs */

			const std::string PATH; /*!< Chemin des skins */
	};
}

#endif



