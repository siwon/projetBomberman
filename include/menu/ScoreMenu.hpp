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
			 */
			ScoreMenu(SMenuConfig* menuConfig);

			/*!
			 * \brief Destructeur
			 */
			~ScoreMenu() {}

			/*!
			 * \see IMenuScreen::validPressed
			 */			
			void validPressed(EMenuScreen* nextScreen);
		
			/*!
			 * \see IMenuScreen::run
			 */
			EMenuScreen run(MainWindow& window, EMenuScreen previous);

		private:
			TextWidget title;
			//TextWidget winner;

			ImageWidget* pictures[4];
			TextWidget* names[4];
			
			LinkWidget back;

			SMenuConfig* menuConfig;

			void initWidgets();
	};
}

#endif

