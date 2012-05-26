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

#include "../../include/gameEngine/GameEngineManager.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	
	GameEngineManager::GameEngineManager() {
		this->board=Board();
		this->gameConfigIsSet=false;
		this->runnable=false;
		this->horloge=sf::Clock();
		this->debutPause=0;
		srand(time(NULL));
	}
	
	GameEngineManager::~GameEngineManager() {
		this->board.~Board();
		this->horloge.~Clock();
	}
	
	void GameEngineManager::generateWall() {
		for (int i=0; i<19; i++) {
			for (int j=0; j<13; j++) {
				if (i%2==1 && j%2==1) { // case impaire
					board.addWall(Wall(i,j));
				}
			}
		}
	}
	
	void GameEngineManager::generatePlayer(int nbPlayer) {
		switch (nbPlayer) {//TODO : vérifier la position des joueurs
			case 2:
				board.addPlayer(Player(3,3,0));
				board.addPlayer(Player(87,62,1));
				break;
				
			case 3:
				board.addPlayer(Player(3,3,0));
				board.addPlayer(Player(87,3,1));
				board.addPlayer(Player(45,62,2));
				break;
				
			case 4:
				board.addPlayer(Player(3,3,0));
				board.addPlayer(Player(87,3,1));
				board.addPlayer(Player(87,62,2));
				board.addPlayer(Player(3,62,3));
				break;
				
			default:
				break;
		}
	}
	
	void GameEngineManager::generateBox(int nbBox) {
		int x=rand()%18;
		int y=rand()%13;

		for (int i=0;i<nbBox;i++) {
			while (!board.caseIsFreeInitialisation(x,y)) {
				x=rand()%18;
				y=rand()%13;
			}
			board.addBox(Box(x,y));
		}
	}
	
	void GameEngineManager::generateFlame(int origineX, int origineY, int range, int date) {
		board.generateFlame(origineX, origineY, range, date);
	}
	
	void GameEngineManager::decalageHoraire(int secondes) {
		this->board.effectuerDecalage(secondes);
	}
	
	//IGameEngineToNetwork
	void GameEngineManager::setGameConfig(SGameConfig gameConfig) {
		if (!gameConfigIsSet) {
			resetConfig();
		}
		int nbPlayer = gameConfig.nbPlayers;
		int nbBonusTemp;
		int x=rand()%18;
		int y=rand()%13;
		int nbBonus=0;
		
		//generation des joueurs
		generatePlayer(nbPlayer);
		
		//generation des murs
		generateWall();
		
		//generation des bonus
		for (int i=0;i<18;i++) {
			nbBonusTemp = gameConfig.nbBonus[i];
			for (int j=0; j<nbBonusTemp; j++) {
				while (!board.caseIsFreeInitialisation(x,y)) {
					x=rand()%18;
					y=rand()%13;
				}
				board.addBonus(Bonus(x,y,(EGameBonus)i,false));
			}
			nbBonus=nbBonus+nbBonusTemp;
		}
		
		//generation des caisses
		generateBox(NOMBREBOX-nbBonus);
		
		this->gameConfigIsSet=true;
	}
	
	void GameEngineManager::run() {
		if (runnable) {
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
				
				board.checkPosition(horloge.getElapsedTime().asSeconds());
				
				//supprimer les flammes
				board.removeObseleteFlame(horloge.getElapsedTime().asSeconds());
				//déclencher les bombes
				board.explodeAllBomb(horloge.getElapsedTime().asSeconds());
				
				//gestion des touches
				for (int i=0; i<board.getNbPlayer(); i++) { //pour chaque zoueur
					if (sKeyPressed.keys[i][0]=true) {//touche haut
						board.actionToucheHaut(i);
					}
					if (sKeyPressed.keys[i][1]=true) {//touche bas
						board.actionToucheBas(i);
					}
					if (sKeyPressed.keys[i][2]=true) {//touche gauche
						board.actionToucheGauche(i);
					}
					if (sKeyPressed.keys[i][3]=true) {//touche droite
						board.actionToucheDroite(i);
					}
					if (sKeyPressed.keys[i][4]=true) {//touche action1
						board.actionToucheAction1(i,horloge.getElapsedTime().asSeconds());
					}
					if (sKeyPressed.keys[i][5]=true) {//touche action2
						board.actionToucheAction2(i,horloge.getElapsedTime().asSeconds());
					}
				}
			}
		}
	}
	
	//IGameEngineToGameInterface
	SBoard GameEngineManager::getBoard() {
		SBoard gameboard = this->board.boardToSBoard();
		return gameboard;
	}
	
	int GameEngineManager::isFinished() {
		return board.getIdSurvivant();
	}
	
	void GameEngineManager::resetConfig() {
		this->runnable=false;
		board.resetConfig();
		this->gameConfigIsSet=false;
	}
}