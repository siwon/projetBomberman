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
	
	GameEngineManager::GameEngineManager() : IGameEngineToNetwork(), INetworkToGameEngine() {
		this->board=Board();
		this->gameConfigIsSet=false;
		this->horloge=sf::Clock();
		this->debutPause=0;
	}
	
	GameEngineManager::GameEngineManager(const GameEngineManager& b) : IGameEngineToNetwork(), INetworkToGameEngine() {
		this->board=Board();
		this->gameConfigIsSet=false;
		this->horloge=sf::Clock();
		this->debutPause=0;
	}
	
	GameEngineManager::~GameEngineManager() {
		this->board.~Board();
		this->horloge.~Clock();
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
	
	void GameEngineManager::generatePlayer(int nbPlayer) {
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
	}
	
	void GameEngineManager::generateBox() {
		int x=0;
		int y=0;
		for (int i=0;i<NOMBREBOX;i++) {
			while (!board.caseIsFreeInitialisation(Board::caseToPixel(x),Board::caseToPixel(y))) {
				x=rand()%18;
				y=rand()%13;
			}
			board.addBox(Box(Board::caseToPixel(x),Board::caseToPixel(y),false));
		}
	}
	
	void GameEngineManager::generateFlame(int origineX, int origineY, int range, int date) {
		board.addFlame(Flame(Board::caseToPixel(origineX),Board::caseToPixel(origineY),ORIENTATION_UP,ORIGIN,date));
		int x;
		int y;
		
		//propagation vers la droite
		x=origineX+1;
		y=origineY;
		while (!board.isAWallInThisCase(x,y) && x-origineX<range && x<18) { 
			board.addFlame(Flame(Board::caseToPixel(x),Board::caseToPixel(y),ORIENTATION_RIGHT,MIDDLE,date));
			x=x+1;
		}
		if (x==origineX+range && !board.isAWallInThisCase(x,y) && x<18) {
			board.addFlame(Flame(Board::caseToPixel(x),Board::caseToPixel(y),ORIENTATION_RIGHT,END,date));
		}
		
		//propagation vers la gauche
		x=origineX-1;
		y=origineY;
		while (!board.isAWallInThisCase(x,y) && origineX-x<range && x>0) { 
			board.addFlame(Flame(Board::caseToPixel(x),Board::caseToPixel(y),ORIENTATION_LEFT,MIDDLE,date));
			x=x-1;
		}
		if (x==origineX-range && !board.isAWallInThisCase(x,y) && x>0) {
			board.addFlame(Flame(Board::caseToPixel(x),Board::caseToPixel(y),ORIENTATION_LEFT,END,date));
		}
		
		//propagation vers le haut
		x=origineX;
		y=origineY-1;
		while (!board.isAWallInThisCase(x,y) && origineY-y<range && y>0) {
			board.addFlame(Flame(Board::caseToPixel(x),Board::caseToPixel(y),ORIENTATION_UP,MIDDLE,date));
			y=y-1;
		}
		if (y==origineY-range && !board.isAWallInThisCase(x,y) && y>0) {
			board.addFlame(Flame(Board::caseToPixel(x),Board::caseToPixel(y),ORIENTATION_UP,END,date));
		}
		
		//propagation vers le bas
		x=origineX;
		y=origineY+1;
		while (!board.isAWallInThisCase(x,y) && y-origineY<range && y<13) {
			board.addFlame(Flame(Board::caseToPixel(x),Board::caseToPixel(y),ORIENTATION_DOWN,MIDDLE,date));
			y=y+1;
		}
		if (y==origineY+range && !board.isAWallInThisCase(x,y) && y<13) {
			board.addFlame(Flame(Board::caseToPixel(x),Board::caseToPixel(y),ORIENTATION_DOWN,END,date));
		}
	}
	
	void GameEngineManager::actionToucheHaut(int player) {
		// TODO : a faire
	}
	
	void GameEngineManager::actionToucheBas(int player) {
		// TODO : a faire
	}
	
	void GameEngineManager::actionToucheGauche(int player) {
		// TODO : a faire
	}
	
	void GameEngineManager::actionToucheDroite(int player) {
		// TODO : a faire
	}
	
	void GameEngineManager::actionToucheAction1(int player) {
		// TODO : a faire
	}
	
	void GameEngineManager::actionToucheAction2(int player) {
		// TODO : a faire
	}
	
	void GameEngineManager::decalageHoraire(int secondes) {
		this->board.effectuerDecalage(secondes);
	}
	
	//IGameEngineToNetwork
	void GameEngineManager::setGameConfig(SGameConfig gameConfig) {
		int nbPlayer = gameConfig.nbPlayers;
		int nbBonusTemp;
		int x=0;
		int y=0;
		
		//generation des joueurs
		generatePlayer(nbPlayer);
		
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
		generateBox();
		
	}
	
	void GameEngineManager::run() {
		SKeyPressed sKeyPressed = getKeysPressed();
		if (isPaused()) {//si le jeu est en pause
			if(debutPause==0) {
				debutPause=horloge.getElapsedTime().asSeconds();//stockage du début de la pause
			}
		} else {
			//vérification de la pause
			if (debutPause!=0) {
				decalageHoraire(horloge.getElapsedTime().asSeconds()-debutPause);
				debutPause=0;
			}
			
			board.checkPosition();
			
			//supprimer les flammes
			board.removeObseleteFlame(this->horloge);
			//déclencher les bombes
			board.explodeBomb();
			
			//gestion des touches
			for (int i=0; i<board.getNbPlayer(); i++) { //pour chaque zoueur
				if (sKeyPressed.keys[i][0]=true) {//touche haut
					actionToucheHaut(i);
				}
				if (sKeyPressed.keys[i][1]=true) {//touche bas
					actionToucheBas(i);
				}
				if (sKeyPressed.keys[i][2]=true) {//touche gauche
					actionToucheGauche(i);
				}
				if (sKeyPressed.keys[i][3]=true) {//touche droite
					actionToucheDroite(i);
				}
				if (sKeyPressed.keys[i][4]=true) {//touche action1
					actionToucheAction1(i);
				}
				if (sKeyPressed.keys[i][5]=true) {//touche action2
					actionToucheAction2(i);
				}
			}
		}
	}
	
	//IGameEngineToGameInterface
	SBoard GameEngineManager::getBoard() {
		return this->board.boardToSBoard();
	}
	
	int GameEngineManager::isFinished() {
		return board.getIdSurvivant();
	}
}