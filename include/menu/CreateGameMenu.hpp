#ifndef _CREATEGAMEMENU
#define _CREATEGAMEMENU

/*!
 * \file CreateGameMenu.hpp
 * \brief Classe de gestion du menu de création d'une partie
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"
#include "menu/SelectionWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class CreateGameMenu
	 * \brief Classe de gestion du menu de création d'une partie
	 */
	class CreateGameMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 */
			CreateGameMenu();

			/*!
			 * Destructeur
			 */
			~CreateGameMenu() {}

			/*!
			 * \see IMenuScreen::downPressed
			 */
			void downPressed();

			/*!
			 * \see IMenuScreen::upPressed
			 */
			void upPressed();

			/*!
			 * \see IMenuScreen::leftPressed
			 */
			void leftPressed();

			/*!
			 * \see IMenuScreen::rightPressed
			 */
			void rightPressed();

			/*!
			 * \see IMenuScreen::validPressed
			 */
			void validPressed(EMenuScreen* nextScreen);

			/*!
			 * \see IMenuScreen:backPressed
			 */
			void backPressed(EMenuScreen* nextScreen);

			/*!
			 * \see IMenuScreen::run
			 */
			EMenuScreen run(MainWindow& window, EMenuScreen previous);

		private:
			TextWidget title;
			TextWidget typeText;
			TextWidget playersText;

			SelectionWidget type;
			SelectionWidget players;

			LinkWidget options;
			
			LinkWidget cancel;
			LinkWidget next;
	};
}

#endif

