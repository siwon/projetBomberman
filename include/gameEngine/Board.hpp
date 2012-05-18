#ifndef BOARD_HEADER
#define BOARD_HEADER

/*!
 * \file Board.hpp
 * \brief Classe Board
 * \author Simon Rousseau
 */
 
#include <vector>

#include "../../include/gameEngine/Flame.hpp"
#include "../../include/gameEngine/Bonus.hpp"
#include "../../include/gameEngine/Box.hpp"
#include "../../include/gameEngine/Explosive.hpp"
#include "../../include/gameEngine/Player.hpp"
#include "../../include/gameEngine/Wall.hpp"
#include "../../include/gameEngine/Location.hpp"

#include <iostream>

namespace PolyBomber {
	/*!
	 * \class Board
	 * \brief Classe Board
	 */
	class Board {
		// TODO : faire en sorte que ce soit un singleton !!!
    protected:
		std::vector<Location> locations;
		
		void generateWall();
		void generatePlayer(int nbPlayer);
		void generateBonus(int nbBonus);
		void generateBox(int nbBox);
		
	public:
		Board();
		Board(const Board& b);
		//opérateur d'affectation
		~Board();
		
		void addLocation(Box boite){this->locations.push_back(boite);}
		void addLocation(Explosive bombe){this->locations.push_back(bombe);}
		void addLocation(Flame flamme){this->locations.push_back(flamme);}
		void addLocation(Bonus bonus){this->locations.push_back(bonus);}
		void addLocation(Player joueur){this->locations.push_back(joueur);}
		void addLocation(Wall mur){this->locations.push_back(mur);}
		
		void generateBoard(int nbPlayer, int nbBonus, int nbBox);
		
		void removeLocation(int x, int y);
		
		bool isEmpty(int x, int y); // détermine si une case est vide
		
		const std::vector<Location> getLocation() const {return this->locations;}
		
		const Board getBoard() const {return *this;}
		
		std::vector<Player> getPlayer();
		std::vector<Explosive> getExplosive();
		std::vector<Flame> getFlame();
		std::vector<Bonus> getBonus();
		std::vector<Box> getBox();
		std::vector<Wall> getWall();
		
		void toString() {
			for (unsigned int i=0; i<locations.size(); i++) {
				std::cout << locations[i].getLocation().x << " ; " << locations[i].getLocation().y << std::endl;
			}
		}
		
	};
}

#endif
