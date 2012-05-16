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
	MainWindow::MainWindow() : window()
	{
		this->settings = sf::VideoMode();
		this->initVideoMode(this->style, this->settings);

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

		this->window.create(this->settings, "PolyBomber", this->style);
		this->window.setMouseCursorVisible(false);
	}

	MainWindow::~MainWindow()
	{}

	MainWindow::MainWindow(const MainWindow& obj) : window()
	{
		this->window.create(obj.getSettings(), "PolyBomber", obj.getStyle());
	}

	MainWindow& MainWindow::operator=(const MainWindow& obj)
	{
		this->window.create(obj.getSettings(), "PolyBomber", obj.getStyle());
		return *this;
	}

	void MainWindow::initVideoMode(unsigned int& style, sf::VideoMode& mode)
	{
		style = sf::Style::Titlebar | sf::Style::Close;

		mode.width = 800;
		mode.height = 600;
		mode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
	}

	unsigned int MainWindow::getStyle() const 
	{
		return this->style;
	}

	sf::VideoMode MainWindow::getSettings() const
	{
		return this->settings;
	}
}


