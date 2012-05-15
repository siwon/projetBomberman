#ifndef _NETWORKMANAGER
#define _NETWORKMANAGER

/*!
 * \file NetworkManager.hpp
 * \brief gestionnaire réseau
 * \author Brice GUILLERMIC
 */

#include <SFML/Network.hpp>

#include "../Sboard.hpp"
#include "../INetworkToGameInterface.hpp"
#include "../INetworkToGameEngine.hpp"
#include "../INetworkToMenu.hpp"
#include "../IControllerToNetwork.hpp"
#include "../IGameEngineToNetwork.hpp"
#include "../SGameConfig.hpp"
#include "../TSingleton.hpp"

namespace PolyBomber
{
	/*!
	 * \class NetworkManager
	 * \brief singleton du gestionnaire réseau
	 */
	class NetworkManager : public INetworkToGameInterface,
		public INetworkToMenu, 
		public INetworkToGameEngine, 
		public Singleton<NetworkManager>
	{
		friend class Singleton<NetworkManager>;
		private:
			SGameConfig gameConfig;
			sf::IpAddress* ip;

			IControllerToNetwork* controller;
			IGameEngineToNetwork* gameEngine;

			/*!
			 * \brief Constructeur
			 */
			NetworkManager();

			/*!
			 * \brief Destructeur
			 */
			~NetworkManager();
		public:
			SKeyPressed getKeysPressed();
			int isPaused();

			void joinGame(string ip);
			int getFreeSlots();
			void setBookedSlots(unsigned int nb);
			void setPlayerName(string[]);
			int* getScores();
			bool isStarted();
			void startGame();
			string getIpAddress();
			void setGameConfig(SGameConfig gameConfig);

			SBoard getBoard();
			int isFinished();
};

#endif
