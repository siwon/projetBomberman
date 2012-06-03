#ifndef _NETWORKMANAGER
#define _NETWORKMANAGER

/*!
 * \file NetworkManager.hpp
 * \brief gestionnaire r�seau
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
			int paused;
			bool started;
			bool connect;
			std::vector<DataPlayer> players;
			std::vector<sf::TcpSocket*> clients;//segment de m�moire partag�
			std::list<sf::Packet> packets; // segment de m�moire partag�
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
			 * \brief envoie un paquet et attent un paquet de r�ponse
			 * \param entier : type du paquet qui est � envoyer
			 * \return un iterateur sur un paquet qui est la r�ponse � la question
			 */
			std::list<sf::Packet>::iterator askServer(int);
			
			/*!
			 * \brief demande synchronis�e si le jeu est connect� � un ordinateur distant 
			 * \return vrai s'il y a connexion a un ordinateur
			 * 	faux sinon
			 */
			bool isConnected();
			
			/*!
			 * \brief remplit l'attribut connect en mode synchronis�
			 * \param bool�en : fournit l'�tat de la connexion
			 */
			void setConnect(bool);
			
			/*!
			 * \brief remplit l'attribut pause en mode synchronis�
			 * \param entier : fournit le num�ro du joueur en pause
			 * z�ro s'il n'y a pas de pause
			 */
			void setPause(int);
			
			/*!
			 * \brief ajout de socket en mode synchronis� � l'attribut clients
			 * \param pointeur vers un socket tcp : socket � ajouter � la collection
			 */
			void addSocket(sf::TcpSocket*);
			
			/*!
			 * \brief supprime un socket en mode synchronis� de l'attribut clients
			 * \param adresse ip : adresse ip du client � retirer de la collection
			 */
			void eraseSocket(sf::IpAddress&);
			
			/*!
			 * \brief initialis� le seleteur de socket pour le serveur et g�re la r�ception de packet
			 * cette m�thode est appel�e dans un thread
			 */
			void createServerSocket();
			
			/*!
			 * \brief initialise la connexion avec un serveur pour le client
			 * cette m�thode est appel�e dans un thread
			 */
			void listenToServer();
			
			/*!
			 * \brief supprime en mode synchronis� des joueurs de l'attribut players
			 * \param adresse ip : adresse ip du joueur � supprimer de la collection
			 */
			void deletePlayer(sf::IpAddress&);
			
			/*!
			 * \brief cr�er un packet avec son type et l'ip de l'�meteur
			 * \param entier : num�ro du type de paquet � construire
			 * \param entier : utilis� pour r�server un nombre j de slots
			 * \return un paquet pr�s � �tre envoy�
			 */
			sf::Packet createPacket(int, int j =0);
			
			/*!
			 * \brief recherche un socket vers un ordinateur distant
			 * \param adresse ip : adresse du socket � rechercher
			 * \return un pointeur vers le socket contenu dans l'attribut clients
			 */
			sf::TcpSocket* findSocket(sf::IpAddress&);
			
			/*!
			 * \brief recherche un socket vers un ordinateur distant
			 * \param adresse ip : adresse du socket � rechercher
			 * \return un iterateur vers le socket contenu dans l'attribut clients
			 */
			std::vector<sf::TcpSocket*>::iterator findSocketIterator(sf::IpAddress&);
			
			/*!
			 * \brief recherche et attend la r�ponse � un paquet envoy� pendant 0.1 seconde maximum
			 * \param entier : type du paquet � attendre
			 * \param adresse ip : adresse de l'�metteur du paquet
			 * \return un iterateur vers le paquet contenu dans l'attribut packets
			 */
			std::list<sf::Packet>::iterator waitPacket(int, sf::IpAddress&);
			
			/*!
			 * \brief d�crypte les paquets r�ceptionn�s
			 * \param paquet : le paquet � d�crypter
			 */
			void decryptPacket(sf::Packet&);
			
			/*!
			 * \brief permet d'afficher l'�tat de la classe � un moment donn�
			 */
			void etatNetwork();
			
			/*!
			 * \brief permet de r�server des slots disponibles
			 * \param entier non sign� : nombre de slots � r�server
			 * \param adresse ip : par d�faut l'adresse ip de l'ordinateur des joueurs qui r�servent les slots
			 */
			void setSlot(unsigned int nb, sf::IpAddress ip = sf::IpAddress::getLocalAddress());
			
			/*!
			 * \brief permet d'enregistrer le nom de joueurs
			 * \param tableau de chaines de caract�res : contient les nom � enregistrer
			 * \param adresse ip : par d�faut l'adresse ip de l'ordinateur des joueurs qui enregistrent leur nom
			 */
			void setName(std::string names[4], sf::IpAddress ip = sf::IpAddress::getLocalAddress());
			
			/*!
			 * \brief permet de r�server des slots disponibles
			 * \return vrai si le serveur est deconnect�,
			 * faux sinon
			 */
			bool isDeconnected();
			
			/*!
			 * \brief permet d'attribuer une valeur � l'attribut deconnect de fa�on synchronis�e
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
