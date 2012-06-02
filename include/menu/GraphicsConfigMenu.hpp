#ifndef _GRAPHICSCONFIGMENU
#define _GRAPHICSCONFIGMENU

/*!
 * \file GraphicsConfigMenu.hpp
 * \brief Classe de gestion de configuration graphique
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"
#include "menu/SelectionWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class GraphicsConfigMenu
	 * \brief Classe de gestion de configuration graphique
	 */
	class GraphicsConfigMenu : public IMenuScreen
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			GraphicsConfigMenu();

			/*!
			 * \brief Destructeur
			 */
			~GraphicsConfigMenu() {}

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
			TextWidget textFullscreen; /*!< Texte pour le plein ecran */
			SelectionWidget fullscreen; /*!< Widget de sélection du mode plein ecran */
			TextWidget noFullscreen; /*!< Texte indiquant que le mode plein ecran est indisponible */
			TextWidget skinText; /*!< Texte pour sélectionner le skin */
			SelectionWidget skinList; /*!< Widget de sélection des skins */
			LinkWidget cancel; /*!< Lien pour annuler et revenir au menu de configuration */
			LinkWidget save; /*!< Lien pour valider et revenir au menu de configuration */

			MainWindow* window; /*!< Pointeur vers la fenêtre du programme */
	};
}

#endif

