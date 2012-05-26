#ifndef _SELECTSLOTSMENU
#define _SELECTSLOTSMENU

/*!
 * \file SelectSlotsMenu.hpp
 * \brief Classe de gestion du menu pour rejoindre une partie
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "INetworkToMenu.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"
#include "menu/SelectionWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class SelectSlotsMenu
	 * \brief Classe de gestion du menu pour rejoindre une partie
	 */
	class SelectSlotsMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 */
			SelectSlotsMenu();

			/*!
			 * Destructeur
			 */
			~SelectSlotsMenu() {}

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
			
			TextWidget nbPlayersText;
			SelectionWidget nbPlayers;
						
			LinkWidget cancel;
			LinkWidget next;

			INetworkToMenu* network; /*!< Lien vers le module réseau */
	};
}

#endif

