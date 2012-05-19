#ifndef E_EXPLOSIVE_TYPE_HEADER
#define E_EXPLOSIVE_TYPE_HEADER

/*!
 * \file EExplosiveType.hpp
 * \brief Enumeration des types d explosifs
 * \author Simon Rousseau
 */

namespace PolyBomber {
  /*!
  * \enum EExplosiveType
  * \brief Enumeration des types d explosifs
  */
  enum EExplosiveType {
    EXPLOSIVE_MINE,		/*! Mine */
    EXPLOSIVE_BOMB,		/*! Bombe */
    EXPLOSIVE_REMOTE	/*! Bombe telecommandee */
  };
}

#endif