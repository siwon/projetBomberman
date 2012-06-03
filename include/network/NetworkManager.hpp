#ifndef _NETWORKMANAGER
#define _NETWORKMANAGER

/*!
 * \file NetworkManager.hpp
 * \brief gestionnaire rÃ©seau
 * \author Brice GUILLERMIC
 */

#include <list>

#include <SFML/Network.hpp>

#include "SBoard.hpp"
#include "INetworkToGameInterface.hpp"
#include "INetworkToGameEngine.hpp"
#include "INetworkToMenu.hpp"
#include "IControllerToNetwork.hpp"
#include "IGameEngineToNetwork.hpp"
#include "SGameConfig.hpp"
#include "network/DataPlayer.hpp"
#include "SKeyPressed.hpp"
#include "TSingleton.hpp"

namespace PolyBomber
{
	/*!
	 * \class NetworkManager
	 * \brief singleton du gestionnaire rÃ©seau
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
			int paused;
			bool started;
			bool connect;
			std::vector<DataPlayer> players;
			std::vector<sf::TcpSocket*> clients;//segment de mémoire partagé
			std::list<sf::Packet> packets; // segment de mémoire partagé
			bool server;
			bool deconnect;
			sf::SocketSelector selector; // le selecteur pour le serveur
			SKeyPressed keyPressed;

			// Threads
			sf::Thread* threadServer;
			sf::Thread* threadClient;
			sf::Thread* threadRun;

			// Interfaces
			IControllerToNetwork* controller;
			IGameEngineToNetwork* gameEngine;

			// Mutex
			sf::Mutex mutexPacket;
			sf::Mutex mutexClients;
			sf::Mutex mutexSlots;
			sf::Mutex mutexNames;
			sf::Mutex mutexConnect;
			sf::Mutex mutexDeconnect;
			sf::Mutex mutexPause;

			/*!
			 * \brief Constructeur
			 */
			NetworkManager();
			
			/*!
			 * \brief Destructeur
			 */
			~NetworkManager();
			
			/*!
			 * \brief initialise les attributs de la classe
			 */
			void initialize();
			
			/*!
<<<<<<< HEAD
			 * \brief envoie un paquet et attent un paquet de rÃ©ponse
			 * \param entier : type du paquet qui est Ã  envoyer
			 * \return un iterateur sur la liste de packets
=======
			 * \brief envoie un paquet et attent un paquet de réponse
			 * \param entier : type du paquet qui est à envoyer
			 * \return un iterateur sur un paquet qui est la réponse à la question
>>>>>>> f5bbc5bc779ed35226a94bce61c8c7788880f50c
			 */
			std::list<sf::Packet>::iterator askServer(int);
			
			/*!
			 * \brief demande synchronisÃ©e si le jeu est connectÃ© Ã  un ordinateur distant 
			 * \return vrai s'il y a connexion a un ordinateur
			 * 	faux sinon
			 */
			bool isConnected();
			
			/*!
			 * \brief remplit l'attribut connect en mode synchronisÃ©
			 * \param boolÃ©en : fournit l'Ã©tat de la connexion
			 */
			void setConnect(bool);
			
			/*!
			 * \brief remplit l'attribut pause en mode synchronisÃ©
			 * \param entier : fournit le numÃ©ro du joueur en pause
			 * zÃ©ro s'il n'y a pas de pause
			 */
			void setPause(int);
			
			/*!
			 * \brief ajout de socket en mode synchronisÃ© Ã  l'attribut clients
			 * \param pointeur vers un socket tcp : socket Ã  ajouter Ã  la collection
			 */
			void addSocket(sf::TcpSocket*);
			
			/*!
			 * \brief supprime un socket en mode synchronisÃ© de l'attribut clients
			 * \param adresse ip : adresse ip du client Ã  retirer de la collection
			 */
			void eraseSocket(sf::IpAddress&);
			
			/*!
			 * \brief initialisÃ© le seleteur de socket pour le serveur et gÃ¨re la rÃ©ception de packet
			 * cette mÃ©thode est appelÃ©e dans un thread
			 */
			void createServerSocket();
			
			/*!
			 * \brief initialise la connexion avec un serveur pour le client
			 * cette mÃ©thode est appelÃ©e dans un thread
			 */
			void listenToServer();
			
			/*!
			 * \brief supprime en mode synchronisÃ© des joueurs de l'attribut players
			 * \param adresse ip : adresse ip du joueur Ã  supprimer de la collection
			 */
			void deletePlayer(sf::IpAddress&);
			
			/*!
			 * \brief crÃ©er un packet avec son type et l'ip de l'Ã©meteur
			 * \param entier : numÃ©ro du type de paquet Ã  construire
			 * \param entier : utilisÃ© pour rÃ©server un nombre j de slots
			 * \return un paquet prÃ¨s Ã  Ãªtre envoyÃ©
			 */
			sf::Packet createPacket(int, int j =0);
			
