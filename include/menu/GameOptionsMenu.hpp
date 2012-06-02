#ifndef _GAMEOPTIONSMENU
#define _GAMEOPTIONSMENU

/*!
 * \file GameOptionsMenu.hpp
 * \brief Classe de gestion du menu d'options d'une partie
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
	 * \class GameOptionsMenu
	 * \brief Classe de gestion du menu d'options d'une partie
	 */
	class GameOptionsMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 * \param menuConfig : Structure de configuration du menu
			 */
			GameOptionsMenu(SMenuConfig* menuConfig);

			/*!
			 * Destructeur
			 */
			~GameOptionsMenu();

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
			TextWidget title; /*!< Titre du menu */
			SelectionWidget category; /*!< Widget de sélection de la catégorie */

			ImageWidget* images[18]; /*!< Images des bonus */
			SelectionWidget* bonus[18]; /*!< Widget de sélection du nombre de bonus */
						
			LinkWidget cancel; /*!< Lien pour annuler */
			LinkWidget save; /*!< Lien pour valider */

			SMenuConfig* menuConfig; /*!< Structure de configuration du menu */

			/*!
			 * \brief Procédure d'initialisation des bonus
			 */
			void initBonus();

			/*!
			 * \brief Procédure pour changer de catégorie
			 */
			void setCategory();

			/*!
			 * \brief Procédure pour recharger le nombre de bonus
			 */
			void reloadBonus();
	};
}

#endif

