#ifndef _IMENUSCREEN
#define _IMENUSCREEN

/*!
 * \file IMenuScreen.hpp
 * \brief Interface des ecrans du menu
 * \author Maxime GUIHAL
 */

#include "menu/EMenuScreen.hpp"
#include "menu/MenuResources.hpp"

namespace PolyBomber
{
	/*!
	 * \class IMenuScreen
	 * \brief Interface des ecrans du menu
	 */
	class IMenuScreen
	{
		public:
			virtual EMenuScreen run(MenuResources& resources, EMenuScreen previous) = 0;
	};
}

#endif




