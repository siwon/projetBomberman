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
#include "gameEngine/Explosive.hpp"
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
		std::vector<Explosive> explosive;
		std::vector<Wall> wall;
		
	public:
		Board();
		Board(const Board& b);
		//operateur d affectation
		~Board();
		
		SBoard boardToSBoard();
		
		void addPlayer(Player pl) {player.push_back(pl);}
		void addWall(Wall w) {wall.push_back(w);}
		void addBonus(Bonus b) {bonus.push_back(b);}
		void addBox(Box b) {box.push_back(b);}
		
		bool caseIsFreeInitialisation(float x, float y);
		bool caseIsFree(float x, float y);
		int nbSurvivant();
		int getIdSurvivant();
		
		static float caseToPixel(float i) {return i*LARGEUR;}
		static int pixelToCase(float i) {return i/LARGEUR;}
		static EGameBonus intToEGameBonus(int i);
		
		
	};
}

#endif
