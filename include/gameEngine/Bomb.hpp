#ifndef BOMB_HEADER
#define BOMB_HEADER

/*!
 * \file Bomb.hpp
 * \brief Classe Bomb
 * \author Simon ROUSSEAU
 */

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "Explosive.hpp"

#include "DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Bomb
	 * \brief Classe Bomb
	 */
	class Bomb : public Explosive {
    protected:
		int timeOfExplosion; /*! Seconde ou doit exploser la bombe */
	public:
		Bomb(sf::Clock, const Player&);
		Bomb(const Bomb&);
		Bomb& operator=(Bomb&);
		~Bomb();
		
		inline int getTimeOfExplosion() const {return this->timeOfExplosion;}
		inline void decalerExplosion(int nbSecondes) {this->timeOfExplosion=this->timeOfExplosion+nbSecondes;}
	};
}

#endif