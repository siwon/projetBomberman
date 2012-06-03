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
	 *
	 * Ce menu permet de sélectionner le nombre de joueurs sur l'ordinateur courant
	 */
	class SelectSlotsMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 * \param menuConfig : Structure de configuration du menu
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
			void loopAction(EMenuScreen*);

		private:
			TextWidget title; /*!< Titre du menu */
			TextWidget error; /*!< Message d'erreur */
			
			TextWidget nbPlayersText; /*!< Texte du nombre de joueurs locaux */
			SelectionWidget nbPlayers; /*!< Widget de sélection du nombre de joueurs */
						
			LinkWidget cancel; /*!< Lien pour annuler et revenir au menu de jeu */
			LinkWidget next; /*!< Lien pour valider et sélectionner les noms des joueurs */

			SMenuConfig* menuConfig;/*!< Structure de configuration du menu */

			INetworkToMenu* network; /*!< Lien vers le module réseau */
	};
}

#endif

