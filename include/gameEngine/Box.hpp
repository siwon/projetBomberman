#ifndef BOX_HEADER
#define BOX_HEADER

/*!
 * \file Box.hpp
 * \brief Classe Box
 * \author Simon ROUSSEAU
 */

#include "gameEngine/Location.hpp"

namespace PolyBomber {
	/*!
	 * \class Box
	 * \brief Classe Box
	 */
	
	class Box : public Location {
    private:
		bool bonus;
		
		
	public:
		Box(int x, int y, bool bonus);
		Box(const Location& loc, bool bonus);
		Box(const Box& boite);
		//operateur par recopie
		~Box();
		
		const bool getBonus() const {return this->bonus;}
		
		/*!
		 * \brief Methode detruisant une caisse
		 *
		 */
		void broke(); //changement du nom de fonction pour cause de mot reserve
		
		
	};
}

#endif