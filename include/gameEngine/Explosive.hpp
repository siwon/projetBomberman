#ifndef EXPLOSIVE_HEADER
#define EXPLOSIVE_HEADER

/*!
 * \file Explosive.hpp
 * \brief Classe Explosive
 * \author Simon ROUSSEAU
 */

#include "Player.hpp"
#include "Location.hpp"

#include "DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Explosive
	 * \brief Classe Explosive
	 */
	class Explosive : public Location {
    protected:
		int range;		/*! Portee de la bombe */
		int player;	/*! Joueur qui possede la bombe */
		
		Explosive(int, int, int, int);
		
    public:
		Explosive(const Player&);
		Explosive(const Player&, int x, int y);
		Explosive(const Explosive&);
		//operateur d affectation
		~Explosive();
		
		inline int getRange() const {return this->range;}
		inline int getPlayer() const {return this->player;}
	};
}

#endif