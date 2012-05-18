/*!
 * \file Player.cpp
 * \brief Implémentation de la classe Player
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards
#include <Vector>

// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Player.hpp"
#include "../../include/gameEngine/DefineAndFunction.hpp"
#include "../../include/EOrientation.hpp"

using namespace PolyBomber;

Player::Player(int x, int y) : Location(x,y) {
	this->id=this->nbJoueur;
	this->nbJoueur++;
	this->speed=VITESSEPARDEFAUT;
	this->capacity=NOMBREBOMBEDEFAUT;
	this->orientation=ORIENTATIONDEFAUT;
	this->range=RANGEDEFAUT;
	this->alive=true;
	this->step=0;
}

Player::Player(const Location& loc) : Location(loc) {
	this->id=this->nbJoueur;
	this->nbJoueur++;
	this->speed=VITESSEPARDEFAUT;
	this->capacity=NOMBREBOMBEDEFAUT;
	this->orientation=ORIENTATIONDEFAUT;
	this->range=RANGEDEFAUT;
	this->alive=true;
	this->step=0;
}

Player::Player(const Player& pl) : Location(pl.getLocation()) {
	this->id=this->nbJoueur;
	this->nbJoueur++;
	this->speed=pl.getSpeed();
	this->capacity=pl.getCapacity();
	this->orientation=pl.getOrientation();
	this->range=pl.getRange();
	this->alive=getAlive();
	this->step=getStep();
}

Player::~Player() {
	
}

void Player::die() {
	this->alive=false;
}

void Player::applyBonus(Bonus bonus) {
	switch (bonus.getType()) {
		case SPEEDUP :
			this->speed=this->speed+PASVITESSE;
			break;
			
		case SPEEDDOWN :
			this->speed=this->speed-PASVITESSE;
			break;
			
		case BOMBLINE :
			this->bombBonus.push_back(bonus);
			break;
			
		case DETONATOR :
			this->bombBonus.push_back(bonus);
			break;
			
		case BOMBUP :
			this->capacity=this->capacity+1;
			break;
			
		case BOMBDOWN :
			this->capacity=this->capacity-1;
			break;
			
		case RANGEUP :
			this->range=this->range+PASRANGE;
			break;
			
		case RANGEDOWN :
			this->range=this->range+PASRANGE;
			break;
			
		case RANGEUPMAX :
			this->range=RANGEMAX;
			break;
			
		case MINE :
			this->bombBonus.push_back(bonus);
			break;
			
		case INFINITYBOMB :
			this->bombBonus.push_back(bonus);
			break;
			
		case ATOMICBOMB :
			this->bombBonus.push_back(bonus);
			break;
			
		case CRANE :
			this->infection.push_back(bonus);
			break;
			
		case HELL :
			this->infection.push_back(bonus);
			break;
			
		case CONFUSION :
			this->infection.push_back(bonus);
			break;
			
		case SPASME :
			this->infection.push_back(bonus);
			break;
			
		case DILATATION :
			this->infection.push_back(bonus);
			break;
			
		case RAGE :
			this->infection.push_back(bonus);
			break;
			
		default:
			//erreur
			break;
	}
}

void Player::move(EOrientation direction) {
	
}