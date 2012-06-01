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
		int lastMove; //date du dernier mouvement
		int range;
		bool detonator;
		int saveCaracBeforeInfectionDilatation;
		//Bonus du joueur
		std::vector<Bonus> bombBonus;
		int infection;
		
	private:
		void removeInfection();
		
	public:	
		Player(int, int, int);
		Player(const Player& pl);
		//Player& operator=(Player&);
		~Player();

		inline int getId() const {return this->id;}
		inline int getSpeed() const {return this->speed;}
		inline int getCapacity() const {return this->capacity;}
		inline EOrientation getOrientation() const {return this->orientation;}
		inline bool getAlive() const {return this->alive;}
		inline int getLastMove() const {return this->lastMove;}
		inline int getStep() const {return this->step;}
		inline int getRange() const {return this->range;}
		inline bool getDetonator() const {return this->detonator;}
		inline std::vector<Bonus> getBombBonus(){return this->bombBonus;}
		inline EGameBonus getFirstBombBonus(){return this->bombBonus[0].getType();}
		inline int getInfection() const {return this->infection;}
		
		inline void killPlayer() {this->alive=false;}
		void addBonus(Bonus bonus);
		void move(int, int);
		void centrerPlayerSurAxeHorizontal();
		void centrerPlayerSurAxeVertical();
		inline void incrementStep() {this->step++;}
		inline void setOrientation(EOrientation orient) {this->orientation=orient;}
		inline void incrementCapacity(int i=1) {this->capacity+=i;}
		inline void decrementCapacity(int i=1) {this->capacity-=i;}
		inline void setLastMove(int date) {this->lastMove=date;}
	};
}

#endif
