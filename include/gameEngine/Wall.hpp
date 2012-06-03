#ifndef WALL_HEADER
#define WALL_HEADER

/*!
 * \file Wall.hpp
 * \brief Classe Wall
 * \author Simon ROUSSEAU
 */

#include "Location.hpp"

namespace PolyBomber {
	/*!
	 * \class Wall
	 * \brief Classe Wall
	 */
	
	class Wall : public Location {
	public:
		/*!
		 * \brief Constructeur de la classe Wall
		 * \param x : Abscisse du mur (en case)
		 * \param y : Ordonné du mur (en case)
		 */
		Wall(int, int);
		
		/*!
		 * \brief Constructeur par recopie de la classe Wall
		 * \param e : Objet à copier
		 */
		Wall(const Wall&);
		
		/*!
		 * \brief Desctructeur de la classe Wall
		 */
		~Wall();
	};
}

#endif