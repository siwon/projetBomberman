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
		SPEEDUP=0, /*!< Acceleration du joueur */
		SPEEDDOWN, 
		BOMBLINE, //bonus de bombe
		DETONATOR,
		BOMBUP,
		BOMBDOWN,
		RANGEUP,
		RANGEDOWN,
		RANGEUPMAX,
		/*bonus de bombe*/
		MINE,
		INFINITYBOMB,
		ATOMICBOMB,
		/*infection*/
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


