#ifndef _MENUMANAGER
#define _MENUMANAGER

/*!
 * \file MenuManager.hpp
 * \brief Classe de gestion du menu
 * \author Maxime GUIHAL
 */

#include <map>

#include "IMenuToMain.hpp"
#include "IMenuToGameInterface.hpp"
#include "TSingleton.hpp"

#include "menu/MainWindow.hpp"
#include "menu/IMenuScreen.hpp"
#include "menu/SMenuConfig.hpp"

namespace PolyBomber
{
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

			/*!
			 * \brief Méthode d'initialisation de la structure de configuration
			 */
			void initMenuConfig();

			MainWindow window; /*!< Fenêtre du programme */
			std::map<EMenuScreen, IMenuScreen*> menuScreens; /*!< Liste des différents menus du jeu */

			SMenuConfig menuConfig; /*!< Configuration des parties */
	};
}

#endif
