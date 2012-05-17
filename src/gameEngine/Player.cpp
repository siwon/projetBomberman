/*!
 * \file Player.cpp
 * \brief Implémentation de la classe Player
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards


// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/Player.hpp"

namespace PolyBomber;

Player::Player() {
	this->id=this->nbJoueur;
	this->nbJoueur++;
	this->speed=VITESSEPARDEFAUT;
	this->capacity=NOMBREBOMBEDEFAUT;
	this->orientation=ORIENTATIONDEFAUT;
	this->range=RANGEDEFAUT;
	this->alive=true;
	this->step=0;
}

Player::Player(Player pl) {
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
		case EGameBonus.SPEEDUP :
			this->speed=this->speed+PASVITESSE;
			break;
			
		case EGameBonus.SPEEDDOWN :
			this->speed=this->speed-PASVITESSE;
			break;
			
		case EGameBonus.BOMBLINE :
			this->bombBonus.push_back(bonus);
			break;
			
		case EGameBonus.DETONATOR :
			this->bombBonus.push_back(bonus);
			break;
			
		case EGameBonus.BOMBUP :
			this->capacity=this->capacity+1;
			break;
			
		case EGameBonus.BOMBDOWN :
			this->capacity=this->capacity-1;
			break;
			
		case EGameBonus.RANGEUP :
			this->range=this->range+PASRANGE;
			break;
			
		case EGameBonus.RANGEDOWN :
			this->range=this->range+PASRANGE;
			break;
			
		case EGameBonus.RANGEUPMAX :
			this->range=RANGEMAX;
			break;
			
		case EGameBonus.MINE :
			this->bombBonus.push_back(bonus);
			break;
			
		case EGameBonus.INFINITYBOMB :
			this->bombBonus.push_back(bonus);
			break;
			
		case EGameBonus.ATOMICBOMB :
			this->bombBonus.push_back(bonus);
			break;
			
		case EGameBonus.CRANE :
			this->infection.push_back(bonus);
			break;
			
		case EGameBonus.HELL :
			this->infection.push_back(bonus);
			break;
			
		case EGameBonus.CONFUSION :
			this->infection.push_back(bonus);
			break;
			
		case EGameBonus.SPASME :
			this->infection.push_back(bonus);
			break;
			
		case EGameBonus.DILATATION :
			this->infection.push_back(bonus);
			break;
			
		case EGameBonus.RAGE :
			this->infection.push_back(bonus);
			break;
			
		default:
			//erreur
			break;
	}
}

void Player::move(EOrientation direction) {
	
}