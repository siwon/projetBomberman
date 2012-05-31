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
		while (window->isOpen())
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

		for (itBoxes=board.boxes.begin(); itBoxes!=board.boxes.end(); itBoxes++)
		{
			sf::Sprite box(*skin->loadImage(EIMAGE_BOX));
			box.setPosition(ORIGX + CASEPX * (*itBoxes).x, ORIGY + CASEPX * (*itBoxes).y);
			this->boxes.push_back(box);
		}

		for (itPlayers=board.players.begin(); itPlayers!=board.players.end(); itPlayers++)
		{
			sf::Sprite player(*skin->loadImage(EIMAGE_PLAYER1LEFT));
			player.setPosition(ORIGX + CASEPX * (*itPlayers).coords.x, ORIGY + CASEPX * (*itPlayers).coords.y);
			this->boxes.push_back(player);
		}

		for (itBonus=board.bonus.begin(); itBonus!=board.bonus.end(); itBonus++)
		{
			EImage image = (EImage)(SPEEDUP + (*itBonus).type);
			sf::Sprite bonus(*skin->loadImage(image));
			bonus.setPosition(ORIGX + CASEPX * (*itBonus).coords.x, ORIGY + CASEPX * (*itBonus).coords.y);
			this->boxes.push_back(bonus);
		}

		for (itExplosives=board.explosives.begin(); itExplosives!=board.explosives.end(); itExplosives++)
		{
			EImage image = (EImage)(EXPLOSIVE_MINE + (*itExplosives).type);
			sf::Sprite explosive(*skin->loadImage(image));
			explosive.setPosition(ORIGX + CASEPX * (*itExplosives).coords.x, ORIGY + CASEPX * (*itExplosives).coords.y);
			this->boxes.push_back(explosive);
		}
	}
}

