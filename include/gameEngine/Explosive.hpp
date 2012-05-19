#ifndef EXPLOSIVE_HEADER
#define EXPLOSIVE_HEADER

/*!
 * \file Explosive.hpp
 * \brief Classe Explosive
 * \author Simon ROUSSEAU
 */

#include "gameEngine/Player.hpp"
#include "gameEngine/Location.hpp"

namespace PolyBomber {
	/*!
	 * \class Explosive
	 * \brief Classe Explosive
	 */
	class Explosive : public Location {
    protected:
		int range;		/*! Portee de la bombe */
		int player;	/*! Joueur qui possede la bombe */
    public:
		Explosive(const Player& player);
		Explosive(const Location& loc, int player, int range);
		Explosive(const Explosive& expl);
		//operateur d affectation
		~Explosive();
		
		/*!
		 * \brief Methode provoquant l explosion de l explosif
		 * 
		 */
		void explode();
		
		const int getRange() const {return this->range;}
		const int getPlayer() const {return this->player;}
	};
}

#endif