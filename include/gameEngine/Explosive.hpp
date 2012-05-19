#ifndef EXPLOSIVE_HEADER
#define EXPLOSIVE_HEADER

/*!
 * \file Explosive.hpp
 * \brief Classe Explosive
 * \author Simon ROUSSEAU
 */

#include "gameEngine/Player.hpp"
#include "gameEngine/Location.hpp"

#include "gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Explosive
	 * \brief Classe Explosive
	 */
	class Explosive : public Location {
    protected:
		int range;		/*! Portee de la bombe */
		int player;	/*! Joueur qui possede la bombe */
		
		Explosive(int player, int range, float x, float y);
		
    public:
		Explosive(const Player& player);
		Explosive(const Explosive& expl);
		//operateur d affectation
		~Explosive();
		
		int getRange() const {return this->range;}
		int getPlayer() const {return this->player;}
	};
}

#endif