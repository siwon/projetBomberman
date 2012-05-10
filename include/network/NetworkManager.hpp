#ifndef _NETWORKMANAGER
#define _NETWORKMANAGER

/*!
 * \file NetworkManager.hpp
 * \brief Classe de gestion du réseau
 * \author Maxime GUIHAL
 */

#include "INetworkToMenu.hpp"
#include "INetworkToGameInterface.hpp"
#include "INetworkToGameEngine.hpp"
#include "TSingleton.hpp"

namespace PolyBomber
{
	/*!
	 * \class NetworkManager
	 * \brief Classe de gestion du réseau
	 */
	class NetworkManager : public INetworkToMenu,
						   public INetworkToGameInterface,
						   public INetworkToGameEngine,
						   public Singleton<NetworkManager>
	{
		friend class Singleton<NetworkManager>;

		public:
			// TODO - A compléter

		private:
			/*!
			 * \brief Constructeur
			 */
			NetworkManager();

			/*!
			 * \brief Destructeur
			 */
			~NetworkManager();
	};
}

#endif
