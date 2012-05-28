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

			window->display();
		}

		return EXITGAME;
	}

	void GameInterfaceManager::update()
	{
		INetworkToGameInterface* network = PolyBomberApp::getINetworkToGameInterface();
		ISkin* skin = PolyBomberApp::getISkin();

		SBoard board = network->getBoard();
		std::vector<sf::Vector2<int> >::iterator it;

		this->boxes.clear();

		for (it=board.boxes.begin(); it!=board.boxes.end(); it++)
		{
			sf::Sprite box(*skin->loadImage(BOX));
			box.setPosition(ORIGX + CASEPX * (*it).x, ORIGY + CASEPX * (*it).y);
			this->boxes.push_back(box);
		}
	}
}

