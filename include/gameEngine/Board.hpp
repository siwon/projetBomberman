#ifndef BOARD_HEADER
#define BOARD_HEADER

/*!
 * \file Board.hpp
 * \brief Classe Board
 * \author Simon Rousseau
 */

namespace PolyBomber {
	/*!
	 * \class Board
	 * \brief Classe Board
	 */
	class Board {
		// TODO : faire en sorte que ce soit un singleton !!!
    protected:
		vector<Location> locations;
		//    vector<Player> joueur; /** Liste des joueurs */
		//	  vector<Explosive> bombe; /** Liste des bombes */
		//	  vector<Flame> deflagration; /** Liste des déflagrations */
		//	  vector<Bonus> bonus; /** Liste des bonus */
		//	  vector<Box> boite; /** Liste des boites */
		//	  vector<Wall> mur; /** Liste des murs */
		
		Board();
		Board(Board b);
		//opérateur d'affectation
		~Board();
		
		void addLocation(Box boite){this->locations.push_back(boite);}
		void addLocation(Bombe bombe){this->locations.push_back(bombe);}
		void addLocation(Flame flamme){this->locations.push_back(flamme);}
		void addLocation(Bonus bonus){this->locations.push_back(bonus);}
		void addLocation(Player joueur){this->locations.push_back(joueur);}
		void addLocation(Wall mur){this->locations.push_back(mur);}
		
		void removeLocation(int x, int y);
		
		vector<Player> getPlayer();
		vector<Explosive> getExplosive();
		vector<Flame> getFlame();
		vector<Bonus> getBonus();
		vector<Box> getBox();
		vector<Wall> getWall();
		
		void generateBoard(int nbPlayer, int nbBonus, int nbBox);
		
		void generateWall();
		void generatePlayer(int nbPlayer);
		void generateBonus(int nbBonus);
		void generateBox(int nbBox);
		
	public:
		
		
		
	private:
		bool isEmpty(int x, int y); // détermine si une case est vide
		
	};
}

#endif