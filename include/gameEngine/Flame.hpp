#ifndef FLAME_HEADER
#define FLAME_HEADER

/*!
 * \file Flame.hpp
 * \brief Classe Flame
 * \author Simon ROUSSEAU
 */

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
		Flame(Location loc, EOrientation orientation, EFlameLocation step);
		Flame(Flame flamme);
		//opérateur d'affectation
		~Flame();
		
		EOrientation getOrientation(){return this->orientation;}
		EFlameLocation getStep(){return this->step;}
	};
}

#endif