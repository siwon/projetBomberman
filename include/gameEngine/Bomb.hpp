#ifndef BOMB_HEADER
#define BOMB_HEADER

/*!
 * \file Bomb.hpp
 * \brief Classe Bomb
 * \author Simon ROUSSEAU
 */

namespace PolyBomber {
  /*!
  * \class Bomb
  * \brief Classe Bomb
  */
  class Bomb : public Explosive {
    protected :
      int explosionTime;	/*! Date à laquelle la bombe va exploser */
	public :
	  Bomb();
	  Bomb(Bomb bombe);
	  //opérateur par recopie
	  ~Bomb();
  };
}

#endif