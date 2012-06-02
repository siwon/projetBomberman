#ifndef _SPLASHSCREEN
#define _SPLASHSCREEN

/*!
 * \file SplashScreen.hpp
 * \brief Classe de gestion de l'écran de démarrage
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

namespace PolyBomber
{
	/*!
	 * \class SplashScreen
	 * \brief Classe de gestion de l'écran de démarrage
	 */
	class SplashScreen : public IMenuScreen
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			SplashScreen();

			/*!
			 * \brief Destructeur
			 */
			~SplashScreen() {}

			/*!
			 * \see IMenuScreen::run
			 */
			EMenuScreen run(MainWindow& window, EMenuScreen previous);

		private:
			ImageWidget splash; /*!< Image de présentation */
			ImageWidget wiiScreen; /*!< Image pour brancher la Wii */
	};
}

#endif

