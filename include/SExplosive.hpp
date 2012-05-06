#ifndef S_EXPLOSIVE _HEADER
#define S_EXPLOSIVE _HEADER

/*!
 * \file SExplosive.hpp
 * \brief Structure de configuration d'un explosif
 * \author Simon Rousseau
 */

/** Includes **/
//Bibliothèque standard
#include <vector>

//Bibliothèque SFML


//Bibliothèque externes


//Headers du projet
#include "./EExplosiveType.hpp"

namespace PolyBomber;

/*!
 * \struct SExplosive
 * \brief Configuration d'un explosif
 * 
 */
struct SExplosive {
  Vector<int> coords;		/*! Coordonnées de l'explosif */
  EExplosiveType type;		/*! Type d'explosif */
};

#endif