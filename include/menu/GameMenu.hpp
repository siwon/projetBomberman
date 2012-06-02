#ifndef _GAMEMENU
#define _GAMEMENU

/*!
 * \file GameMenu.hpp
 * \brief Classe de gestion du menu de jeu
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class GameMenu
	 * \brief Classe de gestion du menu de jeu
	 */
	class GameMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 */
			GameMenu();

			/*!
			 * Destructeur
			 */
			~GameMenu() {}

			/*!
			 * \see IMenuScreen:downPressed
			 */
			void downPressed();

			/*!
			 * \see IMenuScreen:upPressed
			 */
			void upPressed();

			/*!
			 * \see IMenuScreen:validPressed
			 */
			void validPressed(EMenuScreen* nextScreen);

			/*!
			 * \see IMenuScreen:backPressed
			 */
			void backPressed(EMenuScreen* nextScreen);

		private:
			TextWidget title; /*!< Titre du menu */
			LinkWidget create; /*!< Lien pour créer une partie */
			LinkWidget join; /*!< Lien pour rejoindre une partie */
			LinkWidget back; /*!< Lien pour retourner au menu principal */
	};
}

#endif

