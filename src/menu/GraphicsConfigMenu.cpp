/*!
 * \file GraphicsConfigMenu.cpp
 * \brief Gestionnaire du menu de configuration graphique
 * \author Maxime GUIHAL
 */

#include "menu/GraphicsConfigMenu.hpp"
#include "PolyBomberApp.hpp"
#include "configFile/ConfigFileManager.hpp"

namespace PolyBomber
{
	GraphicsConfigMenu::GraphicsConfigMenu() :
		title("Configuration graphique", TITLEFONT, 100),
		textFullscreen("Mode plein-ecran : ", TEXTFONT, 200),
		fullscreen(TEXTFONT, 200),
		noFullscreen("Indisponible", ERRORFONT, 200),
		skinText("Skin choisi :", TEXTFONT, 300),
		skinList(TEXTFONT, 350),
		cancel("Annuler", 450, CONFIGMENU),
		save("Valider", 450, CONFIGMENU)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));
		skinText.setColor(skin->getColor(TEXTCOLOR));		
		textFullscreen.setColor(skin->getColor(TEXTCOLOR));

		// Mode plein ecran
		textFullscreen.move(-100, 0);

		fullscreen.push_back("non");
		fullscreen.push_back("oui");
		fullscreen.move(100, 0);

		noFullscreen.setColor(skin->getColor(ERRORCOLOR));
		noFullscreen.move(100, 0);

		// Liste des skins
		std::vector<std::string> skins = skin->getSkinsList();
		unsigned int currentSkinIndex = 0;
		
		for (unsigned int i=0; i<skins.size(); i++)
		{
			skinList.push_back(skins[i]);
			if (skin->getSkin().compare(skins[i]) == 0)
				currentSkinIndex = i;
		}

		skinList.setCurrentItem(currentSkinIndex);

		cancel.move(-100, 0);
		save.move(100, 0);

		cancel.setSelected(true);
		
		fullscreen.setNext(&skinList);
		skinList.setNext(&cancel);
		
		cancel.setPrevious(&skinList);
		cancel.setNext(&save);
			
		save.setPrevious(&skinList);
		save.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&textFullscreen);
		this->widgets.push_back(&skinText);
		this->widgets.push_back(&skinList);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&save);

		this->window = NULL;
	}

	EMenuScreen GraphicsConfigMenu::run(MainWindow& window, EMenuScreen previous)
	{
		this->window = &window;

		fullscreen.setCurrentItem(window.getFullScreen());

		if (window.canFullScreen())
		{
			skinList.setPrevious(&fullscreen);
			this->widgets.push_back(&fullscreen);
		}
		else
			this->widgets.push_back(&noFullscreen);

		return IMenuScreen::run(window, previous);
	}

	void GraphicsConfigMenu::downPressed()
	{
		skinList.goNext();
		fullscreen.goNext();
	}

	void GraphicsConfigMenu::upPressed()
	{
		skinList.goPrevious();
		cancel.goPrevious();
		save.goPrevious();
	}

	void GraphicsConfigMenu::leftPressed()
	{
		ISkin* skin = PolyBomberApp::getISkin();
		std::vector<std::string> skins = skin->getSkinsList();

		save.goNext();
		fullscreen.goPreviousItem();
		skinList.goPreviousItem();
		skin->setSkin(skins[skinList.getCurrentItem()]);
	}

	void GraphicsConfigMenu::rightPressed()
	{
		ISkin* skin = PolyBomberApp::getISkin();
		std::vector<std::string> skins = skin->getSkinsList();

		cancel.goNext();
		fullscreen.goNextItem();
		skinList.goNextItem();
		skin->setSkin(skins[skinList.getCurrentItem()]);
	}

	void GraphicsConfigMenu::validPressed(EMenuScreen* nextScreen)
	{
		ISkin* skin = PolyBomberApp::getISkin();

		if (cancel.getSelected())
		{
			skin->reloadConfig();
			*nextScreen = cancel.activate();
		}
		
		if (save.getSelected())
		{
			if (window->canFullScreen())
			{
				window->setFullScreen(fullscreen.getCurrentItem());

				IConfigFile* configFile = new ConfigFileManager();

				configFile->setIntValue("window.fullscreen.enabled", fullscreen.getCurrentItem());

				delete configFile;
			}

			skin->saveConfig();							
			*nextScreen = save.activate();
		}
	}

	void GraphicsConfigMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}
}
