#ifndef BOX_HEADER
#define BOX_HEADER

/*!
 * \file Box.hpp
 * \brief Classe Box
 * \author Simon ROUSSEAU
 */

#include "Location.hpp"

#include "DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Box
	 * \brief Classe Box
	 */
	
	class Box : public Location {
		
	public:
		Box(int, int);
		Box(const Box&);
		Box& operator=(Box&);
		~Box();
	};
}

#endif