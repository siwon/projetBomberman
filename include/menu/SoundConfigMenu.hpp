#ifndef _SOUNDCONFIGMENU
#define _SOUNDCONFIGMENU

/*!
 * \file SoundConfigMenu.hpp
 * \brief Classe de gestion du menu de configuration audio
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"
#include "menu/SelectionWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class SoundConfigMenu
	 * \brief Classe de gestion du menu de configuration audio
	 */
	class SoundConfigMenu : public IMenuScreen
	{
		public:
			/*!
			 * Constructeur
			 */
			SoundConfigMenu();

			/*!
			 * Destructeur
			 */
			~SoundConfigMenu() {}

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
			 * \see IMenuScreen::run
			 */
			EMenuScreen run(MainWindow& window, EMenuScreen previous);

		private:
			TextWidget title;
			TextWidget soundText;
			TextWidget musicText;
			SelectionWidget soundVolume;
			SelectionWidget musicVolume;
			LinkWidget cancel;
			LinkWidget save;
	};
}

#endif

