#ifndef _SELECTSLOTSMENU
#define _SELECTSLOTSMENU

/*!
 * \file SelectSlotsMenu.hpp
 * \brief Classe de gestion du menu pour rejoindre une partie
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"
#include "menu/SMenuConfig.hpp"

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
			 * \param menuConfig : Structure de configuration des parties
			 */
			SelectSlotsMenu(SMenuConfig* menuConfig);

			/*!
			 * Destructeur
			 */
			~SelectSlotsMenu() {}

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

			/*!
			 * \see IMenuScreen:loopAction
			 */			
			void loopAction(EMenuScreen* nextScreen);

		private:
			TextWidget title;
			TextWidget error;
			
			TextWidget nbPlayersText;
			SelectionWidget nbPlayers;
						
			LinkWidget cancel;
			LinkWidget next;

			SMenuConfig* menuConfig;

			INetworkToMenu* network; /*!< Lien vers le module réseau */
			bool error;
	};
}

#endif

