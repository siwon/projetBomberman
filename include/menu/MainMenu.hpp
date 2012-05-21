#ifndef _MAINMENU
#define _MAINMENU

/*!
 * \file MainMenu.hpp
 * \brief Classe de gestion du menu principal
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class MainMenu
	 * \brief Classe de gestion du menu principal
	 */
	class MainMenu : public IMenuScreen
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			MainMenu();

			/*!
			 * \brief Destructeur
			 */
			~MainMenu() {}

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

		private:
			TextWidget title;
			LinkWidget play;
			LinkWidget options;
			LinkWidget quit;
			
	};
}

#endif

