#ifndef _PAUSEMENU
#define _PAUSEMENU

/*!
 * \file PauseMenu.hpp
 * \brief Classe de gestion du menu pause
 * \author Maxime GUIHAL
 */

#include <SFML/System/Clock.hpp>

#include "INetworkToMenu.hpp"
#include "menu/IMenuScreen.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class PauseMenu
	 * \brief Classe de gestion du menu pause
	 */
	class PauseMenu : public IMenuScreen
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			PauseMenu();

			/*!
			 * \brief Destructeur
			 */
			~PauseMenu() {}

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
		
			/*!
			 * \see IMenuScreen::run
			 */
			EMenuScreen run(MainWindow& window, EMenuScreen);

		private:
			TextWidget title; /*!< Titre du menu */
			LinkWidget resume; /*!< Lien pour retourner à la partie */
			LinkWidget quit; /*!< Lien pour quitter le programme */
		
			sf::Clock clock; /*! Horloge pour empêcher les clics instantanés sur le menu */

			INetworkToMenu* network; /*!< Interface vers le composant réseau */
	};
}

#endif

