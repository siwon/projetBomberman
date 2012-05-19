#ifndef BOX_HEADER
#define BOX_HEADER

/*!
 * \file Box.hpp
 * \brief Classe Box
 * \author Simon ROUSSEAU
 */

#include "gameEngine/Location.hpp"

#include "gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Box
	 * \brief Classe Box
	 */
	
	class Box : public Location {
    private:
		bool bonus;
		
	public:
		Box(float x, float y, bool bonus);
		Box(const Box& boite);
		//operateur par recopie
		~Box();
		
		bool getBonus() const {return this->bonus;}
		
	};
}

#endif