#ifndef _KEYASSIGNMENU
#define _KEYASSIGNMENU

/*!
 * \file KeyAssignMenu.hpp
 * \brief Classe de gestion du menu d'assignation des touches
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "menu/MainWindow.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"
#include "menu/SelectionWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class KeyAssignMenu
	 * \brief Classe de gestion du menu d'assignation des touches
	 */
	class KeyAssignMenu : public IMenuScreen
	{
		public:
			/*!
			 * \brief Constructeur
			 * \param player : Numéro du joueur (1-4)
			 */
			KeyAssignMenu(unsigned int player);

			/*!
			 * \brief Destructeur
			 */
			~KeyAssignMenu();

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
			TextWidget subtitle; /*!< Sous-titre indiquant le joueur */
			TextWidget errorKey; /*!< Message d'erreur */
			TextWidget* actionText[7]; /*!< Texte des actions */
			LinkWidget* keyText[7]; /*!< Texte cliquable des touches */
			LinkWidget cancel; /*!< Lien pour annuler et retourner au menu de configuration des contrôleurs */
			LinkWidget save; /*!< Lien pour valider et retourner au menu de configuration des contrôleurs */

			unsigned int player; /*!< Numéro du joueur */

			MainWindow* window; /*! Fenêtre du programme */

			/*!
			 * \brief Initialisation des touches
			 */
			void initKeys();
	};
}

#endif


