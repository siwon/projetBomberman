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

#include "EOrientation.hpp"

#include "gameEngine/DefineAndFunction.hpp"

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
		//Bonus du joueur
		std::vector<Bonus> bombBonus;
		std::vector<Bonus> infection;
		
		
    public:
		Player(float x, float y, int id);
		Player(const Location& loc);
		Player(const Player& pl);
		//operateur d affectation
		~Player();
				
		int getId() const {return this->id;}
		int getSpeed() const {return this->speed;}
		int getCapacity() const {return this->capacity;}
		EOrientation getOrientation() const {return this->orientation;}
		bool getAlive() const {return this->alive;}
		int getStep() const {return this->step;}
		int getRange() const {return this->range;}
		std::vector<Bonus> getBombBonus(){return this->bombBonus;}
		std::vector<Bonus> getInfection(){return this->infection;}
	};
}

#endif
