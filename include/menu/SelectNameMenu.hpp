#ifndef _SELECTNAMEMENU
#define _SELECTNAMEMENU

/*!
 * \file SelectNameMenu.hpp
 * \brief Classe de gestion du menu de sélection des noms des joueurs
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "SGameConfig.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"
#include "menu/InputWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class SelectNameMenu
	 * \brief Classe de gestion du menu de sélection des noms des joueurs
	 */
	class SelectNameMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 */
			SelectNameMenu(SGameConfig* gameConfig);

			/*!
			 * Destructeur
			 */
			~SelectNameMenu();

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

			/*!
			 * \see IMenuScreen:loopAction
			 */			
			void loopAction();

		private:
			TextWidget title;

			TextWidget* nameTexts[4];
			InputWidget* names[4];
			
			LinkWidget cancel;
			LinkWidget next;

			SGameConfig* gameConfig;

			/*!
			 * \brief Méthode pour initialiser les widgets
			 */
			void initWidgets();
	};
}

#endif

