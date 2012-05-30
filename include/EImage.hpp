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
		BOMB,
		INFINITYBOMB,
		MINE,
		REMOTEBOMB,

		//BONUS
		BOMBPLUS,
		BOMBMOINS,
		VITESSEPLUS,
		VITESSEMOINS,
		RANGEPLUS,
		RANGEMOINS,
		RANGEMAX,
		
		ATOMIC,
		BOMBLINE,
		INFINITY,
		MINEBONUS,
		REMOTEBONUS,
		
		//INFECTION
		CONFUSION,
		CRANE,
		DILATATION,
		HELL,
		RAGE,
		SPASME
	};
}

#endif


