#ifndef _EIMAGE
#define _EIMAGE

/*!
 * \file EImage.hpp
 * \brief Enumération des images du skin
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EImage
	 * \brief Codes des images du skin
	 */
	enum EImage
	{
		SPLASH, /*!< Ecran d'accueil du programme */
		MENU_BACKGROUND, /*!< Fond du menu */
		WIISCREEN, /*!< Ecran recherche des wiimotes */
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4,
		GAME_BACKGROUND, /*!< Fond du jeu */
		BOX, /*!< Caisse destructible */
		
		//BOMB
		EIMAGE_BOMB,
		EIMAGE_INFINITYBOMB,
		EIMAGE_MINE,
		EIMAGE_REMOTEBOMB,

		//BONUS
		EIMAGE_BOMBPLUS,
		EIMAGE_BOMBMOINS,
		EIMAGE_VITESSEPLUS,
		EIMAGE_VITESSEMOINS,
		EIMAGE_RANGEPLUS,
		EIMAGE_RANGEMOINS,
		EIMAGE_RANGEMAX,
		
		EIMAGE_ATOMIC,
		EIMAGE_BOMBLINE,
		EIMAGE_INFINITY,
		EIMAGE_MINEBONUS,
		EIMAGE_REMOTEBONUS,
		
		//INFECTION
		EIMAGE_CONFUSION,
		EIMAGE_CRANE,
		EIMAGE_DILATATION,
		EIMAGE_HELL,
		EIMAGE_RAGE,
		EIMAGE_SPASME
	};
}

#endif