			/*!
			 * \brief recherche un socket vers un ordinateur distant
			 * \param adresse ip : adresse du socket Ã  rechercher
			 * \return un pointeur vers le socket contenu dans l'attribut clients
			 */
			sf::TcpSocket* findSocket(sf::IpAddress&);
			
			/*!
			 * \brief recherche un socket vers un ordinateur distant
			 * \param adresse ip : adresse du socket Ã  rechercher
			 * \return un iterateur vers le socket contenu dans l'attribut clients
			 */
			std::vector<sf::TcpSocket*>::iterator findSocketIterator(sf::IpAddress&);
			
			/*!
			 * \brief recherche et attend la rÃ©ponse Ã  un paquet envoyÃ© pendant 0.1 seconde maximum
			 * \param entier : type du paquet Ã  attendre
			 * \param adresse ip : adresse de l'Ã©metteur du paquet
			 * \return un iterateur vers le paquet contenu dans l'attribut packets
			 */
			std::list<sf::Packet>::iterator waitPacket(int, sf::IpAddress&);
			
			/*!
			 * \brief dÃ©crypte les paquets rÃ©ceptionnÃ©s
			 * \param paquet : le paquet Ã  dÃ©crypter
			 */
			void decryptPacket(sf::Packet&);
			
			/*!
			 * \brief permet d'afficher l'Ã©tat de la classe Ã  un moment donnÃ©
			 */
			void etatNetwork();
			
			/*!
			 * \brief permet de rÃ©server des slots disponibles
			 * \param entier non signÃ© : nombre de slots Ã  rÃ©server
			 * \param adresse ip : par dÃ©faut l'adresse ip de l'ordinateur des joueurs qui rÃ©servent les slots
			 */
			void setSlot(unsigned int nb, sf::IpAddress ip = sf::IpAddress::getLocalAddress());
			
			/*!
			 * \brief permet d'enregistrer le nom de joueurs
			 * \param tableau de chaines de caractÃ¨res : contient les nom Ã  enregistrer
			 * \param adresse ip : par dÃ©faut l'adresse ip de l'ordinateur des joueurs qui enregistrent leur nom
			 */
			void setName(std::string names[4], sf::IpAddress ip = sf::IpAddress::getLocalAddress());
			
			/*!
			 * \brief permet de rÃ©server des slots disponibles
			 * \return vrai si le serveur est deconnectÃ©,
			 * faux sinon
			 */
			bool isDeconnected();
			
			/*!
			 * \brief permet d'attribuer une valeur Ã  l'attribut deconnect de faÃ§on synchronisÃ©e
			 */
			void setDeconnected(bool);

			
		public:
			/*!
			 * \see INetworkToGameEngine::isPaused
			 */
			SKeyPressed getKeysPressed();
			
			/*!
			 * \see INetworkToGameEngine::isPaused
			 */
			int isPaused();
			
			/*!
			 * \see IGameEngineToGameInterface::resume
			 */
			void resume();
			
			/*!
			 * \see INetworkToMenu::cancel
			 */
			void cancel();
			
			/*!
			 * \see INetworkToMenu::joinGame
			 */
			void joinGame(std::string ip);
			
			/*!
			 * \see INetworkToMenu::getFreeSlots
			 */
			int getFreeSlots();
			
			/*!
			 * \see INetworkToMenu::setBookedSlots
			 */
			void setBookedSlots(unsigned int nb);
			
			/*!
			 * \see INetworkToMenu::setPlayerName
			 */
			void setPlayerName(std::string names[4]);
			
			/*!
			 * \see INetworkToMenu::getPlayersName
			 */
			void getPlayersName(std::string names[4]);
			
			/*!
			 * \see INetworkToMenu::isStarted
			 */
			bool isStarted();
			
			/*!
			 * \see INetworkToMenu::startGame
			 */
			void startGame();
			
			/*!
			 * \see INetworkToMenu::getIpAddress
			 */
			std::string getIpAddress();
			
			/*!
			 * \see INetworkToMenu::setGameConfig
			 */
			void setGameConfig(SGameConfig&);
			
			/*!
			 * \see IGameEngineToGameInterface::getBoard
			 */
			SBoard getBoard();
			
			/*!
			 * \see IGameEngineToGameInterface::isFinished
			 */
			int isFinished();
			
	};

	sf::Packet& operator<<(sf::Packet&, SBoard&);
	sf::Packet& operator<<(sf::Packet&, SKeyPressed&);
	sf::Packet& operator>>(sf::Packet&, SBoard&);
	sf::Packet& operator>>(sf::Packet&, SKeyPressed&);

}
#endif
