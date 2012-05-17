#ifndef EXPLOSIVE_HEADER
#define EXPLOSIVE_HEADER

/*!
 * \file Explosive.hpp
 * \brief Classe Explosive
 * \author Simon ROUSSEAU
 */

namespace PolyBomber {
	/*!
	 * \class Explosive
	 * \brief Classe Explosive
	 */
	class Explosive : public Location {
    protected:
		int range;		/*! Portée de la bombe */
		Player player;	/*! Joueur qui possède la bombe */
    public:
		Explosive(Player player);
		Explosive(Explosive expl);
		//opérateur d'affectation
		~Explosive();
		
		/*!
		 * \brief Méthode provoquant l'explosion de l'explosif
		 * 
		 */
		void explode();
		
		int getRange(){return this->range;}
		Player getPlayer(){return this->player;}
	};
}

#endif