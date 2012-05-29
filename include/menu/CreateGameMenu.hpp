#ifndef _CREATEGAMEMENU
#define _CREATEGAMEMENU

/*!
 * \file CreateGameMenu.hpp
 * \brief Classe de gestion du menu de création d'une partie
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"
#include "menu/SMenuConfig.hpp"

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
			 * \param menuConfig : Structure de configuration des parties
			 */
			CreateGameMenu(SMenuConfig* menuConfig);

			/*!
			 * Destructeur
			 */
			~CreateGameMenu() {}

			/*!
			 * \see IMenuScreen::run
			 */
			EMenuScreen run(MainWindow& window, EMenuScreen previous);

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

		private:
			TextWidget title;
			TextWidget typeText;
			TextWidget playersText;

			SelectionWidget type;
			SelectionWidget players;

			LinkWidget options;
			
			LinkWidget cancel;
			LinkWidget next;

			SMenuConfig* menuConfig;

			/*!
			 * \brief Méthode pour initialiser les widgets
			 */
			void initWidgets();
	};
}

#endif

