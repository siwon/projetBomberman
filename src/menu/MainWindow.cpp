/*!
 * \file MainWindow.cpp
 * \brief Fenêtre principale du programme
 * \author Maxime GUIHAL
 */

#include <iostream>

#include "menu/MainWindow.hpp"

#include "PolyBomberException.hpp"
#include "configFile/ConfigFileManager.hpp"

namespace PolyBomber
{
	MainWindow::MainWindow()
	{
		unsigned int style;
		sf::VideoMode settings = sf::VideoMode();
		this->initVideoMode(style, settings);

		try
		{
			/*IConfigFile* configFile = new ConfigFileManager();

			// On charge les paramètres du plein écran
			if (configFile->getIntValue("window.fullscreen.enabled"))
			{
				style = sf::Style::Fullscreen;
				settings.width = configFile->getIntValue("window.fullscreen.width");
				settings.height = configFile->getIntValue("window.fullscreen.height");
				settings.bitsPerPixel = configFile->getIntValue("window.fullscreen.bpp");
			}

			delete configFile;

			if (!settings.isValid())
				throw PolyBomberException("Mode video plein ecran incorrect");*/
		}
		catch (PolyBomberException& e)
		{
			std::cerr << "Erreur : " << e.what() << std::endl;
			this->initVideoMode(style, settings);
		}		

		sf::RenderWindow(settings, "PolyBomber", style);

		while(1)
		{
			sf::RenderWindow::display();
		}
	}

	MainWindow::~MainWindow()
	{}

	MainWindow& MainWindow::operator=(const MainWindow& obj)
	{
		return *this;
	}

	void MainWindow::initVideoMode(unsigned int& style, sf::VideoMode& mode)
	{
		style = sf::Style::Titlebar | sf::Style::Close;

		mode.width = 800;
		mode.height = 600;
		mode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
	}
}


