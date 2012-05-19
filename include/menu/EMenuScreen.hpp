#ifndef _EMENUSCREEN
#define _EMENUSCREEN

/*!
 * \file EMenuScreen.hpp
 * \brief Enumération des menus
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EMenuScreen
	 * \brief Menus du jeu
	 */
	enum EMenuScreen
	{
		SPLASHSCREEN,
		MAINMENU,
		CONFIGMENU,
		GAMEMENU,
		JOINGAMEMENU,
		SELECTSLOTSMENU,
		CREATEGAMEMENU,
		GAMEOPTIONSMENU,
		SELECTNAMEMENU,
		WAITINGMENU,
		CONTROLLERSCONFIGMENU,
		KEYASSIGNMENU,
		SOUNDCONFIGMENU,
		GRAPHICSCONFIGMENU,
		RUNGAME,
		PAUSEMENU,
		SCOREMENU,
		EXIT
	};
}

#endif


