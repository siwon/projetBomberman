#ifndef E_FLAME_LOCATION_HEADER
#define E_FLAME_LOCATION_HEADER

/*!
 * \file EFlameLocation.hpp
 * \brief Enumération des différents types de flammes
 * \author Simon ROUSSEAU
 */

namespace PolyBomber {
  /*!
  * \enum EFlameLocation
  * \brief Enumération des différents types de flammes
  */
  enum EFlameLocation {
    ORIGIN,	/*! Origine de la flamme */
    MIDDLE,	/*! Milieu de la flamme */
    END		/*! Fin de la flamme */
  };
}

#endif