/*!
 * \file GameMenu.cpp
 * \brief Gestionnaire du menu de jeu
 * \author Maxime GUIHAL
 */

#include "menu/GameMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	GameMenu::GameMenu() :
		title("Jouer", TITLEFONT, 100),
		create("Creer une partie", 250, CREATEGAMEMENU),
		join("Rejoindre une partie", 300, JOINGAMEMENU),
		back("Retour", 450, MAINMENU)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		title.setColor(skin->getColor(TITLECOLOR));

		create.setNext(&join);
		join.setNext(&back);
		join.setPrevious(&create);
		back.setPrevious(&join);

		create.setSelected(true);

		this->widgets.push_back(&title);
		this->widgets.push_back(&create);
		this->widgets.push_back(&join);
		this->widgets.push_back(&back);
	}

	void GameMenu::downPressed()
	{
		back.goNext();
		join.goNext();
		create.goNext();
	}

	void GameMenu::upPressed()
	{
		create.goPrevious();
		join.goPrevious();
		back.goPrevious();
	}

	void GameMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (create.getSelected())
			*nextScreen = create.activate();
			
		if (join.getSelected())
			*nextScreen = join.activate();
			
		if (back.getSelected())
			*nextScreen = back.activate();
	}

	void GameMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = back.activate();
	}
}

