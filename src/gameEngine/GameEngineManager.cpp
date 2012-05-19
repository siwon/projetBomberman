/*!
 * \file GameEngineManager.cpp
 * \brief Implementation de la classe GameEngineManager
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers

#include "gameEngine/GameEngineManager.hpp"

namespace PolyBomber {
	
	GameEngineManager::GameEngineManager() : IGameEngineToNetwork(), IGameEngineToGameInterface(), INetworkToGameEngine() {
		this->board=Board();
		this->gameConfigIsSet=false;
	}
	
	GameEngineManager::GameEngineManager(const GameEngineManager& b) : IGameEngineToNetwork(), IGameEngineToGameInterface(), INetworkToGameEngine() {
		this->board=Board();
		this->gameConfigIsSet=false;
	}
	
	GameEngineManager::~GameEngineManager() {
		this->board.~Board();
	}
	
	//IGameEngineToNetwork
	void GameEngineManager::setGameConfig(SGameConfig gameConfig) {
		
	}
	
	//IGameEngineToGameInterface
	SBoard GameEngineManager::getBoard() {
		return this->board.boardToSBoard();
	}
	
	int GameEngineManager::isFinished() {
		int toReturn=0;
		
		return toReturn;
	}
}