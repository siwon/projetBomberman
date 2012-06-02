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
			TextWidget title; /*!< Titre du menu */
			TextWidget error; /*!< Message d'erreur */
			TextWidget* playerText[4]; /*!< Noms des joueurs */
			SelectionWidget* playerController[4]; /*!< Widget de sélection du contrôleur */
			LinkWidget cancel; /*!< Lien pour retourner au menu précédent */

			/*!
			 * \brief Initialisation des contrôleurs
			 */
			void initControllers();

			/*!
			 * \brief Changement d'un contrôleur
			 * \param next : True si on sélectionne le contrôleur suivant
			 */
			void changeController(bool next);
	};
}

#endif


