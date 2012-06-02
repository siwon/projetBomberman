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
			 * \param menuConfig : Structure de configuration du menu
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
			void loopAction(EMenuScreen*);

		private:
			TextWidget title; /*!< Titre du menu */
			TextWidget error; /*!< Message d'erreur */
			
			TextWidget ipText; /*!< Label pour la zone de texte */
			InputWidget ipInput; /*!< Zone de texte pour rentrer l'adresse IP du serveur */
						
			LinkWidget cancel; /*!< Lien pour annuler et retourner au menu de jeu */
			LinkWidget next; /*!< Lien pour valider et sélectionner le nombre de joueurs locaux */

			SMenuConfig* menuConfig; /*!< Structure de configuration du menu */
	};
}

#endif

