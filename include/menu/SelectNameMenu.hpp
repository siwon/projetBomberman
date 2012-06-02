#ifndef _SELECTNAMEMENU
#define _SELECTNAMEMENU

/*!
 * \file SelectNameMenu.hpp
 * \brief Classe de gestion du menu de sélection des noms des joueurs
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"
#include "menu/SMenuConfig.hpp"

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
			 * \param menuConfig : Structure de configuration du menu
			 */
			SelectNameMenu(SMenuConfig* menuConfig);

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
			 * \see IMenuScreen::backPressed
			 */
			void backPressed(EMenuScreen* nextScreen);

			/*!
			 * \see IMenuScreen::loopAction
			 */			
			void loopAction(EMenuScreen*);

		private:
			TextWidget title; /*!< Titre du menu */
			TextWidget error; /*!< Message d'erreur */

			TextWidget* nameTexts[4]; /*!< Textes des noms des joueurs */
			InputWidget* names[4]; /*!< Zones de saisie des noms */
			
			LinkWidget cancel; /*!< Lien pour annuler et revenir au menu de jeu */
			LinkWidget next; /*!< Lien pour valider et aller au menu d'attente */

			SMenuConfig* menuConfig; /*!< Structure de configuration des menus */

			/*!
			 * \brief Méthode pour initialiser les widgets
			 */
			void initWidgets();
	};
}

#endif

