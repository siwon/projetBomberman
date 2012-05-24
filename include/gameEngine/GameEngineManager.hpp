#ifndef GAME_ENGINE_MANAGER_HEADER
#define GAME_ENGINE_MANAGER_HEADER

/*!
 * \file GameEngineManager.hpp
 * \brief Classe de gestion du moteur de jeu
 * \author Simon Rousseau
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gameEngine/Board.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "IGameEngineToNetwork.hpp"
#include "IGameEngineToGameInterface.hpp"
#include "INetworkToGameEngine.hpp"

#include "gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class ControllerManager
	 * \brief Classe de gestion du moteur de jeu
	 */
	class GameEngineManager : public IGameEngineToNetwork, public INetworkToGameEngine {
		// TODO : faire en sorte que ce soit un singleton !!!
	protected:
		Board board; /*! Objet stockant le plateau de jeu */
		bool gameConfigIsSet;
		sf::Clock horloge;
		int debutPause;
		
	private:
		//generation de la map
		void generateWall();
		void generatePlayer(int nbPlayer);
		void generateBox();
		void generateFlame(int x, int y, int range, int date);
		
		//decalageHoraire
		void decalageHoraire(int secondes);
		
    public:
		GameEngineManager();
		GameEngineManager(const GameEngineManager& b);
		//operateur d affectation
		~GameEngineManager();
		
		//IGameEngineToNetwork
		void setGameConfig(SGameConfig gameConfig);
		void run();
		
		//IGameEngineToGameInterface
		SBoard getBoard();
		int isFinished();
		
		//INetworkToGameEngine
		SKeyPressed getKeysPressed();
		int isPaused();
		
	};
}

#endif
