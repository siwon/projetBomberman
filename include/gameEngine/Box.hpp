#ifndef BOX_HEADER
#define BOX_HEADER

/*!
 * \file Box.hpp
 * \brief Classe Box
 * \author Simon ROUSSEAU
 */

#include "Location.hpp"

namespace PolyBomber {
	/*!
	 * \class Box
	 * \brief Classe Box
	 */
	
	class Box : public Location {
		
	public:
		/*!
		 * \brief Constructeur de la classe Box
		 * \param x : Abscisse de la caisse (en case)
		 * \param y : Ordonné de la caisse (en case)
		 */
		Box(int, int);
		
		/*!
		 * \brief Constructeur par recopie de la classe Box
		 * \param boite : Caisse à recopier
		 */
		Box(const Box&);
		
		/*!
		 * \brief Destructeur de la classe Box
		 */
		~Box();
	};
}

#endif