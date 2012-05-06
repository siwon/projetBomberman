#ifndef LOCATION_HEADER
#define LOCATION_HEADER

/*!
 * \file Location.hpp
 * \brief Classe Location
 * \author Simon Rousseau
 */

namespace PolyBomber;

/*!
 * \class Location
 * \brief Classe Location
 */
class Location {
  protected :
    Board board ;	/*! Plateau de jeu */
    int x;		/*! coordonnée horizontale */
    int y;		/*! coordonnée verticale */
};

#endif