#ifndef WALL_HEADER
#define WALL_HEADER

/*!
 * \file Wall.hpp
 * \brief Classe Wall
 * \author Simon ROUSSEAU
 */

#include "gameEngine/Location.hpp"

namespace PolyBomber {
	/*!
	 * \class Wall
	 * \brief Classe Wall
	 */
	
	class Wall : public Location {
	public:
		Wall(int x, int y);
		Wall(const Location& loc);
		Wall(const Wall& e);
		//operateur d affectation
		~Wall();
	};
}

#endif