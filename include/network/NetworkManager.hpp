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
#include "../network/DataPlayer.hpp"
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
			bool connect;
			std::vector<DataPlayer> players;
			std::vector<sf::TcpSocket*> clients;//ME
			std::list<sf::Packet> packets; // segment de m�moire partag�
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

			/*!
			 * \brief Constructeur
			 */
			NetworkManager();
			/*!
			 * \brief Destructeur
			 */
			~NetworkManager();
			void initialize();
			std::list<sf::Packet>::iterator askServer(int);
			bool isConnected();
			void erasePlayer(std::string);
			
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
			std::string getName();
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
			sf::TcpSocket* findSocket(sf::IpAddress&);
			std::list<sf::Packet>::iterator waitPacket(int, sf::IpAddress&);
			void decryptPacket(sf::Packet&);
			
	};

	sf::Packet& operator<<(sf::Packet&, SBoard&);
	sf::Packet& operator<<(sf::Packet&, SKeyPressed&);
	sf::Packet& operator>>(sf::Packet&, SBoard&);
	sf::Packet& operator>>(sf::Packet&, SKeyPressed&);

}
#endif
