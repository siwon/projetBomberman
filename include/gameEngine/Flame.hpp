#ifndef FLAME_HEADER
#define FLAME_HEADER

/*!
 * \file Flame.hpp
 * \brief Classe Flame
 * \author Simon ROUSSEAU
 */

#include "gameEngine/Location.hpp"

#include "EOrientation.hpp"
#include "EFlameLocation.hpp"

#include "gameEngine/DefineAndFunction.hpp"

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
		Flame(float x, float y, EOrientation orientation, EFlameLocation step);
		Flame(const Flame& flamme);
		//operateur d affectation
		~Flame();
		
		EOrientation getOrientation() const {return this->orientation;}
		EFlameLocation getStep() const {return this->step;}
	};
}

#endif