#ifndef _GRAPHICSCONFIGMENU
#define _GRAPHICSCONFIGMENU

/*!
 * \file GraphicsConfigMenu.hpp
 * \brief Classe de gestion de configuration graphique
 * \author Maxime GUIHAL
 */

#include "menu/IMenuScreen.hpp"

namespace PolyBomber
{
	/*!
	 * \class GraphicsConfigMenu
	 * \brief Classe de gestion de configuration graphique
	 */
	class GraphicsConfigMenu : public IMenuScreen
	{
		public:
			GraphicsConfigMenu();
			~GraphicsConfigMenu();
		
			EMenuScreen run(MainWindow& window, EMenuScreen previous);
	};
}

#endif

