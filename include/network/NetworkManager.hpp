#ifndef _NETWORKMANAGER
#define _NETWORKMANAGER

/*!
 * \file NetworkManager.hpp
 * \brief gestionnaire r�seau
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
#include "DataPlayer.hpp"
#include "../SKeyPressed.hpp"
#include "../TSingleton.hpp"

namespace PolyBomber
{
	/*!
	 * \class NetworkManager
	 * \brief singleton du gestionnaire r�seau
	 */
	class  NetworkManager : public INetworkToGameInterface,
		public INetworkToMenu, 
		public INetworkToGameEngine, 
		public Singleton<NetworkManager>
	{
		friend class Singleton<NetworkManager>;
		private:
			SGameConfig gameConfig;
			sf::IpAddress ip[4];
			int nbPlayerByIp[4];
			int scores[4];
			int paused;
			bool started;
			std::vector<DataPlayer> players;
			std::list<sf::TcpSocket*> clients;//ME
			std::list<sf::Packet> packets; // segment de m�moire partag�
			bool server;
			SKeyPressed keyPressed;

			IControllerToNetwork* controller;
			IGameEngineToNetwork* gameEngine;

			sf::Mutex mutexPacket;
			sf::Mutex mutexClients;

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
			void setBookedSlots(unsigned int nb, sf::IpAddress ip = sf::IpAddress::getLocalAddress());
			void setPlayerName(std::string names[4], sf::IpAddress ip = sf::IpAddress::getLocalAddress());
			int* getScores();
			bool isStarted();
			void startGame();
			std::string getIpAddress();
			void setGameConfig(SGameConfig&);
			SBoard getBoard();
			int isFinished();

			/******m�thode ne provenant pas d'interface***/
			void createServerSocket();
			void listenToServer();
			sf::Packet createPacket(int, int j =0);
			sf::TcpSocket& findSocket(sf::IpAddress&);
			std::list<sf::Packet>::iterator waitPacket(int, sf::IpAddress&);
			void decryptPacket(sf::Packet&);
			
	};

	sf::Packet& operator<<(sf::Packet&, SBoard&);
	sf::Packet& operator<<(sf::Packet&, SKeyPressed&);
	sf::Packet& operator>>(sf::Packet&, SBoard&);
	sf::Packet& operator>>(sf::Packet&, SKeyPressed&);

}
#endif
