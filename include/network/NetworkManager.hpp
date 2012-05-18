#ifndef _NETWORKMANAGER
#define _NETWORKMANAGER

#define NBNETWORKMAX 4

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
			sf::IpAddress ip[NBNETWORKMAX];
			int nbPlayerByIp[NBNETWORKMAX];
			int paused;
			bool started;
			std::vector<DataPlayer> players;
			std::list<sf::TcpSocket*> clients;
			std::list<sf::Packet> packets; // segment de mémoire partagé
			SBoard board;
			bool server;
			SKeyPressed keyPressed;

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

			void joinGame(std::string ip);
			int getFreeSlots();
			void setBookedSlots(unsigned int nb);
			//void setPlayerName(string[]);
			//int* getScores();
			bool isStarted();
			void startGame();
			std::string getIpAddress();
			void setGameConfig(SGameConfig&);
			
			SBoard getBoard();
			int isFinished();

			/******méthode ne provenant pas d'interface***/
			sf::IpAddress getIp();
			void createServerSocket();
			sf::Packet createPacket(int, int j =0);
			SBoard packetToSBoard(sf::Packet&);
			SKeyPressed packetToSKeyPressed(sf::Packet&);
			sf::TcpSocket& findSocket(sf::IpAddress&);
			std::list<sf::Packet>::iterator waitPacket(int, sf::IpAddress&);
	};

	sf::Packet& operator<<(sf::Packet&, const SBoard&);
	sf::Packet& operator<<(sf::Packet&, const SKeyPressed&);
	sf::Packet& operator>>(sf::Packet&, SBoard&);
	sf::Packet& operator>>(sf::Packet&, SKeyPressed&);
}
#endif
