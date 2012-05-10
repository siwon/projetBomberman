#ifndef _GAMEINTERFACEMANAGER
#define _GAMEINTERFACEMANAGER

/*!
 * \file GameInterfaceManager.hpp
 * \brief Classe de gestion de l'interface du plateau de jeu
 * \author Maxime GUIHAL
 */

#include "IGameInterfaceToMenu.hpp"
#include "TSingleton.hpp"

namespace PolyBomber
{
	/*!
	 * \class NetworkManager
	 * \brief Classe de gestion de l'interface du plateau de jeu
	 */
	class GameInterfaceManager : public IGameInterfaceToMenu,
						         public Singleton<GameInterfaceManager>
	{
		friend class Singleton<GameInterfaceManager>;

		public:
			// TODO - A compléter

		private:
			/*!
			 * \brief Constructeur
			 */
			GameInterfaceManager();

			/*!
			 * \brief Destructeur
			 */
			~GameInterfaceManager();
	};
}

#endif

