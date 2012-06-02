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
			 * \param menuConfig : Structure de configuration du menu
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

		private:
			TextWidget title; /*!< Titre du menu */
			TextWidget ip; /*!< Adresse IP s'affichant pour le serveur */

			ImageWidget* pictures[4]; /*!< Images des 4 joueurs */
			TextWidget* names[4]; /*!< Noms des 4 joueurs */
						
			LinkWidget cancel; /*!< Lien pour annuler vers le menu de jeu */
			LinkWidget start; /*!< Lien pour le serveur, pour commencer la partie */

			SMenuConfig* menuConfig; /*!< Structure de configuration du menu */

			INetworkToMenu* network; /*!< Lien vers le module réseau */

			/*!
			 * \brief Méthode pour initialiser les widgets
			 */
			void initWidgets();

			/*!
			 * \brief Méthode pour mettre à jour les noms
			 */
			void update();
	};
}

#endif

