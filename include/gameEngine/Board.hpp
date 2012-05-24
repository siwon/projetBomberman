#ifndef BOARD_HEADER
#define BOARD_HEADER

/*!
 * \file Board.hpp
 * \brief Classe Board
 * \author Simon Rousseau
 */
 
#include <vector>

#include "gameEngine/Flame.hpp"
#include "gameEngine/Bonus.hpp"
#include "gameEngine/Box.hpp"
#include "gameEngine/RemoteBomb.hpp"
#include "gameEngine/Bomb.hpp"
#include "gameEngine/Mine.hpp"
#include "gameEngine/Player.hpp"
#include "gameEngine/Wall.hpp"

#include "SBoard.hpp"

#include "gameEngine/DefineAndFunction.hpp"


namespace PolyBomber {
	/*!
	 * \class Board
	 * \brief Classe Board
	 */
	class Board {
		// TODO : faire en sorte que ce soit un singleton !!!
    protected:
		std::vector<Bonus> bonus;
		std::vector<Flame> flame;
		std::vector<Box> box;
		std::vector<Player> player;
		std::vector<Bomb> bomb;
		std::vector<RemoteBomb> remoteBomb;
		std::vector<Mine> mine;
		std::vector<Wall> wall;
		
		Player getPlayerById(int id);
		
	public:
		Board();
		Board(const Board& b);
		//operateur d affectation
		~Board();
		
		int getNbPlayer() {return this->player.size();}
		
		SBoard boardToSBoard();
		
		//gestion des touches
		void actionToucheHaut(int player); //TODO
		void actionToucheBas(int player); //TODO
		void actionToucheGauche(int player); //TODO
		void actionToucheDroite(int player); //TODO
		void actionToucheAction1(int player); //TODO
		void actionToucheAction2(int player); //TODO
		
		void addPlayer(Player pl) {player.push_back(pl);}
		void addWall(Wall w) {wall.push_back(w);}
		void addBonus(Bonus b) {bonus.push_back(b);}
		void addBox(Box b) {box.push_back(b);}
		void addFlame(Flame f) {flame.push_back(f);}
		
		void removeBox(int i);
		
		bool caseIsFreeInitialisation(float x, float y);
		bool caseIsFree(float x, float y);
		bool isAWallInThisCase(int x, int y);//vérifie si il y a un mur dans la case sélectionnée
		bool isAFlameInThisCase(int x, int y);
		bool isABonusInThisCase(int x, int y);
		bool isAMineInThisCase(int x, int y);
		
		
		int nbSurvivant();
		int getIdSurvivant();
		void applyBonus(int pl, Bonus b);
		void effectuerDecalage(int nbSecondes);
		void explodeBomb(int x, int y);
		void explodeBomb(unsigned int indice);
		void explodeMine(int x, int y, int date);
		void explodeMine(unsigned int indice, int date);
		void generateFlame(int x, int y, int range, int date);
		Bonus getBonusByCoord(int x, int y);
		Bonus getBonusByIndice(unsigned int indice){return this->bonus[indice];}
		unsigned int getIndiceBonus(int x, int y);
		unsigned int getIndiceMineByCoord(int x, int y);
		
		void checkPosition(int date);//A VERIFIER
		void removeObseleteFlame(int date);
		void explodeAllBomb(int date);
		
		static float caseToPixel(float i) {return i*LARGEUR;}
		static int pixelToCase(float i) {return i/LARGEUR;}
		static EGameBonus intToEGameBonus(int i);
		
		
	};
}

#endif
