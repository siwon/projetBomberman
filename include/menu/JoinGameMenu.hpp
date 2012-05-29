#ifndef _JOINGAMEMENU
#define _JOINGAMEMENU

/*!
 * \file JoinGameMenu.hpp
 * \brief Classe de gestion du menu pour rejoindre une partie
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
	 * \class JoinGameMenu
	 * \brief Classe de gestion du menu pour rejoindre une partie
	 */
	class JoinGameMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 * \param menuConfig : Structure de configuration des parties
			 */
			JoinGameMenu(SMenuConfig* menuConfig);

			/*!
			 * Destructeur
			 */
			~JoinGameMenu() {}

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
			TextWidget error;
			
			TextWidget ipText;
			InputWidget ipInput;
						
			LinkWidget cancel;
			LinkWidget next;

			SMenuConfig* menuConfig;
	};
}

#endif

