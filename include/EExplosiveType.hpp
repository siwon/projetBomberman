#ifndef E_EXPLOSIVE_TYPE_HEADER
#define E_EXPLOSIVE_TYPE_HEADER

/*!
 * \file EExplosiveType.hpp
 * \brief Enumération des types d'explosifs
 * \author Simon Rousseau
 */

namespace PolyBomber;

/*!
 * \enum EExplosiveType
 * \brief Enumération des types d'explosifs
 */
enum EExplosiveType {
  MINE,		/*! Mine */
  BOMB,		/*! Bombe */
  REMOTE	/*! Bombe télécommandée */
};

#endif