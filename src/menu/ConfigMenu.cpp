/*!
 * \file ConfigMenu.cpp
 * \brief Gestionnaire du menu de jeu
 * \author Maxime GUIHAL
 */

#include "menu/ConfigMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	ConfigMenu::ConfigMenu() :
		title("Configuration", TITLEFONT, 100),
		keys("Controles", 250, CONTROLLERSCONFIGMENU),	
		audio("Audio", 300, SOUNDCONFIGMENU),
		graphics("Graphisme", 350, GRAPHICSCONFIGMENU),		
		back("Retour", 450, MAINMENU)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		title.setColor(skin->getColor(TITLECOLOR));

		keys.setNext(&audio);
		audio.setNext(&graphics);
		graphics.setNext(&back);
		audio.setPrevious(&keys);
		graphics.setPrevious(&audio);
		back.setPrevious(&graphics);

		keys.setSelected(true);

		this->widgets.push_back(&title);
		this->widgets.push_back(&keys);
		this->widgets.push_back(&audio);
		this->widgets.push_back(&graphics);
		this->widgets.push_back(&back);
	}

	void ConfigMenu::downPressed()
	{
		back.goNext();
		graphics.goNext();
		audio.goNext();
		keys.goNext();
	}

	void ConfigMenu::upPressed()
	{
		keys.goPrevious();
		audio.goPrevious();
		graphics.goPrevious();
		back.goPrevious();
	}

	void ConfigMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (keys.getSelected())
			*nextScreen = keys.activate();
			
		if (audio.getSelected())
			*nextScreen = audio.activate();
			
		if (graphics.getSelected())
			*nextScreen = graphics.activate();
			
		if (back.getSelected())
			*nextScreen = back.activate();
	}

	void ConfigMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = back.activate();
	}
}

