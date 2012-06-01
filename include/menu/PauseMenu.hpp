#ifndef _PAUSEMENU
#define _PAUSEMENU

/*!
 * \file PauseMenu.hpp
 * \brief Classe de gestion du menu pause
 * \author Maxime GUIHAL
 */

#include <SFML/Clock.hpp>

#include "menu/IMenuScreen.hpp"

#include "menu/ImageWidget.hpp"
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

		private:
			TextWidget title;
			LinkWidget resume;
			LinkWidget quit;
		
			sf::Clock clock; 
			
	};
}

#endif

