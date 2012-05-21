#ifndef BOMB_HEADER
#define BOMB_HEADER

/*!
 * \file Bomb.hpp
 * \brief Classe Bomb
 * \author Simon ROUSSEAU
 */

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "gameEngine/Explosive.hpp"

#include "gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Bomb
	 * \brief Classe Bomb
	 */
	class Bomb : public Explosive {
    protected:
		int timeOfExplosion; /*! Seconde ou doit exploser la bombe */
	public:
		Bomb(sf::Clock horloge, const Player& player);
		Bomb(const Bomb& bombe);
		//operateur par recopie
		~Bomb();
		
		int getTimeOfExplosion() const {return this->timeOfExplosion;}
		void decalerExplosion(int nbSecondes) {this->timeOfExplosion=this->timeOfExplosion+nbSecondes;}
	};
}

#endif