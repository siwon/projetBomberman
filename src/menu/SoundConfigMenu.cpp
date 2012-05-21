/*!
 * \file SoundConfigMenu.cpp
 * \brief Gestionnaire du menu de configuration audio
 * \author Maxime GUIHAL
 */

#include "menu/SoundConfigMenu.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	SoundConfigMenu::SoundConfigMenu() :
		title("Configuration audio", TITLEFONT, 100),
		soundText("Volume des bruitages : ", TEXTFONT, 200),
		musicText("Volume de la musique : ", TEXTFONT, 300),
		soundVolume(TEXTFONT, 250),
		musicVolume(TEXTFONT, 350),
		cancel("Annuler", 450, CONFIGMENU),
		save("Valider", 450, CONFIGMENU)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		title.setColor(skin->getColor(TITLECOLOR));
		soundText.setColor(skin->getColor(TEXTCOLOR));		
		musicText.setColor(skin->getColor(TEXTCOLOR));

		soundVolume.push_back("Muet");
		musicVolume.push_back("Muet");
		soundVolume.push_back("10%");
		musicVolume.push_back("10%");
		soundVolume.push_back("20%");
		musicVolume.push_back("20%");
		soundVolume.push_back("30%");
		musicVolume.push_back("30%");
		soundVolume.push_back("40%");
		musicVolume.push_back("40%");
		soundVolume.push_back("50%");
		musicVolume.push_back("50%");
		soundVolume.push_back("60%");
		musicVolume.push_back("60%");
		soundVolume.push_back("70%");
		musicVolume.push_back("70%");
		soundVolume.push_back("80%");
		musicVolume.push_back("80%");
		soundVolume.push_back("90%");
		musicVolume.push_back("90%");
		soundVolume.push_back("100%");
		musicVolume.push_back("100%");

		cancel.move(-100, 0);
		save.move(100, 0);

		cancel.setSelected(true);
		
		soundVolume.setNext(&musicVolume);
		musicVolume.setPrevious(&soundVolume);
		musicVolume.setNext(&cancel);
		
		cancel.setPrevious(&musicVolume);
		cancel.setNext(&save);
			
		save.setPrevious(&musicVolume);
		save.setNext(&cancel);

		this->widgets.push_back(&title);
		this->widgets.push_back(&soundText);
		this->widgets.push_back(&musicText);
		this->widgets.push_back(&soundVolume);
		this->widgets.push_back(&musicVolume);
		this->widgets.push_back(&cancel);
		this->widgets.push_back(&save);
	}

	void SoundConfigMenu::downPressed()
	{
		musicVolume.goNext();
		soundVolume.goNext();
	}

	void SoundConfigMenu::upPressed()
	{
		musicVolume.goPrevious();
		cancel.goPrevious();
		save.goPrevious();
	}

	void SoundConfigMenu::leftPressed()
	{
		ISound* sound = PolyBomberApp::getISound();

		save.goNext();
		soundVolume.goPreviousItem();
		musicVolume.goPreviousItem();

		sound->setSoundVolume(soundVolume.getCurrentItem()*10);
		sound->setMusicVolume(musicVolume.getCurrentItem()*10);
	}

	void SoundConfigMenu::rightPressed()
	{
		ISound* sound = PolyBomberApp::getISound();

		cancel.goNext();
		soundVolume.goNextItem();
		musicVolume.goNextItem();

		sound->setSoundVolume(soundVolume.getCurrentItem()*10);
		sound->setMusicVolume(musicVolume.getCurrentItem()*10);
	}

	void SoundConfigMenu::validPressed(EMenuScreen* nextScreen)
	{
		ISound* sound = PolyBomberApp::getISound();

		if (cancel.getSelected())
		{
			sound->reloadConfig();
			*nextScreen = cancel.activate();
		}
		
		if (save.getSelected())
		{						
			sound->saveConfig();
			*nextScreen = save.activate();
		}
	}

	void SoundConfigMenu::backPressed(EMenuScreen* nextScreen)
	{
		*nextScreen = cancel.activate();
	}

	EMenuScreen SoundConfigMenu::run(MainWindow& window, EMenuScreen previous)
	{
		ISound* sound = PolyBomberApp::getISound();

		soundVolume.setCurrentItem(sound->getSoundVolume()/10);
		musicVolume.setCurrentItem(sound->getMusicVolume()/10);
		IMenuScreen::run(window, previous);
	}
}
