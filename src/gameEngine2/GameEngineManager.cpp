/*!
 * \file GameEngineManager.cpp
 * \brief Implementation de la classe GameEngineManager
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <vector>

// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>

// Bibliotheques externes


// Headers

#include "gameEngine/DefineAndFunction.hpp"
#include "gameEngine/Board.hpp"
#include "gameEngine/Bonus.hpp"
#include "gameEngine/Player.hpp"
#include "gameEngine/GameEngineManager.hpp"
#include "IGameEngineToNetwork.hpp"
#include "IGameEngineToGameInterface.hpp"
#include "INetworkToGameEngine.hpp"
#include "SBoard.hpp"
#include "SGameConfig.hpp"

using namespace PolyBomber;

GameEngineManager::GameEngineManager() {
	this->board=Board();
	this->gameConfigIsSet=false;
}

GameEngineManager::GameEngineManager(const GameEngineManager& b) : IGameEngineToNetwork(), IGameEngineToGameInterface(), INetworkToGameEngine() {
	this->board=b.getTheBoard();
	this->gameConfigIsSet=b.getGameConfigIsSet();
}

GameEngineManager::~GameEngineManager() {
	this->board.~Board();
}
/*
void GameEngineManager::applyBonus(Bonus bonus, Player player) {
	//TODO : a faire
}

void GameEngineManager::movePlayer(Player player, EOrientation orientation) {
	//TODO : a faire
}

void GameEngineManager::activateDetonator(Player player) {
	//TODO : a faire
}

void GameEngineManager::putMine(Player player) {
	if (player.getCapacity()) {
		player.decreaseCapacity();
		//this.board.add(new );
		// TODO : a terminer
	}
}

SBoard IGameEngineToGameInterface::getBoard() {
	SBoard toReturn;
	
	// TODO : a terminer
	
	return toReturn;
}

bool GameEngineManager::isFinished() {
	int nbSurvivant;
	bool toReturn;
	
	// TODO : a terminer
	
	return toReturn;
}

void GameEngineManager::setGameConfig(SGameConfig gameConfig) {
	unsigned int nbPlayers = gameConfig.nbPlayers;
	unsigned int nbBonus[17];
	
	for (int i=0; i<17; i++) {
		nbBonus[i]=gameConfig.nbBonus[i];
	}
	
	this->setGameConfigIsSet(true);
}

void GameEngineManager::run() {
	if (this->gameConfigIsSet) {
		//fonctionnement normal
	} else {
		//erreur : la partie n a pas etee parametree
	}
}*/