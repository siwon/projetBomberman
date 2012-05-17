#ifndef _MAINWINDOW
#define _MAINWINDOW

/*!
 * \file MainWindow.hpp
 * \brief Classe de la fenêtre du programme
 * \author Maxime GUIHAL
 */

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"

#include "menu/MainWindow.hpp"

namespace PolyBomber
{
	/*!
	 * \class MainWindow
	 * \brief Classe de la fenêtre du programme
	 */
	class MainWindow : public sf::RenderWindow
	{
		public:
			MainWindow();
			~MainWindow();
			MainWindow& operator=(const MainWindow& obj);

		private:
			void initVideoMode(unsigned int& style, sf::VideoMode& mode);
	};
}

#endif


