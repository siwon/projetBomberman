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
#include "../../include/gameEngine/Player.hpp"

namespace PolyBomber {
	
	Player::Player(int x, int y, int id) : Location(x,y) {
		this->id=id;
		this->speed=VITESSEPARDEFAUT;
		this->capacity=NOMBREBOMBEDEFAUT;
		this->orientation=ORIENTATIONDEFAUT;
		this->range=RANGEDEFAUT;
		this->alive=true;
		this->step=0;
		
		this->bombBonus=std::vector<Bonus>();
		
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
	}
	
	Player::~Player() {
	}
	
	void Player::removeInfection() {
		this->infection.~Bonus();
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
				detonator=true;
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
				infection=bonus;
				break;
				
			case HELL:
				infection=bonus;
				break;
				
			case CONFUSION:
				infection=bonus;
				break;
				
			case SPASME:
				infection=bonus;
				break;
				
			case DILATATION:
				infection=bonus;
				break;
				
			case RAGE:
				infection=bonus;
				break;
				
			default:
				break;
		}
	}

	void Player::move(int x, int y) {
		this->setLocation(x,y);
	}

	void Player::centrerPlayerSurAxeHorizontal() {
		int newX=this->getLocationX()-(this->getLocationX()%5)+2;
		int newY=this->getLocationY();
		this->setLocation(newX,newY);
	}

	void Player::centrerPlayerSurAxeVertical() {
		int newX=this->getLocationX();
		int newY=this->getLocationY()-(this->getLocationY()%5)+2;
		this->setLocation(newX,newY);
	}
}