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
      
	  
	public :
	  Bonus();
	  Bonus(Cell cell);
	  //opérateur de recopie
	  ~Bonus();
  };
}

#endif