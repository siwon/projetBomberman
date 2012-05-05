#ifndef PLACE_HEADER
#define PLACE_HEADER

/*!
 * \file Place.hpp
 * \brief Classe Place
 * \author Simon ROUSSEAU
 */

namespace PolyBomber;

/*!
 * \class Place
 * \brief Classe Place
 */

class Place : public Cell {
  public :
    /*!
     * \brief Méthode déterminant si une cellule est libre
     *
     * \return TRUE si la case est libre, FALSE sinon.
     */
    bool canEnter();
};

#endif