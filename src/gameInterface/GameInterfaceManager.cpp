/*!
 * \file GameInterfaceManager.cpp
 * \brief Gestionnaire de l'interface graphique du plateau
 * \author Maxime GUIHAL
 */

#include <SFML/Graphics.hpp>

#include "gameInterface/GameInterfaceManager.hpp"
#include "PolyBomberApp.hpp"

#define ORIGX 68
#define ORIGY 72
#define CASEPX 35

namespace PolyBomber
{
	GameInterfaceManager::GameInterfaceManager()
	{
		ISkin* skin = PolyBomberApp::getISkin();

		this->background.setTexture(*skin->loadImage(GAME_BACKGROUND));
	}

	GameInterfaceManager::~GameInterfaceManager()
	{}

	EScreenSignal GameInterfaceManager::run(sf::RenderWindow* window, unsigned int score[4], int& winner)
	{		
		INetworkToGameInterface* network = PolyBomberApp::getINetworkToGameInterface();

		while (window->isOpen() && !network->isPaused())
		{			
			sf::Event event;
			while (window->pollEvent(event))
				if (event.type == sf::Event::Closed) window->close();

  			window->clear();

  			update();
  			
			window->draw(this->background);

			unsigned int i;

			for (i=0; i<this->boxes.size(); i++)		window->draw(this->boxes[i]);
			for (i=0; i<this->players.size(); i++)		window->draw(this->players[i]);
			for (i=0; i<this->bonus.size(); i++)		window->draw(this->bonus[i]);
			for (i=0; i<this->explosives.size(); i++)	window->draw(this->explosives[i]);
			for (i=0; i<this->flames.size(); i++)		window->draw(this->flames[i]);

			window->display();
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
				sf::IntRect rect(0, 0, 35, 35);

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
			EImage image = (EImage)(EIMAGE_FLAME_UP);

			sf::Sprite flame(*skin->loadImage(image));
			flame.setPosition(ORIGX + CASEPX * (*itFlames).coords.x, ORIGY + CASEPX * (*itFlames).coords.y);
			this->flames.push_back(flame);
		}		
	}
}

