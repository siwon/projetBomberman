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
		Wall(int, int);
		Wall(const Wall&);
		Wall& operator=(Wall&);
		~Wall();
	};
}

#endif