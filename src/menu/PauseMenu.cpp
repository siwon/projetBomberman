/*!
 * \file PauseMenu.cpp
 * \brief Gestionnaire du menu pause
 * \author Maxime GUIHAL
 */

#include "menu/PauseMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	PauseMenu::PauseMenu() :
		title("Pause", TITLEFONT, 100),
		resume("Reprendre la partie", 250, RUNGAME),		
		quit("Quitter la partie", 350, EXIT)
	{
		ISkin* skin = PolyBomberApp::getISkin();

		title.setColor(skin->getColor(TITLECOLOR));

		resume.setNext(&quit);
		quit.setPrevious(&resume);

		resume.setSelected(true);

		this->widgets.push_back(&title);
		this->widgets.push_back(&resume);
		this->widgets.push_back(&quit);
	}

	void PauseMenu::downPressed()
	{
		resume.goNext();
	}

	void PauseMenu::upPressed()
	{
		quit.goPrevious();
	}

	void PauseMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (this->clock.getElapsedTime().asMilliseconds() > 250)
		{
			if (resume.getSelected())
				*nextScreen = resume.activate();
			
			if (quit.getSelected())
				*nextScreen = quit.activate();
		}
	}
	
	EMenuScreen PauseMenu::run(MainWindow& window, EMenuScreen previous)
	{
		this->clock.restart();
		return IMenuScreen::run(window, previous);
	}
}
