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
		
		static int caseToPixel(int i) {
			return i*LARGEUR;
		}
		
		static int pixelToCase(int i) {
			return i/LARGEUR;
		}
		
	};
}

#endif
