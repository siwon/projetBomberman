#ifndef _NETWORKMANAGER
#define _NETWORKMANAGER

/*!
 * \file NetworkManager.hpp
 * \brief gestionnaire réseau
 * \author Brice GUILLERMIC
 */

#include <SFML/Network.hpp>

#include "Sboard.hpp"
#include "INetworkToGameInterface.hpp"
#include "INetworkToGameEngine.hpp"
#include "INetworkToMenu.hpp"
#include "SGameConfig.hpp"

namespace PolyBomber
{
	/*!
	 * \class NetworkManager
	 * \brief singleton du gestionnaire réseau
	 */
	class NetworkManager : public INetworkToGameInterface, public INetworkToMenu, public INetworkToGameEngine
	{
		private:
			SGameConfig gameConfig;
			sf::IpAddress[4] ip;
		public:
			
};

#endif
