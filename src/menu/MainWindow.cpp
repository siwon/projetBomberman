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
	sf::RenderWindow MainWindow::window;

	MainWindow::MainWindow() : fullscreen(false)
	{
		IConfigFile* configFile = new ConfigFileManager();

		try
		{
			if (configFile->getIntValue("window.fullscreen.enabled"))
				this->fullscreen = true;
		}
		catch (PolyBomberException& e)
		{
			std::cerr << e.what() << std::endl;
		}

		delete configFile;
			
		initWindow();
	}

	MainWindow::~MainWindow()
	{}

	MainWindow::MainWindow(const MainWindow& obj) : fullscreen(obj.fullscreen)
	{
		initWindow();
	}

	MainWindow& MainWindow::operator=(const MainWindow& obj)
	{
		if (this->fullscreen != obj.fullscreen)
		{
			this->fullscreen = obj.fullscreen;
			initWindow();
		}
		return *this;
	}

	void MainWindow::initWindow()
	{
		unsigned int style = sf::Style::Titlebar | sf::Style::Close;
		sf::VideoMode settings(800, 600, sf::VideoMode::getDesktopMode().bitsPerPixel);

		if (this->fullscreen)
			style = sf::Style::Fullscreen;

		MainWindow::window.create(settings, "PolyBomber", style);
		MainWindow::window.setMouseCursorVisible(false);
		MainWindow::window.setFramerateLimit(60);
	}

	bool MainWindow::isOpen()
	{
		return window.isOpen();
	}

	void MainWindow::clear()
	{
		MainWindow::window.clear();
	}	

	void MainWindow::display(std::vector<sf::Drawable*> widgets)
	{
		std::vector<sf::Drawable*>::iterator it;
		
		for (it = widgets.begin(); it < widgets.end(); it++)
			MainWindow::window.draw(**it);

		MainWindow::window.display();
	}

	void MainWindow::setFullScreen(bool fullscreen)
	{
		if (this->fullscreen != fullscreen)
		{
			this->fullscreen = fullscreen;
			initWindow();			
		}
		this->fullscreen = fullscreen;
	}

	bool MainWindow::canFullScreen()
	{
		sf::VideoMode settings(800, 600, sf::VideoMode::getDesktopMode().bitsPerPixel);
		return settings.isValid();
	}
}


