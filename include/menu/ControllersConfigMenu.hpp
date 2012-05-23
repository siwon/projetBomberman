#ifndef _CONTROLLERSCONFIGMENU
#define _CONTROLLERSCONFIGMENU

/*!
 * \file ControllersConfigMenu.hpp
 * \brief Classe de gestion du menu de configuration des contrôleurs
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"
#include "menu/SelectionWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class ControllersConfigMenu
	 * \brief Classe de gestion du menu de configuration des contrôleurs
	 */
	class ControllersConfigMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 */
			ControllersConfigMenu();

			/*!
			 * Destructeur
			 */
			~ControllersConfigMenu();

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
			TextWidget* playerText[4];
			SelectionWidget* playerController[4];
			LinkWidget cancel;
			LinkWidget save;

			/*!
			 * \brief Initialisation des contrôleurs
			 */
			void initControllers();
	};
}

#endif


