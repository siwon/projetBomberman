/*!
 * \file GameEngineManager.cpp
 * \brief Implementation de la classe GameEngineManager
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	
	void GameEngineManager::generateWall() {
		for (int i=0; i<19; i++) {
			for (int j=0; j<13; j++) {
				if (i%2==1 && j%2==1) {
					board.addWall(Wall(Board::caseToPixel(i),Board::caseToPixel(j)));
				}
			}
		}
	}
	
	//IGameEngineToNetwork
	void GameEngineManager::setGameConfig(SGameConfig gameConfig) {
		int nbPlayer = gameConfig.nbPlayers;
		int nbBonusTemp;
		int x=0;
		int y=0;
		
		//generation des joueurs
		switch (nbPlayer) {
			case 2:
				board.addPlayer(Player(Board::caseToPixel(0),Board::caseToPixel(0),0));
				board.addPlayer(Player(Board::caseToPixel(18),Board::caseToPixel(12),1));
				break;
				
			case 3:
				board.addPlayer(Player(Board::caseToPixel(0),Board::caseToPixel(0),0));
				board.addPlayer(Player(Board::caseToPixel(18),Board::caseToPixel(0),1));
				board.addPlayer(Player(Board::caseToPixel(9),Board::caseToPixel(12),2));
				break;
				
			case 4:
				board.addPlayer(Player(Board::caseToPixel(0),Board::caseToPixel(0),0));
				board.addPlayer(Player(Board::caseToPixel(18),Board::caseToPixel(0),1));
				board.addPlayer(Player(Board::caseToPixel(18),Board::caseToPixel(12),2));
				board.addPlayer(Player(Board::caseToPixel(0),Board::caseToPixel(12),3));
				break;
				
			default:
				break;
		}
		
		//generation des murs
		generateWall();
		
		//generation des bonus
		for (int i=0;i<17;i++) {
			nbBonusTemp = gameConfig.nbBonus[i];
			for (int j=0; j<nbBonusTemp; j++) {
				while (!board.caseIsFreeInitialisation(Board::caseToPixel(x),Board::caseToPixel(y))) {
					x=rand()%18;
					y=rand()%13;
				}
				board.addBonus(Bonus(Board::caseToPixel(x),Board::caseToPixel(y),Board::intToEGameBonus(i),false));
				board.addBox(Box(Board::caseToPixel(x),Board::caseToPixel(y),true));
			}
		}
		
		//generation des caisses
		for (int i=0;i<NOMBREBOX;i++) {
			while (!board.caseIsFreeInitialisation(Board::caseToPixel(x),Board::caseToPixel(y))) {
				x=rand()%18;
				y=rand()%13;
			}
			board.addBox(Box(Board::caseToPixel(x),Board::caseToPixel(y),false));
		}
		
	}
	
	void GameEngineManager::run() {
		
	}
	
	//IGameEngineToGameInterface
	SBoard GameEngineManager::getBoard() {
		return this->board.boardToSBoard();
	}
	
	int GameEngineManager::isFinished() {
		return board.getIdSurvivant();
	}
}