/*!
 * \file ScoreMenu.cpp
 * \brief Gestionnaire du menu score
 * \author Maxime GUIHAL
 */

#include <sstream>

#include "menu/ScoreMenu.hpp"
#include "PolyBomberApp.hpp"

#include "menu/ImageWidget.hpp"
#include "menu/TextWidget.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	ScoreMenu::ScoreMenu(SMenuConfig* menuConfig) :
		title("Score de la partie", TITLEFONT, 100),
		winner("Le joueur i a gagne !", TEXTFONT, 170),
		back("Retour au menu", 550, MAINMENU),
		menuConfig(menuConfig)
	{
		ISkin* skin = PolyBomberApp::getISkin();

		title.setColor(skin->getColor(TITLECOLOR));
		winner.setColor(skin->getColor(TEXTCOLOR));

		back.setSelected(true);

		this->widgets.push_back(&title);
		this->widgets.push_back(&winner);
		this->widgets.push_back(&back);

		for (int i=0; i<4; i++)
		{
			this->pictures[i] = new ImageWidget();
			this->pictures[i]->setPosition(300, 250 + 60*i);				
			this->pictures[i]->setImage(skin->loadImage((EImage)(PLAYER1 + i)));				

			this->names[i] = new TextWidget("", TEXTFONT, 250 + 60*i);
			this->names[i]->setColor(skin->getColor(TEXTCOLOR));

			this->widgets.push_back(this->pictures[i]);
			this->widgets.push_back(this->names[i]);
		}
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
		if (menuConfig->winner == -1)
			winner.setString("    Match nul !      ");
		else
		{
			std::ostringstream text;
			text << menuConfig->gameConfig.playersName[menuConfig->winner-1] << " a gagne !";
			winner.setString(text.str());
		}

		for (unsigned int i=0; i<4; i++)
		{
			this->pictures[i]->setVisible(i < menuConfig->gameConfig.nbPlayers);
			this->names[i]->setVisible(i < menuConfig->gameConfig.nbPlayers);

			std::ostringstream score;
			score << menuConfig->gameConfig.playersName[i] << " : " << menuConfig->scores[i] << " points";
			this->names[i]->setString(score.str());
		}


		

		for (int i=0; i<4; i++)
		{
			std::cout << "Joueur " << i << " : " << this->menuConfig->gameConfig.playersName[i] << std::endl;
		}
	}
}
