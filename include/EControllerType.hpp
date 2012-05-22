#ifndef _ECONTROLLERTYPE
#define _ECONTROLLERTYPE

/*!
 * \file EControllerType.hpp
 * \brief Enumération des interfaces de jeu
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EControllerType
	 * \brief Interfaces de jeu
	 */
	enum EControllerType
	{
		KEYBOARD=0, /*!< Clavier */
		GAMEPAD, /*!< Joystick, Joypad, etc... */
		WII /*!< Wiimote */
	};
}

#endif
