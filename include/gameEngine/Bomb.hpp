#ifndef BOMB_HEADER
#define BOMB_HEADER

/*!
 * \file Bomb.hpp
 * \brief Classe Bomb
 * \author Simon ROUSSEAU
 */

#include "gameEngine/Explosive.hpp"

namespace PolyBomber {
	/*!
	 * \class Bomb
	 * \brief Classe Bomb
	 */
	class Bomb : public Explosive {
    protected:
		int timeOfExplosion; /*! Seconde ou doit exploser la bombe */
	public:
		Bomb(int time, const Player& player);
		Bomb(const Bomb& bombe);
		//operateur par recopie
		~Bomb();
		
		const int getTimeOfExplosion() const {return this->timeOfExplosion;}
	};
}

#endif