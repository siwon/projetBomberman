#ifndef BOARD_HEADER
#define BOARD_HEADER

/*!
 * \file Board.hpp
 * \brief Classe Board
 * \author Simon Rousseau
 */
 
#include <vector>
#include <iostream>

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
		
		Player& getPlayerById(int);
		void generateFlameHorizontal(int, int, int, int);
		
	public:
		Board();
		Board(const Board&);
		//Board& operator=(Board&);
		~Board();
		
		inline int getNbPlayer() {return this->player.size();}
		
		SBoard boardToSBoard();
		
		//gestion des touches
		void actionToucheHaut(int, int);
		void actionToucheBas(int, int);
		void actionToucheGauche(int, int);
		void actionToucheDroite(int, int);
		void actionToucheAction1(int, int, int);
		void actionToucheAction2(int, int, int);
		
		inline void addPlayer(Player pl) {this->player.push_back(pl);}
		inline void addWall(Wall w) {this->wall.push_back(w);}
		inline void addBonus(Bonus b) {this->bonus.push_back(b);}
		inline void addBox(Box b) {this->box.push_back(b);}
		inline void addFlame(Flame f) {this->flame.push_back(f);}
		
		void removeBox(int i);
		
		bool caseIsFreeInitialisation(int, int);
		bool caseIsFree(int, int);
		bool isAWallInThisCase(int, int);//vérifie si il y a un mur dans la case sélectionnée
		bool isAFlameInThisCase(int, int);
		bool isABonusInThisCase(int, int);
		bool isAMineInThisCase(int, int);
		bool isABombInThisCase(int, int);
		
		
		int nbSurvivant();
		int getIdSurvivant();
		/*
		 * -1 : pas de gagnant et partie terminée
		 * 0 : partie non terminée
		 * 1-4 : renvoie l'id du joueur +1
		 */
		void applyBonus(int, Bonus);
		void effectuerDecalage(int);
		void explodeBomb(int, int);
		void explodeBomb(unsigned int);
		void explodeRemoteBomb(unsigned int, int);
		void explodeMine(int, int, int);
		void explodeMine(unsigned int, int);
		void generateFlame(int, int, int, int);
		void generateFlameInfinityBomb(unsigned int, int);
		void generateFlameAtomicBomb(unsigned int, int);
		Bonus getBonusByCoord(int, int);
		inline Bonus getBonusByIndice(unsigned int indice){return this->bonus[indice];}
		unsigned int getIndiceBonus(int, int);
		unsigned int getIndiceMineByCoord(int, int);
		void removeBonusByCoord(int x, int y);
		
		void checkPosition(int);
		void makeInfectionAction(int);
		void removeObseleteFlame(int);
		void explodeAllBomb(int);
		
		static int cranToPixel(int i) {return (i-2)*7;}
		static int cranToCase(int i) {return (i-(i%5))/5;}
		bool distanceDesAutresJoueursValide(unsigned int, int, int);
		
		void resetConfig();
	};
}

#endif
