#ifndef EXPLOSIVE_HEADER
#define EXPLOSIVE_HEADER

/*!
 * \file Explosive.hpp
 * \brief Classe Explosive
 * \author Simon ROUSSEAU
 */

namespace PolyBomber;

/*!
 * \class Explosive
 * \brief Classe Explosive
 */
class Explosive {
  protected :
    int impact;		/*!  */
    int step;		/*!  */
    Place place;	/*!  */
    Player player;	/*! Joueur qui possède la bombe */
  public :
    /*!
     * \brief Méthode provoquant l'explosion de l'explosif
     * 
     */
    void explode();
};

#endif