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
			SplashScreen();
			~SplashScreen();
		
			EMenuScreen run(MainWindow& window, EMenuScreen previous);
	};
}

#endif

