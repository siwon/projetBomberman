/*!
 * \file Player.cpp
 * \brief Implementation de la classe Player
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "gameEngine/Player.hpp"

namespace PolyBomber {
	
	Player::Player(float x, float y, int id) : Location(x,y) {
		this->id=id;
		this->speed=VITESSEPARDEFAUT;
		this->capacity=NOMBREBOMBEDEFAUT;
		this->orientation=ORIENTATIONDEFAUT;
		this->range=RANGEDEFAUT;
		this->alive=true;
		this->step=0;
		
		this->bombBonus=std::vector<Bonus>();
		this->infection=std::vector<Bonus>();
	}
	
	Player::Player(const Player& pl) : Location(pl.getLocationX(),pl.getLocationY()) {
		this->id=pl.getId();
		this->speed=pl.getSpeed();
		this->capacity=pl.getCapacity();
		this->orientation=pl.getOrientation();
		this->range=pl.getRange();
		this->alive=getAlive();
		this->step=getStep();
		
		this->bombBonus=std::vector<Bonus>();
		this->infection=std::vector<Bonus>();
	}
	
	Player::~Player() {
		this->bombBonus.~vector();
		this->infection.~vector();
	}
	
	void Player::removeInfection() {
		infection.clear();
	}
	
	void Player::addBonus(Bonus bonus) {
		removeInfection();
		switch (bonus.getType()) {
			case SPEEDUP:
				speed=speed+PASVITESSE;
				if (speed>VITESSEMAX) {
					speed=VITESSEMAX;
				}
				break;
				
			case SPEEDDOWN:
				speed=speed-PASVITESSE;
				if (speed<VITESSEMIN) {
					speed=VITESSEMIN;
				}
				break;
				
			case BOMBLINE:
				bombBonus.push_back(bonus);
				break;
				
			case DETONATOR:
				bombBonus.push_back(bonus);
				break;
				
			case BOMBUP:
				capacity++;
				break;
				
			case BOMBDOWN:
				capacity--;
				if (capacity<1) {
					capacity=1;
				}
				break;
				
			case RANGEUP:
				range=range+PASRANGE;
				if (range>RANGEMAX) {
					range=RANGEMAX;
				}
				break;
				
			case RANGEDOWN:
				range=range-PASRANGE;
				if (range<RANGEMIN) {
					range=RANGEMIN;
				}
				break;
				
			case RANGEUPMAX:
				range=RANGEMAX;
				break;
				
			case MINE:
				bombBonus.push_back(bonus);
				break;
				
			case INFINITYBOMB:
				bombBonus.push_back(bonus);
				break;
				
			case ATOMICBOMB:
				bombBonus.push_back(bonus);
				break;
				
			case CRANE:
				infection.push_back(bonus);
				break;
				
			case HELL:
				infection.push_back(bonus);
				break;
				
			case CONFUSION:
				infection.push_back(bonus);
				break;
				
			case SPASME:
				infection.push_back(bonus);
				break;
				
			case DILATATION:
				infection.push_back(bonus);
				break;
				
			case RAGE:
				infection.push_back(bonus);
				break;
				
			default:
				break;
		}
	}
}