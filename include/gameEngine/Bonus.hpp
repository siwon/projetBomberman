#ifndef BONUS_HEADER
#define BONUS_HEADER

/*!
 * \file Bonus.hpp
 * \brief Classe Bonus
 * \author Simon ROUSSEAU
 */

#include "EGameBonus.hpp"

#include "Location.hpp"

#include "DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Bonus
	 * \brief Classe Bonus
	 */
	class Bonus : public Location {
	protected :
		EGameBonus type;
		bool visible;
		
	public :
		Bonus(int, int, EGameBonus, bool);
		Bonus(const Bonus&);
		//Bonus& operator=(const Bonus&);
		~Bonus();
		
		inline EGameBonus getType() const {return this->type;}
		inline bool isVisible() const {return this->visible;}
		
		inline void setVisible() {this->visible=true;}
	};
}

#endif