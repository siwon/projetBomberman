#ifndef _MENUMANAGER
#define _MENUMANAGER

/*!
 * \file MenuManager.hpp
 * \brief Classe de gestion du menu
 * \author Maxime GUIHAL
 */

#include <vector>

#include "IMenuToMain.hpp"
#include "IMenuToGameInterface.hpp"
#include "TSingleton.hpp"

#include "menu/MenuResources.hpp"
#include "menu/IMenuScreen.hpp"

namespace PolyBomber
{
	class PolyBomberApp;
	/*!
	 * \class MenuManager
	 * \brief Classe de gestion du menu
	 */
	class MenuManager : public IMenuToMain,
						public IMenuToGameInterface,
						public Singleton<MenuManager>
	{
		friend class Singleton<MenuManager>;

		public:
			/*!
			 * \see IMenuToMain::run
			 */
			EScreenSignal run();

			/*!
			 * \see IMenuToGameInterface::runPause
			 */
			EScreenSignal runPause(unsigned int player);

		private:
			/*!
			 * \brief Constructeur
			 */
			MenuManager();

			/*!
			 * \brief Destructeur
			 */
			~MenuManager();

			MenuResources menuResources; /*!< Interfaces avec les autres composants et conteneur de la fenêtre */
			std::vector<IMenuScreen*> menuScreens; /*!< Liste des différents menus du jeu */
	};
}

#endif
