#ifndef _SKINMANAGER
#define _SKINMANAGER

/*!
 * \file SkinManager.hpp
 * \brief Classe de gestion du skin
 * \author Maxime GUIHAL
 */

#include "ISkin.hpp"
#include "TSingleton.hpp"

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
			 * \brief Récupération de la liste des skins disponibles
			 *
			 * Cette méthode liste les dossiers présents dans /resources/skins
			 *
			 * \return La liste des skins disponibles
			 */
			std::vector<std::string> getSkinsList();

			/*!
			 * \brief Récupère une image du skin selon son intitulé
			 * \param name : Intitulé de l'image
			 * \return Texture associée à l'image
			 */
			sf::Texture* loadImage(EImage name);

			/*!
			 * \brief Récupère un code couleur du skin
			 * \param key : intitulé de la couleur
			 * \return Couleur correspondant à l'intitulé
			 */
			sf::Color getColor(EColorKey key);

			/*!
			 * \brief Change le skin courant
			 * \param name : Nouveau skin
			 */
			void setSkin(std::string name);

			/*!
			 * \brief Récupère le skin courant
			 * \return Skin courant
			 */
			std::string getSkin();

			/*!
			 * \brief Sauvegarde le skin dans la configuration
			 */
			void saveConfig();

			/*!
			 * \brief Recharge le skin de la configuration
			 */
			void reloadConfig();

		private:
			/*!
			 * \brief Constructeur
			 */
			SkinManager();

			/*!
			 * \brief Destructeur
			 */
			~SkinManager();

			
	};
}

#endif



