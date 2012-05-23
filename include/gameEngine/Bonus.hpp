#ifndef BONUS_HEADER
#define BONUS_HEADER

/*!
 * \file Bonus.hpp
 * \brief Classe Bonus
 * \author Simon ROUSSEAU
 */

#include "EGameBonus.hpp"

#include "gameEngine/Location.hpp"

#include "gameEngine/DefineAndFunction.hpp"

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
		Bonus(float x, float y, EGameBonus type, bool visible);
		Bonus(const Bonus& bonus);
		//operateur de recopie
		~Bonus();
		
		EGameBonus getType() const {return this->type;}
		bool isVisible() const {return this->visible;}
		
		void setVisible() {this->visible=true;}
	};
}

#endif