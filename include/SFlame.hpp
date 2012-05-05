#ifndef S_FLAME_HEADER
#define S_FLAME_HEADER

/*!
 * \file SFlame.hpp
 * \brief Structure de configuration d'une déflagration
 * \author Simon Rousseau
 */

/** Includes **/
//Bibliothèque standard
#include <vector>

//Bibliothèque SFML


//Bibliothèque externes


//Headers du projet
#include "./EOrientation.hpp"
#include "./EFlameLocation.hpp"

namespace PolyBomber;

/*!
 * \struct SFlame
 * \brief Configuration d'une déflagration
 * 
 */
struct SFlame {
  Vector<int> coords;		/*! Coordonnées de la déflagration */
  EOrientation orientation;	/*! Orientation de la déflagration */
  unsigned int step;		/*!  */
  EFlameLocation location;	/*!  */
};

#endif