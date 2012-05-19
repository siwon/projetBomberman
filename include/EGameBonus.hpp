#ifndef _EGAMEBONUS
#define _EGAMEBONUS

/*!
 * \file EGameBonus.hpp
 * \brief Enumeration des bonus du jeu
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EGameBonus
	 * \brief Liste des bonus du jeu
	 */
	enum EGameBonus
	{
		SPEEDUP, /*!< Acceleration du joueur */
		SPEEDDOWN, 
		BOMBLINE,
		DETONATOR,
		BOMBUP,
		BOMBDOWN,
		RANGEUP,
		RANGEDOWN,
		RANGEUPMAX,
		MINE,
		INFINITYBOMB,
		ATOMICBOMB,
		CRANE,
		HELL,
		CONFUSION,
		SPASME,
		DILATATION,
		RAGE
		
		//TODO : a commenter
	};
}

#endif


