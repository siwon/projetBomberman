#ifndef _CONFIGMENU
#define _CONFIGMENU

/*!
 * \file ConfigMenu.hpp
 * \brief Classe de gestion du menu de configuration
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class GameMenu
	 * \brief Classe de gestion du menu de configuration
	 */
	class ConfigMenu : public IMenuScreen
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			ConfigMenu();

			/*!
			 * \brief Destructeur
			 */
			~ConfigMenu() {}
		
			/*!
			 * \see IMenuScreen::downPressed
			 */
			void downPressed();

			/*!
			 * \see IMenuScreen::upPressed
			 */
			void upPressed();

			/*!
			 * \see IMenuScreen::validPressed
			 */
			void validPressed(EMenuScreen* nextScreen);

			/*!
			 * \see IMenuScreen::backPressed
			 */
			void backPressed(EMenuScreen* nextScreen);

		private:
			TextWidget title; /*!< Titre du menu */
			LinkWidget keys; /*! Lien vers le menu de configuration des contrôleurs */		
			LinkWidget audio; /*!< Lien vers le menu de configuration audio */		
			LinkWidget graphics; /*!< Lien vers le menu de configuration graphique */		
			LinkWidget back; /*!< Lien pour revenir au menu précédent */
	};
}

#endif

