#ifndef S_EXPLOSIVE _HEADER
#define S_EXPLOSIVE _HEADER

/*!
 * \file SExplosive.hpp
 * \brief Structure de configuration d'un explosif
 * \author Simon Rousseau
 */

/** Includes **/
//Bibliothèque standard


//Bibliothèque SFML
#include <Vector2.hpp>

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
  sf::Vector2<int> coords;	/*! Coordonnées de l'explosif */
  EExplosiveType type;		/*! Type d'explosif */
};

#endif