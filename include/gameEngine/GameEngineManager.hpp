#ifndef GAME_ENGINE_MANAGER_HEADER
#define GAME_ENGINE_MANAGER_HEADER

/*!
 * \file GameEngineManager.hpp
 * \brief Classe de gestion du moteur de jeu
 * \author Simon Rousseau
 */

#include "gameEngine/Board.hpp"

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
		
	private:
		void generateWall();
		
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
