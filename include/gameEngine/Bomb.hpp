#ifndef BOMB_HEADER
#define BOMB_HEADER

/*!
 * \file Bomb.hpp
 * \brief Classe Bomb
 * \author Simon ROUSSEAU
 */

namespace PolyBomber {
	/*!
	 * \class Bomb
	 * \brief Classe Bomb
	 */
	class Bomb : public Explosive {
    protected:
		int timeOfExplosion; /*! Seconde ou doit exploser la bombe */
	public:
		Bomb(int time, Player player);
		Bomb(Bomb bombe);
		//opérateur par recopie
		~Bomb();
		
		int getTimeOfExplosion(){return this->timeOfExplosion;}
	};
}

#endif