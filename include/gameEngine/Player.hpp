#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/*!
 * \file Player.hpp
 * \brief Classe Player
 * \author Simon ROUSSEAU
 */

#include <vector>
#include <iostream>

#include "Bonus.hpp"
#include "Location.hpp"
#include "EOrientation.hpp"

namespace PolyBomber {
	/*!
	 * \class Player
	 * \brief Classe Player
	 */
	class Player : public Location {
    protected:
		int id;				/*< Identifiant du joueur */
		int speed;			/*< Vitesse du joueur */
		int capacity;		/*< Nombre de bombes qu un joueur peut poser */
		EOrientation orientation;	/*< Orientation du joueur */
		bool alive;	/*< Statut du joueur */
		int step;			/*< Etat de la jambe du joueur */
		int lastMove; /*< Date du dernier mouvement */
		int lastActionSecond; /*< Date de la dernière action 2 en secondes */
		int range; /*< Portée du joueur */
		bool detonator; /*< Le joueur possède un détonateur */
		int saveCaracBeforeInfectionDilatation; /*< Permet une sauvegarde des caractéristiques avant l'infection dilatation */
		//Bonus du joueur
		std::vector<Bonus> bombBonus; /*< Vecteur des bonus attribués au joueur */
		int infection; /*< Type d'infection que le joueur a */
		
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
		inline int getLastAction2() const {return this->lastActionSecond;}
		inline int getStep() const {return this->step;}
		inline int getRange() const {return this->range;}
		inline bool getDetonator() const {return this->detonator;}
		inline std::vector<Bonus> getBombBonus(){return this->bombBonus;}
		inline EGameBonus getFirstBombBonus(){return this->bombBonus[0].getType();}
		inline unsigned int getBombBonusSize() {return this->bombBonus.size();}
		inline int getInfection() const {return this->infection;}
		inline void eraseFirstBonus() {this->bombBonus.erase(this->bombBonus.begin());}
		
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
		inline void setLastAction2(int date) {this->lastActionSecond=date;}
	};
}

#endif
