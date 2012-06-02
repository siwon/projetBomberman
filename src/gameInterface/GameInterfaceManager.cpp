/*!
 * \file GameInterfaceManager.cpp
 * \brief Gestionnaire de l'interface graphique du plateau
 * \author Maxime GUIHAL
 */

#include "gameInterface/GameInterfaceManager.hpp"
#include "PolyBomberApp.hpp"

#include "EColorKey.hpp"

#define ORIGX 68
#define ORIGY 72
#define CASEPX 35

namespace PolyBomber
{
	GameInterfaceManager::GameInterfaceManager()
	{
		ISkin* skin = PolyBomberApp::getISkin();

		this->background.setTexture(*skin->loadImage(GAME_BACKGROUND));

		// Chargement de la police pour le texte
		if (!this->font.loadFromFile("resources/fonts/normal.ttf"))
			throw PolyBomberException("Impossible de charger la police du GameInterface");

		this->finishText.setFont(this->font);
		this->finishText.setCharacterSize(30);
		this->finishText.setColor(skin->getColor(TEXTCOLOR));
		this->finishText.setString("Partie terminee");
	}

	EScreenSignal GameInterfaceManager::run(sf::RenderWindow* window, unsigned int score[4], int& winner)
	{		
		INetworkToGameInterface* network = PolyBomberApp::getINetworkToGameInterface();
		IMenuToGameInterface* menu = PolyBomberApp::getIMenuToGameInterface();
		ISound* music = PolyBomberApp::getISound();
		
		int pause = 0;
		bool running = true;

		// On cache le texte de fin
		this->finishText.setPosition(320, -550);

		while (running && window->isOpen()) 
		{
			sf::Event event;
			while (window->pollEvent(event))
				if (event.type == sf::Event::Closed) window->close();

			// On teste la fin du jeu
			winner = network->isFinished();
		
			if (winner != 0)
			{
				running = false;
				this->finishText.setPosition(320, 550);
			}

  			window->clear();

  			update();

  			// On dessine les sprites
			window->draw(this->background);
			window->draw(this->finishText);
			
			unsigned int i;

			for (i=0; i<this->boxes.size(); i++)		window->draw(this->boxes[i]);
			for (i=0; i<this->players.size(); i++)		window->draw(this->players[i]);
			for (i=0; i<this->bonus.size(); i++)		window->draw(this->bonus[i]);
			for (i=0; i<this->explosives.size(); i++)	window->draw(this->explosives[i]);
			for (i=0; i<this->flames.size(); i++)		window->draw(this->flames[i]);

			window->display();

			// Gestion de la pause
			if ((pause = network->isPaused()) != 0)
			{
				music->playMusic(PAUSEMUSIC);
				EScreenSignal signal = menu->runPause(pause);
				music->stopMusic(PAUSEMUSIC);
				if (signal == EXITGAME || signal == EXITERROR)
					running = false;
			}

			sf::sleep(sf::milliseconds(50));
		}

		if (winner != 0)
		{
			score[winner-1]++;
			sf::sleep(sf::seconds(5));
		}

		return EXITGAME;
	}

	void GameInterfaceManager::update()
	{
		INetworkToGameInterface* network = PolyBomberApp::getINetworkToGameInterface();
		ISkin* skin = PolyBomberApp::getISkin();

		SBoard board = network->getBoard();
		
		std::vector<sf::Vector2<int> >::iterator itBoxes;
		std::vector<SPlayer>::iterator itPlayers;
		std::vector<SBonus>::iterator itBonus;
		std::vector<SExplosive>::iterator itExplosives;
		std::vector<SFlame>::iterator itFlames;

		this->boxes.clear();
		this->players.clear();
		this->bonus.clear();
		this->explosives.clear();
		this->flames.clear();

		// Caisses
		for (itBoxes=board.boxes.begin(); itBoxes!=board.boxes.end(); itBoxes++)
		{
			sf::Sprite box(*skin->loadImage(EIMAGE_BOX));
			box.setPosition(ORIGX + CASEPX * (*itBoxes).x, ORIGY + CASEPX * (*itBoxes).y);
			this->boxes.push_back(box);
		}

		// Joueurs
		for (itPlayers=board.players.begin(); itPlayers!=board.players.end(); itPlayers++)
		{
			if ((*itPlayers).state == ALIVE)
			{
				sf::IntRect rect(((*itPlayers).step % 8)*35, 0, 35, 35);

				EImage image = (EImage)((EIMAGE_PLAYER1UP + (*itPlayers).number*4) + (*itPlayers).orientation);
				
				sf::Sprite player(*skin->loadImage(image), rect);
				player.setPosition(ORIGX + (*itPlayers).coords.x, ORIGY + (*itPlayers).coords.y);
				this->players.push_back(player);
			}
		}

		// Bonus
		for (itBonus=board.bonus.begin(); itBonus!=board.bonus.end(); itBonus++)
		{
			EImage image = (EImage)(EIMAGE_VITESSEPLUS + (*itBonus).type);
			sf::Sprite bonus(*skin->loadImage(image));
			bonus.setPosition(ORIGX + CASEPX * (*itBonus).coords.x, ORIGY + CASEPX * (*itBonus).coords.y);
			this->bonus.push_back(bonus);
		}

		// Bombes
		for (itExplosives=board.explosives.begin(); itExplosives!=board.explosives.end(); itExplosives++)
		{
			EImage image = (EImage)(EIMAGE_MINE + (*itExplosives).type);
			sf::Sprite explosive(*skin->loadImage(image));
			explosive.setPosition(ORIGX + CASEPX * (*itExplosives).coords.x, ORIGY + CASEPX * (*itExplosives).coords.y);
			this->explosives.push_back(explosive);
		}

		// Flammes
		for (itFlames=board.flames.begin(); itFlames!=board.flames.end(); itFlames++)
		{
			EImage image;
			if ((*itFlames).location == ORIGIN)
				image = EIMAGE_FLAME_ORIG;
			else if ((*itFlames).location == MIDDLE)
			{
				if ((*itFlames).orientation == ORIENTATION_DOWN || (*itFlames).orientation == ORIENTATION_UP)
					image = EIMAGE_FLAME_V;
				else
					image = EIMAGE_FLAME_H;
			}
			else
				image = (EImage)(EIMAGE_FLAME_UP + (*itFlames).orientation);

			sf::Sprite flame(*skin->loadImage(image));
			flame.setPosition(ORIGX + CASEPX * (*itFlames).coords.x, ORIGY + CASEPX * (*itFlames).coords.y);
			this->flames.push_back(flame);
		}		
	}
}

