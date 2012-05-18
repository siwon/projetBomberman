#ifndef BONUS_HEADER
#define BONUS_HEADER

/*!
 * \file Bonus.hpp
 * \brief Classe Bonus
 * \author Simon ROUSSEAU
 */

#include "../../include/EGameBonus.hpp"
#include "../../include/gameEngine/Location.hpp"

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
		Bonus(int x, int y, EGameBonus type);
		Bonus(const Location& loc, EGameBonus type);
		Bonus(const Bonus& bonus);
		//opérateur de recopie
		~Bonus();
		
		const EGameBonus getType() const {return this->type;}
		const bool isVisible() const {return this->visible;}
	};
}

#endif