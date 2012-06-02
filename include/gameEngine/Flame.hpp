#ifndef FLAME_HEADER
#define FLAME_HEADER

/*!
 * \file Flame.hpp
 * \brief Classe Flame
 * \author Simon ROUSSEAU
 */

#include "Location.hpp"

#include "EOrientation.hpp"
#include "EFlameLocation.hpp"

#include "DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Flame
	 * \brief Classe Flame
	 */
	
	class Flame : public Location {
	private:
		EOrientation orientation;
		EFlameLocation flameLocation;
		int dateDebutFlame;
		
	public:
		Flame(int, int, EOrientation, EFlameLocation, int);
		Flame(const Flame&);
		//Flame& operator=(Flame&);
		~Flame();
		
		inline EOrientation getOrientation() const {return this->orientation;}
		inline EFlameLocation getFlameLocation() const {return this->flameLocation;}
		inline int getDateDebutFlame() const {return this->dateDebutFlame;}
		inline void decalerDebutFlame(int nbSecondes) {this->dateDebutFlame=this->dateDebutFlame+nbSecondes;}
	};
}

#endif