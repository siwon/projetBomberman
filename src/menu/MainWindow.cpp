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

		IConfigFile* configFile = new ConfigFileManager();

		try
		{
			// On charge les paramètres du plein écran
			if (configFile->getIntValue("window.fullscreen.enabled"))
			{
				this->style = sf::Style::Fullscreen;
				this->settings.width = configFile->getIntValue("window.fullscreen.width");
				this->settings.height = configFile->getIntValue("window.fullscreen.height");
				this->settings.bitsPerPixel = configFile->getIntValue("window.fullscreen.bpp");
			}

			if (!this->settings.isValid())
				throw PolyBomberException("Mode video plein ecran incorrect");
		}
		catch (PolyBomberException& e)
		{
			std::cerr << e.what() << std::endl;
			this->initVideoMode(this->style, this->settings);
		}

		delete configFile;
			
		initWindow(this->style, this->settings);
	}

	MainWindow::~MainWindow()
	{}

	MainWindow::MainWindow(const MainWindow& obj) : window()
	{
		initWindow(obj.getStyle(), obj.getSettings());
	}

	MainWindow& MainWindow::operator=(const MainWindow& obj)
	{
		initWindow(obj.getStyle(), obj.getSettings());
		return *this;
	}

	void MainWindow::initVideoMode(unsigned int& style, sf::VideoMode& mode)
	{
		style = sf::Style::Titlebar | sf::Style::Close;

		mode.width = 800;
		mode.height = 600;
		mode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
	}

	void MainWindow::initWindow(unsigned int style, sf::VideoMode settings)
	{
		this->window.create(settings, "PolyBomber", style);
		this->window.setMouseCursorVisible(false);
		this->window.setFramerateLimit(60);
	}

	unsigned int MainWindow::getStyle() const 
	{
		return this->style;
	}

	sf::VideoMode MainWindow::getSettings() const
	{
		return this->settings;
	}

	bool MainWindow::listenCloseButton()
	{
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return true;
		}

		return false;
	}

	void MainWindow::clear()
	{
		this->window.clear();
	}

	void MainWindow::draw(sf::Sprite s)
	{
		this->window.draw(s);
	}	

	void MainWindow::display(std::vector<IWidgetMenu*> widgets)
	{
		std::vector<IWidgetMenu*>::iterator it;
		
		for (it = widgets.begin(); it < widgets.end(); it++)
			this->window.draw(**it);

		this->window.display();
	}
}


