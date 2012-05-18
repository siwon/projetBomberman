#ifndef FLAME_HEADER
#define FLAME_HEADER

/*!
 * \file Flame.hpp
 * \brief Classe Flame
 * \author Simon ROUSSEAU
 */

#include "../../include/EOrientation.hpp"
#include "../../include/EFlameLocation.hpp"
#include "../../include/gameEngine/Location.hpp"

namespace PolyBomber {
	/*!
	 * \class Flame
	 * \brief Classe Flame
	 */
	
	class Flame : public Location {
	private:
		EOrientation orientation;
		EFlameLocation step;
	public:
		Flame(int x, int y, EOrientation orientation, EFlameLocation step);
		Flame(const Location& loc, EOrientation orientation, EFlameLocation step);
		Flame(const Flame& flamme);
		//opérateur d'affectation
		~Flame();
		
		const EOrientation getOrientation() const {return this->orientation;}
		const EFlameLocation getStep() const {return this->step;}
	};
}

#endif