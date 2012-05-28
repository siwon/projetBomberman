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
#include "../network/DataPlayer.hpp"
#include "../SKeyPressed.hpp"
#include "../TSingleton.hpp"

namespace PolyBomber
{
	/*!
	 * \class NetworkManager
	 * \brief singleton du gestionnaire réseau
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
			bool connect;
			std::vector<DataPlayer> players;
			std::vector<sf::TcpSocket*> clients;//ME
			std::list<sf::Packet> packets; // segment de mémoire partagé
			bool server;
			SKeyPressed keyPressed;
			sf::Thread* threadServer;
			sf::Thread* threadClient;
			sf::Thread* threadRun;

			IControllerToNetwork* controller;
			IGameEngineToNetwork* gameEngine;

			sf::Mutex mutexPacket;
			sf::Mutex mutexClients;
			sf::Mutex mutexSlots;
			sf::Mutex mutexNames;
			sf::Mutex mutexConnect;
			sf::Mutex mutexPause;

			/*!
			 * \brief Constructeur
			 */
			NetworkManager();
			/*!
			 * \brief Destructeur
			 */
			~NetworkManager();
			/******méthode ne provenant pas d'interface***/
			void initialize();
			std::list<sf::Packet>::iterator askServer(int);
			bool isConnected();
			void eraseSocket(sf::IpAddress&);
			void createServerSocket();
			void listenToServer();
			sf::Packet createPacket(int, int j =0);
			sf::TcpSocket* findSocket(sf::IpAddress&);
			std::vector<sf::TcpSocket*>::iterator findSocketIterator(sf::IpAddress&);
			std::list<sf::Packet>::iterator waitPacket(int, sf::IpAddress&);
			void decryptPacket(sf::Packet&);

			
public:
			SKeyPressed getKeysPressed();
			int isPaused();
			void resume();
			void cancel();
			void joinGame(std::string ip);
			int getFreeSlots();
			void setBookedSlots(unsigned int nb);
			void setSlot(unsigned int nb, sf::IpAddress ip = sf::IpAddress::getLocalAddress());
			void setPlayerName(std::string names[4]);
			void setName(std::string names[4], sf::IpAddress ip = sf::IpAddress::getLocalAddress());
			void getName(std::string names[4]);
			int* getScores();
			bool isStarted();
			void startGame();
			std::string getIpAddress();
			void setGameConfig(SGameConfig&);
			SBoard getBoard();
			int isFinished();
			
	};

	sf::Packet& operator<<(sf::Packet&, SBoard&);
	sf::Packet& operator<<(sf::Packet&, SKeyPressed&);
	sf::Packet& operator>>(sf::Packet&, SBoard&);
	sf::Packet& operator>>(sf::Packet&, SKeyPressed&);

}
#endif
