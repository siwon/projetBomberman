#ifndef BOARD_HEADER
#define BOARD_HEADER

/*!
 * \file Board.hpp
 * \brief Classe Board
 * \author Simon Rousseau
 */
 
#include <vector>

#include "Flame.hpp"
#include "Bonus.hpp"
#include "Box.hpp"
#include "RemoteBomb.hpp"
#include "Bomb.hpp"
#include "Mine.hpp"
#include "Player.hpp"
#include "Wall.hpp"

#include "../SBoard.hpp"

#include "DefineAndFunction.hpp"


namespace PolyBomber {
	/*!
	 * \class Board
	 * \brief Classe Board
	 */
	class Board {
    protected:
		std::vector<Bonus> bonus;
		std::vector<Flame> flame;
		std::vector<Box> box;
		std::vector<Player> player;
		std::vector<Bomb> bomb;
		std::vector<RemoteBomb> remoteBomb;
		std::vector<Mine> mine;
		std::vector<Wall> wall;
		
		Player getPlayerById(int);
		
	public:
		Board();
		Board(const Board&);
		//Board& operator=(Board&);
		~Board();
		
		inline int getNbPlayer() {return this->player.size();}
		
		SBoard boardToSBoard();
		
		//gestion des touches
		void actionToucheHaut(int);
		void actionToucheBas(int);
		void actionToucheGauche(int);
		void actionToucheDroite(int);
		void actionToucheAction1(int, int);
		void actionToucheAction2(int, int); //TODO
		
		inline void addPlayer(Player pl) {player.push_back(pl);}
		inline void addWall(Wall w) {wall.push_back(w);}
		inline void addBonus(Bonus b) {bonus.push_back(b);}
		inline void addBox(Box b) {box.push_back(b);}
		inline void addFlame(Flame f) {flame.push_back(f);}
		
		void removeBox(int i);
		
		bool caseIsFreeInitialisation(int, int);
		bool caseIsFree(int, int);
		bool isAWallInThisCase(int, int);//vérifie si il y a un mur dans la case sélectionnée
		bool isAFlameInThisCase(int, int);
		bool isABonusInThisCase(int, int);
		bool isAMineInThisCase(int, int);
		
		
		int nbSurvivant();
		int getIdSurvivant();
		void applyBonus(int, Bonus);
		void effectuerDecalage(int);
		void explodeBomb(int, int);
		void explodeBomb(unsigned int);
		void explodeRemoteBomb(unsigned int, int);
		void explodeMine(int, int, int);
		void explodeMine(unsigned int, int);
		void generateFlame(int, int, int, int);
		Bonus getBonusByCoord(int, int);
		inline Bonus getBonusByIndice(unsigned int indice){return this->bonus[indice];}
		unsigned int getIndiceBonus(int, int);
		unsigned int getIndiceMineByCoord(int, int);
		
		void checkPosition(int);//A VERIFIER
		void removeObseleteFlame(int);
		void explodeAllBomb(int);
		
		static int caseToPixel(int i) {return i*LARGEUR;}
		static int pixelToCase(int i) {return i/LARGEUR;}
		static int cranToPixel(int i) {return i*7+4;}
		static int cranToCase(int i) {return (i-(i%5))/5;}
		static bool distanceDesAutresJoueursValide(int, int, int); //TODO
	};
}

#endif
