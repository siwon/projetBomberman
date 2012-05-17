#ifndef LOCATION_HEADER
#define LOCATION_HEADER

/*!
 * \file Location.hpp
 * \brief Classe Location
 * \author Simon Rousseau
 */

namespace PolyBomber {
  /*!
  * \class Location
  * \brief Classe Location
  */
  class Location {
    protected :
      Board board ;	/*! Plateau de jeu */
      int x;		/*! coordonnée horizontale avec 0 à gauche*/
      int y;		/*! coordonnée verticale avec 0 en haut */
	  
	  Location();
	  Location(Location loc);
	  //opérateur d'affectation
	  ~Location();
  };
}

#endif