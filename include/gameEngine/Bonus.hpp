#ifndef BONUS_HEADER
#define BONUS_HEADER

/*!
 * \file Bonus.hpp
 * \brief Classe Bonus
 * \author Simon ROUSSEAU
 */

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
		Bonus(Location loc, EGameBonus type);
		Bonus(Bonus bonus);
		//opérateur de recopie
		~Bonus();
		
		EGameBonus getType(){return this->type;}
		bool isVisible(){return this->visible;}
	};
}

#endif