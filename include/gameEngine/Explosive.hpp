#ifndef EXPLOSIVE_HEADER
#define EXPLOSIVE_HEADER

/*!
 * \file Explosive.hpp
 * \brief Classe Explosive
 * \author Simon ROUSSEAU
 */

#include "../../include/gameEngine/Player.hpp"
#include "../../include/gameEngine/Location.hpp"

namespace PolyBomber {
	/*!
	 * \class Explosive
	 * \brief Classe Explosive
	 */
	class Explosive : public Location {
    protected:
		int range;		/*! Portée de la bombe */
		int player;	/*! Joueur qui possède la bombe */
    public:
		Explosive(const Player& player);
		Explosive(const Location& loc, int player, int range);
		Explosive(const Explosive& expl);
		//opérateur d'affectation
		~Explosive();
		
		/*!
		 * \brief Méthode provoquant l'explosion de l'explosif
		 * 
		 */
		void explode();
		
		const int getRange() const {return this->range;}
		const int getPlayer() const {return this->player;}
	};
}

#endif