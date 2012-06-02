/*!
 * \file ScoreMenu.cpp
 * \brief Gestionnaire du menu score
 * \author Maxime GUIHAL
 */

#include "menu/ScoreMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	ScoreMenu::ScoreMenu(SMenuConfig* menuConfig) :
		title("Score de la partie", TITLEFONT, 100),
		back("Retour au menu", 500, MAINMENU),
		menuConfig(menuConfig)
	{
		ISkin* skin = PolyBomberApp::getISkin();

		title.setColor(skin->getColor(TITLECOLOR));

		back.setSelected(true);

		this->widgets.push_back(&title);
		this->widgets.push_back(&back);
	}

	void ScoreMenu::validPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = back.activate();
	}
	
	EMenuScreen ScoreMenu::run(MainWindow& window, EMenuScreen previous)
	{
		initWidgets();
		return IMenuScreen::run(window, previous);
	}

	void ScoreMenu::initWidgets()
	{
		
	}
}
