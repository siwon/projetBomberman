#ifndef _SCOREMENU
#define _SCOREMENU

/*!
 * \file ScoreMenu.hpp
 * \brief Classe de gestion du menu score
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"
#include "menu/SMenuConfig.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class ScoreMenu
	 * \brief Classe de gestion du menu score
	 */
	class ScoreMenu : public IMenuScreen
	{
		public:
			/*!
			 * \brief Constructeur
			 * \param menuConfig : Structure de configuration du menu
			 */
			ScoreMenu(SMenuConfig* menuConfig);

			/*!
			 * \brief Destructeur
			 */
			~ScoreMenu();

			/*!
			 * \see IMenuScreen::validPressed
			 */			
			void validPressed(EMenuScreen* nextScreen);
		
			/*!
			 * \see IMenuScreen::run
			 */
			EMenuScreen run(MainWindow& window, EMenuScreen previous);

		private:
			TextWidget title; /*!< Titre du menu */
			TextWidget winner; /*!< Texte indiquant le gagnant de la partie */

			ImageWidget* pictures[4]; /*!< Images des joueurs */
			TextWidget* names[4]; /*!< Noms et scores des joueurs */
			
			LinkWidget back; /*!< Lien pour retourner au menu principal */

			SMenuConfig* menuConfig; /*!< Structure de configuration du menu */

			/*!
			 * \brief Méthode pour initialiser les widgets du menu
			 */
			void initWidgets();
	};
}

#endif

