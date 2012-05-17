#ifndef _NETWORKMANAGER
#define _NETWORKMANAGER

/*!
 * \file NetworkManager.hpp
 * \brief gestionnaire réseau
 * \author Brice GUILLERMIC
 */

#include <SFML/Network.hpp>
#include <list>

#include "../SBoard.hpp"
#include "../INetworkToGameInterface.hpp"
#include "../INetworkToGameEngine.hpp"
#include "../INetworkToMenu.hpp"
#include "../IControllerToNetwork.hpp"
#include "../IGameEngineToNetwork.hpp"
#include "../SGameConfig.hpp"
#include "../DataPlayer.hpp"
#include "../SKeyPressed.hpp"
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
			int paused;
			bool started;
			DataPlayer* players;
			std::list<sf::TcpSocket*> clients;
			SBoard board;

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

			//void joinGame(string ip);
			//int getFreeSlots();
			//void setBookedSlots(unsigned int nb);
			//void setPlayerName(string[]);
			//int* getScores();
			bool isStarted();
			//void startGame();
			std::string getIpAddress();
			void setGameConfig(SGameConfig& gameConfig);
			
			SBoard getBoard();
			int isFinished();

			/******méthode ne provenant pas d'interface***/
			sf::IpAddress getIp();
			void createSocket(sf::IpAddress);
			void createServerSocket();
			sf::Packet createPacket(int);
			//void decryptPacket(sf::Packet);
			//void sendPacket(sf::Packet, sf::IpAddress);
			sf::Packet& operator<<(sf::Packet&, const SBoard&);
			sf::Packet& operator<<(sf::Packet&, const SKeyPressed&);
	};
}
#endif
