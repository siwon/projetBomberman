#ifndef _EGAMEBONUS
#define _EGAMEBONUS

/*!
 * \file EGameBonus.hpp
 * \brief Enumération des bonus du jeu
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
		SPEEDUP, /*!< Accélération du joueur */
		SPEEDDOWN, 
		BOMBLINE,
		DETONATOR,
		BOMBUP,
		BOMBDOWN,
		RANGEUP,
		RANGEDOWN,
		RANGEUPMAX,
		MINE,
		INITYBOMB,
		ATOMICBOMB,
		CRANE,
		HELL,
		CONFUSION,
		SPASME,
		DILATATION,
		RAGE
		
		TODO : À commenter
	};
}

#endif


