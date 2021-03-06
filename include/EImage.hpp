#ifndef _EIMAGE
#define _EIMAGE

/*!
 * \file EImage.hpp
 * \brief Enumération des images du skin
 * \author Simon ROUSSEAU
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EImage
	 * \brief Codes des images du skin
	 */
	enum EImage
	{
		//MENU
		SPLASH,
		MENU_BACKGROUND,
		WIISCREEN,
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4,
		GAME_BACKGROUND,

		//BONUS
		EIMAGE_VITESSEPLUS,
		EIMAGE_VITESSEMOINS,
		EIMAGE_BOMBLINE,
		EIMAGE_REMOTEBONUS,
		EIMAGE_BOMBPLUS,
		EIMAGE_BOMBMOINS,
		EIMAGE_RANGEPLUS,
		EIMAGE_RANGEMOINS,
		EIMAGE_RANGEMAX,
		EIMAGE_MINEBONUS,		
		EIMAGE_INFINITY,
		EIMAGE_ATOMIC,

		//INFECTION
		EIMAGE_CRANE,
		EIMAGE_HELL,
		EIMAGE_CONFUSION,
		EIMAGE_SPASME,
		EIMAGE_DILATATION,
		EIMAGE_RAGE,
		
		//BOMB
		EIMAGE_MINE,
		EIMAGE_BOMB,
		EIMAGE_REMOTEBOMB,
		
		EIMAGE_BOX,

		//FLAMES
		EIMAGE_FLAME_UP,
		EIMAGE_FLAME_DOWN,
		EIMAGE_FLAME_LEFT,
		EIMAGE_FLAME_RIGHT,
		EIMAGE_FLAME_H,
		EIMAGE_FLAME_V,
		EIMAGE_FLAME_ORIG,
		
		//PLAYER1
		EIMAGE_PLAYER1UP,
		EIMAGE_PLAYER1DOWN,
		EIMAGE_PLAYER1LEFT,
		EIMAGE_PLAYER1RIGHT,
		//PLAYER2
		EIMAGE_PLAYER2UP,
		EIMAGE_PLAYER2DOWN,
		EIMAGE_PLAYER2LEFT,
		EIMAGE_PLAYER2RIGHT,

		//PLAYER3
		EIMAGE_PLAYER3UP,
		EIMAGE_PLAYER3DOWN,
		EIMAGE_PLAYER3LEFT,
		EIMAGE_PLAYER3RIGHT,

		//PLAYER4
		EIMAGE_PLAYER4UP,
		EIMAGE_PLAYER4DOWN,
		EIMAGE_PLAYER4LEFT,
		EIMAGE_PLAYER4RIGHT
	};
}

#endif


