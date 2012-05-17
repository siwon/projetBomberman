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
			std::vector<std::string> getSkinsList();

			sf::Image loadImage(EImage name);

			sf::Color getColor(EColorKey key);

			void setSkin(std::string name);

			std::string getSkin();

			void saveConfig();

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



