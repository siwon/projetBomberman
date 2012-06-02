/*!
 * \file Player.cpp
 * \brief Implementation de la classe Player
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <vector>
#include <iostream>

// Bibliotheques SFML
#include <SFML/System/Vector2.hpp>

// Bibliotheques externes


// Headers
#include "gameEngine/Bonus.hpp"
#include "EOrientation.hpp"
#include "gameEngine/DefineAndFunction.hpp"
#include "gameEngine/Player.hpp"

namespace PolyBomber {
	
	Player::Player(int x, int y, int id) : Location(x,y) {
		this->id=id;
		this->speed=VITESSEPARDEFAUT;
		this->capacity=NOMBREBOMBEDEFAUT;
		this->orientation=ORIENTATIONDEFAUT;
		this->range=RANGEDEFAUT;
		this->alive=true;
		this->step=0;
		this->saveCaracBeforeInfectionDilatation=0;
		this->detonator=false;
		this->lastMove=0;
		this->lastActionSecond=0;
		
		this->bombBonus=std::vector<Bonus>();
		this->infection=0;
		/*
		 * 0 => rien
		 * 1 => CONFUSION
		 * 2 => SPASME
		 * 3 => DILATATION
		 * 4 => RAGE
		 */
	}
	
	Player::Player(const Player& pl) : Location(pl.getLocationX(),pl.getLocationY()) {
		this->id=pl.getId();
		this->speed=pl.getSpeed();
		this->capacity=pl.getCapacity();
		this->orientation=pl.getOrientation();
		this->range=pl.getRange();
		this->alive=pl.getAlive();
		this->step=pl.getStep();
		this->saveCaracBeforeInfectionDilatation=0;
		this->detonator=false;
		this->lastMove=0;
		this->lastActionSecond=0;
		
		this->bombBonus=std::vector<Bonus>();
		this->infection=pl.getInfection();
	}
	
	Player::~Player() {
	}
	
	void Player::removeInfection() {
		if (infection==3) {
			speed=saveCaracBeforeInfectionDilatation;
		}
		saveCaracBeforeInfectionDilatation=0;
		infection=0;
	}
	
	void Player::addBonus(Bonus bonus) {
		removeInfection();
		switch (bonus.getType()) {
			case SPEEDUP:
				speed=speed-PASVITESSE;
				if (speed<VITESSEMAX) {
					speed=VITESSEMAX;
				}
				break;
				
			case SPEEDDOWN:
				speed=speed+PASVITESSE;
				if (speed>VITESSEMIN) {
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
				
			case CONFUSION:
				this->infection=1;
				break;
				
			case SPASME:
				this->infection=2;
				break;
				
			case DILATATION:
				this->saveCaracBeforeInfectionDilatation=this->speed;
				this->infection=3;
				this->speed=VITESSEMIN;
				break;
				
			case RAGE:
				this->infection=4;
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
