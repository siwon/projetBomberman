#ifndef EXPLOSIVE_HEADER
#define EXPLOSIVE_HEADER

/*!
 * \file Explosive.hpp
 * \brief Classe Explosive
 * \author Simon ROUSSEAU
 */

#include "Player.hpp"
#include "Location.hpp"

namespace PolyBomber {
	/*!
	 * \class Explosive
	 * \brief Classe Explosive
	 */
	class Explosive : public Location {
    protected:
		int range;		/*! Portee de la bombe */
		int player;		/*! Identifiant du joueur qui possede la bombe */
		
		/*!
		 * \brief Constructeur de la classe Explosive
		 * \param player : Identifiant du joueur qui pose l'explosif
		 * \param range : Portée de l'explosif
		 * \param x : Abscisse de l'explosif (en case)
		 * \param y : Ordonné de l'explosif (en case)
		 */
		Explosive(int, int, int, int);
		
    public:
		/*!
		 * \brief Constructeur de la classe Explosive
		 * \param player : Player qui pose l'explosif
		 */
		Explosive(const Player&);
		
		/*!
		 * \brief Constructeur de la classe Explosive
		 * \param player : Player qui pose l'explosif
		 * \param x : Abscisse de l'explosif (en case)
		 * \param y : Ordonné de l'explosif (en case)
		 */
		Explosive(const Player&, int, int);
		
		/*!
		 * \brief COnstructeur par recopie de la classe Explosive
		 * \param expl : Objet à copier
		 */
		Explosive(const Explosive&);
		
		/*!
		 * \brief Destructeur de la classe Explosive
		 */
		~Explosive();
		
		
		/*!
		 * \brief Retourne la portée de l'explosif
		 * \return Portée de l'explosif (en case)
		 */
		inline int getRange() const {return this->range;}
		
		/*!
		 * \brief Retourne l'identifiant du joueur qui a posé l'explosif
		 * \return Identifiant du joueur qui a posé l'explosif
		 */
		inline int getPlayer() const {return this->player;}
	};
}

#endif