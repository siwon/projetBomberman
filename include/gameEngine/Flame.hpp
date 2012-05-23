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
		int dateDebutFlame;
		
	public:
		Flame(float x, float y, EOrientation orientation, EFlameLocation step, int date);
		Flame(const Flame& flamme);
		//operateur d affectation
		~Flame();
		
		EOrientation getOrientation() const {return this->orientation;}
		EFlameLocation getStep() const {return this->step;}
		int getDateDebutFlame() const {return this->dateDebutFlame;}
		void decalerDebutFlame(int nbSecondes) {this->dateDebutFlame=this->dateDebutFlame+nbSecondes;}
	};
}

#endif