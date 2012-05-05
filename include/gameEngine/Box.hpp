#ifndef BOX_HEADER
#define BOX_HEADER

/*!
 * \file Box.hpp
 * \brief Classe Box
 * \author Simon ROUSSEAU
 */

namespace PolyBomber;

/*!
 * \class Box
 * \brief Classe Box
 */

class Box : public Cell {
  public :
    /*!
     * \brief Méthode detruisant une caisse
     *
     */
    void break();
};

#endif