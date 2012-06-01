/*!
 * \file GameEngineManager.cpp
 * \brief Implementation de la classe GameEngineManager
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <ctime>
#include <cstdlib>

// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "../../include/gameEngine/GameEngineManager.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"

#include "../../include/PolyBomberApp.hpp"

namespace PolyBomber {
	
	GameEngineManager::GameEngineManager() {
		this->network=PolyBomberApp::getINetworkToGameEngine();
		this->board=Board();
		this->gameConfigIsSet=false;
		this->runnable=false;
		this->horloge=sf::Clock();
		this->debutPause=0;
		this->lastInfectionAction=0;
		srand(time(NULL));
	}
	
	GameEngineManager::~GameEngineManager() {
	}
	
	void GameEngineManager::generateWall() {
		this->mutexBoard.lock();
		for (int i=0; i<19; i++) {
			for (int j=0; j<13; j++) {
				if (i%2==1 && j%2==1) { // case impaire
					board.addWall(Wall(i,j));
				}
			}
		}
		this->mutexBoard.unlock();
	}
	
	void GameEngineManager::generatePlayer(int nbPlayer) {
		this->mutexBoard.lock();
		switch (nbPlayer) {
			case 2:
				board.addPlayer(Player(2,2,0));
				board.addPlayer(Player(92,62,1));
				break;
				
			case 3:
				board.addPlayer(Player(2,2,0));
				board.addPlayer(Player(92,2,1));
				board.addPlayer(Player(47,62,2));
				break;
				
			case 4:
				board.addPlayer(Player(2,2,0));
				board.addPlayer(Player(92,2,1));
				board.addPlayer(Player(92,62,2));
				board.addPlayer(Player(2,62,3));
				break;
				
			default:
				break;
		}
		this->mutexBoard.unlock();
	}
	
	void GameEngineManager::generateBox(int nbBox) {
		int x=rand()%19;
		int y=rand()%13;
		
		for (int i=0;i<nbBox;i++) {
			while (!board.caseIsFreeInitialisation(x,y)) {
				x=rand()%19;
				y=rand()%13;
			}
			this->mutexBoard.lock();
			board.addBox(Box(x,y));
			this->mutexBoard.unlock();
		}
	}
	
	void GameEngineManager::generateFlame(int origineX, int origineY, int range, int date) {
		this->mutexBoard.unlock();
		board.generateFlame(origineX, origineY, range, date);
		this->mutexBoard.unlock();
	}
	
	void GameEngineManager::decalageHoraire(int secondes) {
		this->mutexBoard.lock();
		this->board.effectuerDecalage(secondes);
		this->mutexBoard.unlock();
	}
	
	//IGameEngineToNetwork
	void GameEngineManager::setGameConfig(SGameConfig gameConfig) {		
		if (!gameConfigIsSet) {
			resetConfig();
		}
		std::cout << gameConfig.nbPlayers<< std::endl;
		int nbPlayer = gameConfig.nbPlayers;
		int nbBonusTemp;
		int x=rand()%19;
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
					x=rand()%19;
					y=rand()%13;
				}
				
				this->mutexBoard.lock();
				board.addBonus(Bonus(x,y,(EGameBonus)i,false));
				this->mutexBoard.unlock();
			}
			
			nbBonus=nbBonus+nbBonusTemp;
		}
		
		//generation des caisses
		generateBox(NOMBREBOX-nbBonus);
		
		this->gameConfigIsSet=true;
		this->runnable = true;
	}
	
	void GameEngineManager::run() {
		while (runnable) {
			int time=horloge.getElapsedTime().asSeconds();
			int time2=horloge.getElapsedTime().asMilliseconds();
			SKeyPressed sKeyPressed = network->getKeysPressed();
			
			if (network->isPaused()) {//si le jeu est en pause
				if(debutPause==0) {
					debutPause=time;//stockage du début de la pause
				}
			} else {
				//vérification de la pause
				if (debutPause!=0) {
					decalageHoraire(time-debutPause);
					debutPause=0;
				}
				
				//provoque les actions associees aux infections
				if (time%TEMPSENTREDEUXACTIONSINFECTION==0) {
					if (time!=this->lastInfectionAction) {
						this->mutexBoard.lock();
						board.makeInfectionAction(time);
						this->mutexBoard.unlock();
						this->lastInfectionAction=time;
					}
				}
				
				this->mutexBoard.lock();
				board.checkPosition(time);
				this->mutexBoard.unlock();
				
				//supprimer les flammes
				this->mutexBoard.lock();
				board.removeObseleteFlame(time);
				this->mutexBoard.unlock();
				
				//déclencher les bombes
				this->mutexBoard.lock();
				board.explodeAllBomb(time);
				this->mutexBoard.unlock();
				
				//gestion des touches
				for (int i=0; i<board.getNbPlayer(); i++) { //pour chaque zoueur
					if (sKeyPressed.keys[i][0]==true) {//touche haut
						this->mutexBoard.lock();
						board.actionToucheHaut(i, time2);
						this->mutexBoard.unlock();
					}
					if (sKeyPressed.keys[i][1]==true) {//touche bas
						this->mutexBoard.lock();
						board.actionToucheBas(i, time2);
						this->mutexBoard.unlock();
					}
					if (sKeyPressed.keys[i][2]==true) {//touche gauche
						this->mutexBoard.lock();
						board.actionToucheGauche(i, time2);
						this->mutexBoard.unlock();
					}
					if (sKeyPressed.keys[i][3]==true) {//touche droite
						this->mutexBoard.lock();
						board.actionToucheDroite(i, time2);
						this->mutexBoard.unlock();
					}
					if (sKeyPressed.keys[i][4]==true) {//touche action1
						this->mutexBoard.lock();
						board.actionToucheAction1(i,time);
						this->mutexBoard.unlock();
					}
					if (sKeyPressed.keys[i][5]==true) {//touche action2
						this->mutexBoard.lock();
						board.actionToucheAction2(i,time);
						this->mutexBoard.unlock();
					}
				}
			}
			
			sf::sleep(sf::milliseconds(8));

			if (board.nbSurvivant()<=1) {
				this->runnable=false;
				std::cout << "Partie terminee" << std::endl;
			}
		}
	}
	
	//IGameEngineToGameInterface
	SBoard GameEngineManager::getBoard() {
		this->mutexBoard.lock();
		SBoard gameboard = this->board.boardToSBoard();
		this->mutexBoard.unlock();
		return gameboard;
	}
	
	int GameEngineManager::isFinished() {
		this->mutexBoard.lock();
		return board.getIdSurvivant();
		this->mutexBoard.unlock();
	}
	
	void GameEngineManager::resetConfig() {
		this->runnable=false;
		this->mutexBoard.lock();
		board.resetConfig();
		this->mutexBoard.unlock();
		this->gameConfigIsSet=false;
	}
}
