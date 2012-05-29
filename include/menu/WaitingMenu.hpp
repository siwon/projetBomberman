#ifndef _WAITINGMENU
#define _WAITINGMENU

/*!
 * \file WaitingMenu.hpp
 * \brief Classe de gestion du menu d'attente de début de partie
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"
#include "menu/SMenuConfig.hpp"

#include "INetworkToMenu.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class WaitingMenu
	 * \brief Classe de gestion du menu d'attente de début de partie
	 */
	class WaitingMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 */
			WaitingMenu(SMenuConfig* menuConfig);

			/*!
			 * Destructeur
			 */
			~WaitingMenu() {}

			/*!
			 * \see IMenuScreen::run
			 */
			EMenuScreen run(MainWindow& window, EMenuScreen previous);

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
			 * \see IMenuScreen::loopAction
			 */			
			void loopAction();

		private:
			TextWidget title;
			TextWidget ip;

			ImageWidget* pictures[4];
			TextWidget* names[4];
						
			LinkWidget cancel;
			LinkWidget start;

			SMenuConfig* menuConfig;

			INetworkToMenu* network; /*!< Lien vers le module réseau */

			/*!
			 * \brief Méthode pour initialiser les widgets
			 */
			void initWidgets();
	};
}

#endif

