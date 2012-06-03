/*!
 * \file GameOptionsMenu.cpp
 * \brief Gestionnaire du menu d'options d'une partie
 * \author Maxime GUIHAL
 */

#include "menu/GameOptionsMenu.hpp"
#include "PolyBomberApp.hpp"
#include "EImage.hpp"

namespace PolyBomber
{
	GameOptionsMenu::GameOptionsMenu(SMenuConfig* menuConfig) :
		title("Options de la partie", TITLEFONT, 30),
		category(TITLEFONT, 100),		
		cancel("Annuler", 550, CREATEGAMEMENU),
		save("Valider", 550, CREATEGAMEMENU),
		menuConfig(menuConfig)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));

		category.push_back("Bonus de bombe");
		category.push_back("Bonus de personnage");
		category.push_back("Infections");

		cancel.move(-100, 0);
		save.move(100, 0);

		cancel.setSelected(true);
		
		cancel.setNext(&save);			
		save.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&category);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&save);

		initBonus();
	}

	GameOptionsMenu::~GameOptionsMenu()
	{
		for (int i=0; i<18; i++)
		{
			delete this->images[i];
			delete this->bonus[i];
		}
	}

	void GameOptionsMenu::downPressed()
	{
		for (int i=17; i>=0; i--)
			this->bonus[i]->goNext();

		category.goNext();
	}

	void GameOptionsMenu::upPressed()
	{
		for (int i=0; i<18; i++)
			this->bonus[i]->goPrevious();

		cancel.goPrevious();
		save.goPrevious();
	}

	void GameOptionsMenu::leftPressed()
	{
		for (int i=0; i<18; i++)
			this->bonus[i]->goPreviousItem();

		category.goPreviousItem();
		save.goNext();
		setCategory();
	}

	void GameOptionsMenu::rightPressed()
	{
		for (int i=0; i<18; i++)
			this->bonus[i]->goNextItem();

		category.goNextItem();
		cancel.goNext();
		setCategory();
	}

	void GameOptionsMenu::validPressed(EMenuScreen* nextScreen)
	{
		if (cancel.getSelected())
		{
			reloadBonus();
			*nextScreen = cancel.activate();
		}
		
		if (save.getSelected())
		{						
			for (int i=0; i<18; i++)
				this->menuConfig->gameConfig.nbBonus[i] = this->bonus[i]->getCurrentItem();

			*nextScreen = save.activate();
		}
	}

	void GameOptionsMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}

	EMenuScreen GameOptionsMenu::run(MainWindow& window, EMenuScreen previous)
	{
		reloadBonus();
		return IMenuScreen::run(window, previous);
	}

	void GameOptionsMenu::initBonus()
	{				
		ISkin* skin = PolyBomberApp::getISkin();

		EImage icones[18] = {EIMAGE_BOMBPLUS, EIMAGE_BOMBMOINS, EIMAGE_RANGEPLUS, EIMAGE_RANGEMOINS,
							EIMAGE_RANGEMAX, EIMAGE_MINEBONUS, EIMAGE_INFINITY, EIMAGE_ATOMIC,
							EIMAGE_VITESSEPLUS, EIMAGE_VITESSEMOINS, EIMAGE_BOMBLINE, EIMAGE_REMOTEBONUS,
							EIMAGE_CRANE, EIMAGE_HELL, EIMAGE_CONFUSION,	EIMAGE_SPASME,	EIMAGE_DILATATION,
							EIMAGE_RAGE};
		int i;
		
		for (i=0; i<18; i++)
		{
			int j = i;
			if (i >= 12) j -= 12;
			else if (i >= 8) j -= 8;

			this->images[i] = new ImageWidget();
			this->images[i]->setImage(skin->loadImage(icones[i]));
			this->images[i]->setPosition(300,200+40*j);			
			
			this->bonus[i] = new SelectionWidget(TEXTFONT, 200 + 40*j);
			this->bonus[i]->push_back("0");
			this->bonus[i]->push_back("1");
			this->bonus[i]->push_back("2");
			this->bonus[i]->push_back("3");
			this->bonus[i]->push_back("4");
			this->bonus[i]->push_back("5");
			this->bonus[i]->push_back("6");
			this->bonus[i]->push_back("7");
			this->bonus[i]->push_back("8");
			this->bonus[i]->push_back("9");
			this->bonus[i]->push_back("10");
			this->bonus[i]->setCurrentItem(this->menuConfig->gameConfig.nbBonus[i]);
			this->bonus[i]->move(70, 0);

			if (j > 0)
				this->bonus[i]->setPrevious(this->bonus[i-1]);
			else
				this->bonus[i]->setPrevious(&category);
			
			this->widgets.push_back(this->images[i]);
			this->widgets.push_back(this->bonus[i]);
		}

		for (i=0; i<7; i++)
			this->bonus[i]->setNext(this->bonus[i+1]);

		for (i=8; i<11; i++)
			this->bonus[i]->setNext(this->bonus[i+1]);

		for (i=12; i<17; i++)
			this->bonus[i]->setNext(this->bonus[i+1]);

		this->bonus[7]->setNext(&cancel);						
		this->bonus[11]->setNext(&cancel);						
		this->bonus[17]->setNext(&cancel);

		setCategory();				
	}

	void GameOptionsMenu::setCategory()
	{
		unsigned int category = this->category.getCurrentItem();

		for (int i=0; i<18; i++)
		{
			if (category == 0)
			{
				this->images[i]->setVisible(i < 8);
				this->bonus[i]->setVisible(i < 8);
				this->category.setNext(this->bonus[0]);
				this->cancel.setPrevious(this->bonus[7]);
				this->save.setPrevious(this->bonus[7]);
			}
			else if (category == 1)
			{
				this->images[i]->setVisible(i >= 8 && i < 12);
				this->bonus[i]->setVisible(i >= 8 && i < 12);
				this->category.setNext(this->bonus[8]);
				this->cancel.setPrevious(this->bonus[11]);
				this->save.setPrevious(this->bonus[11]);
			}
			else
			{
				this->images[i]->setVisible(i >= 12);
				this->bonus[i]->setVisible(i >= 12);
				this->category.setNext(this->bonus[12]);
				this->cancel.setPrevious(this->bonus[17]);
				this->save.setPrevious(this->bonus[17]);
			}			
		}
	}

	void GameOptionsMenu::reloadBonus()
	{
		for (int i=0; i<18; i++)
			this->bonus[i]->setCurrentItem(this->menuConfig->gameConfig.nbBonus[i]);
	}
}
