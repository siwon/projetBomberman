#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/*!
 * \file Player.hpp
 * \brief Classe Player
 * \author Simon ROUSSEAU
 */

#include <vector>

#include "Bonus.hpp"
#include "Location.hpp"

#include "../EOrientation.hpp"

#include "../gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Player
	 * \brief Classe Player
	 */
	class Player : public Location {
    protected:
		int id;				/*! Identifiant du joueur */
		int speed;			/*! Vitesse du joueur */
		int capacity;		/*! Nombre de bombes qu un joueur peut poser */
		EOrientation orientation;	/*! Orientation du joueur */
		bool alive;	/*! Statut du joueur */
		int step;			/*! Etat de la jambe du joueur */
		int range;
		bool detonator;
		//Bonus du joueur
		std::vector<Bonus> bombBonus;
		Bonus infection;
		
	private:
		void removeInfection();
		
	public:	
		Player(int, int, int);
		Player(const Player& pl);
		Player& operator=(Player&);
		~Player();

		inline int getId() const {return this->id;}
		inline int getSpeed() const {return this->speed;}
		inline int getCapacity() const {return this->capacity;}
		inline EOrientation getOrientation() const {return this->orientation;}
		inline bool getAlive() const {return this->alive;}
		inline int getStep() const {return this->step;}
		inline int getRange() const {return this->range;}
		inline bool getDetonator() const {return this->detonator;}
		inline std::vector<Bonus> getBombBonus(){return this->bombBonus;}
		inline Bonus getInfection(){return this->infection;}
		
		inline void killPlayer() {this->alive=false;}
		void addBonus(Bonus bonus);
		void move(int, int);
		void centrerPlayerSurAxeHorizontal();
		void centrerPlayerSurAxeVertical();
	};
}

#endif
