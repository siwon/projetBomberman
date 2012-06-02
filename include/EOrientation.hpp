#ifndef E_ORIENTATION_HEADER
#define E_ORIENTATION_HEADER

/*!
 * \file EOrientation.hpp
 * \brief Enumération des orientations
 * \author Simon ROUSSEAU
 */

namespace PolyBomber {
  /*!
  * \enum EOrientation
  * \brief Codes des orientations
  */
  enum EOrientation {
    ORIENTATION_UP =0,		/*!< Vers le haut */
    ORIENTATION_DOWN,		/*!< Vers le bas */
    ORIENTATION_LEFT,		/*!< Vers la gauche */
    ORIENTATION_RIGHT		/*!< Vers la droite */
  };
}

#endif
