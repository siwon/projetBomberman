/*!
 * \file NetworkManager.cpp
 * \brief Impl�mentation de classe NetworkManager
 * \author Brice GUILLERMIC
 */

// Biblioth�ques SFML
#include <SFML/Network.hpp>

//Headers
#include <iostream>
#include <vector>

#include "network/NetworkManager.hpp"
#include "SKeyPressed.hpp"
#include "SBonus.hpp"
#include "EGameBonus.hpp"
#include "SExplosive.hpp"
#include "EExplosiveType.hpp"
#include "SPlayer.hpp"
#include "EOrientation.hpp"
#include "EPlayerState.hpp"
#include "SFlame.hpp"
#include "EGameKeys.hpp"

#include "PolyBomberException.hpp"
#include "PolyBomberApp.hpp"

namespace PolyBomber
{
	NetworkManager::NetworkManager(){
		this->initialize();
	}

	NetworkManager::~NetworkManager(){		
		for(unsigned int i=0;i<this->clients.size();i++){
			delete this->clients[i]; // destruction des clients cr��s dynamiquements
		}
		

		if(this->threadClient != NULL)
			delete this->threadClient;
		if(this->threadRun != NULL)
			delete this->threadRun;
		if(this->threadServer != NULL)
			delete this->threadServer;
	}

	void NetworkManager::initialize(){
		for(int i = 0;i < 4;i++){
			this->ip[i] = sf::IpAddress::None;
			this->nbPlayerByIp[i] = 0;
		}
		this->setPause(0);
		this->started = false;
		this->setConnect(false);
		this->server = false;
		this->deconnect = false;
		for(int i=0;i<4;i++){
			for(int j=0;j<7;j++){
				this->keyPressed.keys[i][j] = false;
			}
		}

		this->controller = PolyBomberApp::getIControllerToNetwork();
		this->gameEngine = NULL;
		this->threadClient = NULL;
		this->threadRun = NULL;
		this->threadServer = NULL;
	}

	std::list<sf::Packet>::iterator NetworkManager::askServer(int num){
		std::list<sf::Packet>::iterator it;
		if(this->isConnected()){
			this->mutexClients.lock();
			sf::TcpSocket* client = this->clients[0];

			sf::Packet packet = this->createPacket(num);
			if(client->send(packet) != sf::TcpSocket::Done){
				this->mutexClients.unlock();
				setDeconnected(true);
			}

			sf::IpAddress address = client->getRemoteAddress();
			this->mutexClients.unlock();
			it = waitPacket(num, address);
		} else {
			setDeconnected(true);
		}
		return it;
	}

	SKeyPressed NetworkManager::getKeysPressed(){
		SKeyPressed keys;
		if(this->server){
			this->keyPressed = this->controller->getKeysPressed();

			// chercher le nombre de joueur sur le r�seau
			unsigned int nbPlayerDone = 0;
			for(unsigned int i = 0;i < this->players.size();i++){
				if(this->players[i].getIp() == sf::IpAddress::getLocalAddress()) // l'adresse local est celle du serveur
					nbPlayerDone++;
			}
			// pour chaque joueur en dehors du reseau, demander ces touches
			for(int i=0;i<4;i++){ // on parcourt le tableau d'ip
				if(this->nbPlayerByIp[i] != 0){ // s'il y a une adresse d'enregistr�e
					try {
						this->mutexClients.lock();
						sf::TcpSocket* client = this->findSocket(this->ip[i]); //peut renvoyer une exception
						this->mutexClients.unlock();
						sf::Packet packet = this->createPacket(3);
						if(client->send(packet) == sf::TcpSocket::Done){
							sf::IpAddress address = client->getRemoteAddress();
							std::list<sf::Packet>::iterator it = waitPacket(3, address);
							
							sf::Packet& thePacket =  *it ;
							int a;
							std::string s;
							thePacket >> a >> s >> keys; // r�cup�ration des touches envoy�es
							this->mutexPacket.lock();
							this->packets.erase(it);
							this->mutexPacket.unlock();
							
							//ajouter ses touches.
							for(int j = 0;j < this->nbPlayerByIp[i];j++){


								for(int k=0;k<7;k++){
									this->keyPressed.keys[nbPlayerDone][k] = keys.keys[j][k];
								}
								nbPlayerDone++;
							}
						} else {
							for(int j = 0;j<this->nbPlayerByIp[i];j++){
								for(int k = 0;k<7;k++){
									this->keyPressed.keys[nbPlayerDone][k] = false;
								}
								nbPlayerDone++;
							}
						}
					}
					catch(PolyBomberException e) {
						std::cerr << e.what() << std::endl;
						for(int j = 0;j<this->nbPlayerByIp[i];j++){
							for(int k = 0;k < 7;k++){
								this->keyPressed.keys[nbPlayerDone][k] = false;
							}
							nbPlayerDone++;
						}
					}
				}
			}
			//verification de la pause par un joueur
			unsigned int i = 0;
			while(i<this->gameConfig.nbPlayers && !this->paused){
				if(this->keyPressed.keys[i][GAME_PAUSE]) {
					this->setPause(i+1);
				}
				else
					i++;
			}
		}

		return this->keyPressed;
	}

	int NetworkManager::isPaused(){
		int result;
		if(this->server){
			this->mutexPause.lock();
			result = this->paused;
			this->mutexPause.unlock();
		}
		else {
			//demander au serveur
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
			std::list<sf::Packet>::iterator it2 = this->askServer(7);
			sf::Packet& thePacket = *it2;
			int num;
			std::string ip;
			thePacket >> num >> ip  >> result;
			this->packets.erase(it2);
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
		}
		return result;
	}

	void NetworkManager::resume(){
		if(this->server){

			this->setPause(0);

		} else {
			//envoyer un paquet (sans r�ponse) au serveur pour lui dire de reprendre
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
			this->mutexClients.lock();
			sf::TcpSocket* client = this->clients[0];

			sf::Packet packet = this->createPacket(21);
			if(client->send(packet) != sf::TcpSocket::Done) {// pas besoin de r�ponse
				this->mutexClients.unlock();
				setDeconnected(true);
			}
			this->mutexClients.unlock();
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
		}
	}

	void NetworkManager::cancel(){
		if(this->server){
			this->gameEngine->resetConfig(); // stop le thread run() s'il est commenc�
		}
		if(this->isConnected()){
			sf::Packet packet;
			packet = createPacket(101);
			if(this->server){ // on pr�vient les clients
				if(!this->gameConfig.isLocal){
					this->mutexClients.lock();
					for(unsigned int i = 0;i < this->clients.size();i++){
						if(this->clients[i]->send(packet) != sf::TcpSocket::Done){
							std::cerr << ("Le client "+this->clients[i]->getRemoteAddress().toString() +" n'a pas pu �tre contact� pour appeler sa m�thode Cancel")<< std::endl;
						}
					}
					this->mutexClients.unlock();
					
				}
			} else { // on pr�vient le serveur
				if(this->clients[0]->send(packet) != sf::TcpSocket::Done){
					setDeconnected(true);
				}
			}
			
			//terminer les threads 
			this->setConnect(false);

			// vider les vecteurs
			for(unsigned int i = 0;i < this->clients.size();i++){
				delete this->clients[i]; // destruction des clients cr�� dynamiquements
			}
			this->clients.clear();;
			this->packets.clear();
			this->selector.clear();
			// et lib�rer les threads
			if(this->threadClient != NULL)
			delete this->threadClient;
			if(this->threadRun != NULL)
				delete this->threadRun;
			if(this->threadServer != NULL)
				delete this->threadServer;

			
		}
		
		this->players.clear();
		this->initialize();
	}

	void NetworkManager::joinGame(std::string ip){
		this->initialize();
		sf::TcpSocket* server = new sf::TcpSocket;
		sf::IpAddress ip2(ip);
		if(server->connect(ip, 2222, sf::milliseconds(1000)) != sf::TcpSocket::Done){
			throw PolyBomberException("Erreur de connexion au serveur "+ip);
		} else {
			this->addSocket(server);
			this->setConnect(true);
			threadClient = new sf::Thread(&NetworkManager::listenToServer, this);
			threadClient->launch();
		}
		
	}

	int NetworkManager::getFreeSlots(){
		int result;
		if(this->server){
			result = (this->gameConfig.nbPlayers - this->players.size());
		} else {
			// demande au serveur
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
			std::list<sf::Packet>::iterator it2 = this->askServer(5);
			sf::Packet& thePacket = *it2;
			int num;
			std::string ip;
			thePacket >> num >> ip  >> result;
			this->packets.erase(it2);
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
		}

		return result;
	}

	void NetworkManager::setBookedSlots(unsigned int nb){
		this->setSlot(nb);
	}

	void NetworkManager::setSlot(unsigned int nb, sf::IpAddress ip) {
		this->mutexSlots.lock();
		if(this->server){
			if(ip != sf::IpAddress::getLocalAddress()){
				int i =0;
				while(i < 4 && !(this->ip[i] == sf::IpAddress::None)){ // on cherche un emplacement libre dans le tableau d'ip
					i++;
				}
				this->ip[i] = ip;
				this->nbPlayerByIp[i] = nb;
			}
			for(unsigned int i = 0;i < nb;i++){
				DataPlayer aPlayer(i, ip);
				this->players.push_back(aPlayer);
			}
		} else {
			// envoyer au serveur
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
			this->mutexClients.lock();
			sf::TcpSocket* client = this->clients[0];

			sf::Packet packet = this->createPacket(19,nb);
			if(client->send(packet) != sf::TcpSocket::Done) {// pas besoin de r�ponse
				setDeconnected(true);
			}
			this->mutexClients.unlock();
		}
		this->mutexSlots.unlock();
		if(isDeconnected()){
			throw PolyBomberException("Le serveur vient de quitter");
		}
	}

	void NetworkManager::setPlayerName(std::string names[4]){
		this->setName(names);
	}

	void NetworkManager::setName(std::string names[4], sf::IpAddress ip){
		if(this->server){
			int i = 0; //indice sur le vecteur de joueur
			int j = 0; //indice sur le tableau de nom
			while(i<4 && !(names[j] == "")){ // tant qu'il y a des noms � enregistrer
				if(this->players[i].getIp() == ip){
					this->mutexNames.lock();
					this->players[i].setName(names[j]);
					this->mutexNames.unlock();
					j++;
				}
				i++;
			}
		} else { // envoyer la demande au serveur
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
			this->mutexClients.lock();
			sf::TcpSocket* client = this->clients[0];
			sf::Packet packet; //paquet cr�� sur place car modification de createPacket pour passer les params
			packet << 17 << sf::IpAddress::getLocalAddress().toString();
			for(int i = 0;i < 4;i++){
				packet << names[i];
			}
			if(client->send(packet) != sf::TcpSocket::Done) {// pas besoin de r�ponse
				this->mutexClients.unlock();
				setDeconnected(true);
			}
			this->mutexClients.unlock();
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
		}
	}

	void NetworkManager::getPlayersName(std::string names[4]){
		if(this->server){
			for(unsigned int i = 0;i < 4;i++) {
				if(i<players.size()){
					this->mutexNames.lock();
					names[i] = this->players[i].getName();
					this->mutexNames.unlock();
				}
				else
					names[i] = "";
			}
		} else {
			//envoyer un paquet pour demander les noms aux serveur	
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
			std::list<sf::Packet>::iterator it = this->askServer(15);
			sf::Packet& thePacket = *it;
			int num;
			std::string ip;
			thePacket >> num >> ip;
			for(int i=0;i<4;i++){
				thePacket >> names[i];
			}
			this->packets.erase(it);	
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
		}
	}

	bool NetworkManager::isStarted(){
		bool result;
		if(this->server){
			result = this->started;
		} else {
		//demander au serveur
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
			std::list<sf::Packet>::iterator it2 = this->askServer(11);
			sf::Packet& thePacket = *it2;
			int num;
			std::string ip;
			thePacket >> num >> ip  >> result;
			this->started = result;
			this->packets.erase(it2);
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
		}
		return result;
	}

	void NetworkManager::startGame() {//threader la fonction de run
		if(this->server){			
			threadRun = new sf::Thread(&IGameEngineToNetwork::run, this->gameEngine);
			threadRun->launch();
			this->started=true;
		} 
	}

	std::string NetworkManager::getIpAddress(){
		sf::IpAddress address = sf::IpAddress::getLocalAddress();
		return address.toString();
	}

	void NetworkManager::setGameConfig(SGameConfig& pGameConfig){
		this->initialize();
		this->gameEngine = PolyBomberApp::getIGameEngineToNetwork();

		this->gameConfig = pGameConfig;

		this->server=true; //l'ordinateur sera le serveur

		this->gameEngine->setGameConfig(this->gameConfig);
		// cr�ation du listener qui �coute tous les clients
		
		if(!this->gameConfig.isLocal) {
			threadServer = new sf::Thread(&NetworkManager::createServerSocket, this);
			threadServer->launch();
		}
	}

	SBoard NetworkManager::getBoard(){
		if(this->server){
			return this->gameEngine->getBoard();
		} else {
			//demande au serveur
			SBoard aBoard;
			try {
				std::list<sf::Packet>::iterator it = this->askServer(1);
				sf::Packet& thePacket = *it;
				int i;
				std::string s;
				thePacket >> i >> s;
				thePacket >> aBoard;
				this->packets.erase(it);
			}
			catch(PolyBomberException e) {
				std::cerr << e.what() << std::endl;
			}
			return aBoard;
		}
		
	}

	int NetworkManager::isFinished(){
		int result = 0;
		if(this->server){
			result = this->gameEngine->isFinished();
		} else {
		//demander au r�seau
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
			std::list<sf::Packet>::iterator it2 = this->askServer(9);
			sf::Packet& thePacket = *it2;
			int num;
			std::string ip;
			thePacket >> num >> ip  >> result;
			this->packets.erase(it2);
			if(isDeconnected()){
				throw PolyBomberException("Le serveur vient de quitter");
			}
		}
		return result;
	}


	/******m�thode ne provenant pas d'interface***/

	/*!
	 * \brief Cr�ation d'un Listener pour le serveur
	 */
	void NetworkManager::createServerSocket(){
		sf::TcpListener listener;
		this->setConnect(true);

		listener.listen(2222);
		this->selector.add(listener);

		while (this->isConnected())
		 {
			 if (selector.wait(sf::milliseconds(100)))
			 {
				
				 // Test du listener
				 if (selector.isReady(listener))
				 {
					 // il y a une connexion en attente
					 sf::TcpSocket* client = new sf::TcpSocket;
					 if (listener.accept(*client) == sf::Socket::Done)
					 {
						 // ajout � la liste des sockets connect�s
						 this->addSocket(client);

						 // ajout au s�lecteur pour �tre averti lors de l'activit� du socket
						 selector.add(*client);
					 }
				 }
				 else
				 {
					 this->mutexClients.lock();
					 for (unsigned int i = 0;i < this->clients.size();i++)
					 {
						 sf::TcpSocket* client = this->clients[i];
						 if (this->selector.isReady(*client))
						 {
							 // le client envoie des donn�es
							 sf::Packet packet;
							 if (client->receive(packet) == sf::Socket::Done)
							 {
								 //V�rifier le premier num�ro s'il est impaire
								 sf::Packet testPacket = packet; // recopie du paquet re�u
								 int num;
								 testPacket >> num;
								 if(num%2){ // si c'est impaire
									 decryptPacket(packet);
								 } else { //ajouter le packet !!!!! mutex !!!!
									 this->mutexPacket.lock();
									 this->packets.push_back(packet);
									 this->mutexPacket.unlock();
								 }
							 }
						 }
					 }
					 this->mutexClients.unlock();
				 }
			 }
		 }
	}

	void NetworkManager::listenToServer(){
		sf::TcpSocket* server = this->clients[0];
		server->setBlocking(false);
		sf::Packet packet;
		while(this->isConnected()){
			if (server->receive(packet) == sf::Socket::Done){
				//V�rifier le premier num�ro s'il est impaire
				sf::Packet testPacket = packet; // recopie du paquet re�u
				int num;
				testPacket >> num;
				if(num%2){ // si c'est impaire
					decryptPacket(packet);
				} else { //ajouter le packet !!!!! mutex !!!!
					this->mutexPacket.lock();
					this->packets.push_back(packet);
					this->mutexPacket.unlock();
				}
			}
		}
	}

	// Cette m�thode sert au d�bugguage du module r�seau
	// Jamais appel�e dans la version rendue
	void NetworkManager::etatNetwork(){
		std::cout << "sf::IpAddress ip[4] ";
		for(int i = 0;i < 4;i++)
			std::cout << ip[i] << "|";
		std::cout << std::endl <<"nbPlayerByIp[4] ";
		for(int i = 0;i < 4;i++)
			std::cout << nbPlayerByIp[i] << "|";
		
		std::cout << std::endl << "Pause : " << paused << std::endl;
		std::cout << "Started ? : " << started << std::endl;
		std::cout << "connect ? : " << connect << std::endl;
		std::cout << "serveur ? : " << server << std::endl;

		std::cout << "taille Vecteur Players : " << players.size() << std::endl;
		for(unsigned int i = 0;i<players.size();i++)
			std::cout << players[i].getIp() << " | " ;


		std::cout << std::endl << "taille Vecteur clients : " << clients.size() << std::endl;
		for(unsigned int i = 0;i < clients.size();i++)
			std::cout << clients[i]->getRemoteAddress() << " | " ;
		
		std::cout << std::endl << "taille list packets : " << packets.size() << std::endl;
		for(std::list<sf::Packet>::iterator it = packets.begin();it != packets.end();it++)
			std::cout << *it << " | " ;

		std::cout << std::endl;
	}
	
	bool NetworkManager::isDeconnected(){
		bool result;
		this->mutexDeconnect.lock();
		result = this->deconnect;
		this->mutexDeconnect.unlock();
		return result;
	}
	
	void NetworkManager::setDeconnected(bool state){
		this->mutexDeconnect.lock();
		this->deconnect = state;
		this->mutexDeconnect.unlock();
	}

	sf::Packet NetworkManager::createPacket(int i, int j){
		sf::Packet packet;
		sf::IpAddress ipAddr = sf::IpAddress::getLocalAddress();
		std::string ipLocal = ipAddr.toString();
		packet << i << ipLocal;
		switch(i){
			//case 1 : demande de getboard d'un client
			case 2 : // envoi d'un SBoard
				if(this->server){
					SBoard gameBoard = this->gameEngine->getBoard();
					packet <<  gameBoard;
				}
				break;
			//case 3 : demande des touches press�es
			case 4 : // envoi d'un SKeyPressed
				if(!this->server){
					SKeyPressed keys = this->controller->getKeysPressed();
					packet << keys;
				}
				break;
			//case 5 :  demande des slots disponible
			case 6 : // envoi des slots disponibles
				int w;
				w = this->getFreeSlots();
				packet << w;
				break;
			//case 7 :  demande s'il y a une pause
			case 8 : // envoi s'il y a une pause
				this->mutexPause.lock();
				packet << this->paused;
				this->mutexPause.unlock();
				break;
			//case 9 :  demande s'il c'est fini
			case 10 : // envoi si c'est fini
				int a;
				a = this->isFinished();
				packet << a;
				break;
			//case 11 :  demande si c'est commenc�
			case 12 : // envoi si c'est commenc�
				bool b;
				b = this->isStarted();
				packet << b;
				break;
			//case 13 : inutilis�
			//case 14 : inutilis�
			//case 15 : demande des noms
			case 16 : // envoi des noms
				for(unsigned int i=0;i<4;i++) {
					if(i<players.size()){
						std::string s = this->players[i].getName();
						packet << s;
					}
					else
						packet << "";
				}
				break;
			//le cas 17 est directement g�r� dans la fonction setPlayersName
			case 19 : // envoi r�servation d'un slot
				packet << j;
				break;
			//case 21 :  envoi de la reprise du jeu			
		}
		return packet;
	}

	sf::TcpSocket* NetworkManager::findSocket(sf::IpAddress& ip){
		if(!this->server && (this->clients.size() > 0)){
			return this->clients[0];
		} else {
			std::vector<sf::TcpSocket*>::iterator it = findSocketIterator(ip);
			return *it;
		}
	}

	std::vector<sf::TcpSocket*>::iterator NetworkManager::findSocketIterator(sf::IpAddress& ip){
		bool find = false;
		sf::IpAddress ipClient;
		sf::TcpSocket* client = NULL;
		std::vector<sf::TcpSocket*>::iterator it = clients.begin();
		while( it != clients.end() && !find){
			client = *it;
			ipClient = client->getRemoteAddress();
			if(ipClient == ip)
				find = true;
			else
				it++;
		}
		if(!find) {
			this->mutexClients.unlock();
			throw PolyBomberException ("Le serveur n'a pas pu trouver le socket pour communiquer avec le client "+ip.toString());
		}
		return it;
	}

	std::list<sf::Packet>::iterator NetworkManager::waitPacket(int num, sf::IpAddress& ipAddr){
		bool find = false;
		int type;
		std::string ip;
		std::list<sf::Packet>::iterator it;
		sf::Clock clock;
		while(!find && clock.getElapsedTime().asMilliseconds() < 250){
			
			this->mutexPacket.lock();
			it = this->packets.begin();
			while(it!=this->packets.end() && !find){
				sf::Packet aPacket = *it; // duplique le paquet pour pouvoir le regarder
				aPacket >> type >> ip;
				if(type == (num+1) && ip == ipAddr.toString()){
					find = true;
				} else {
					it++;
				}
			}
			this->mutexPacket.unlock();
		}
		if(!find){
			this->setDeconnected(true);
		}
		return it;
	}

	void NetworkManager::decryptPacket(sf::Packet& packet){
		int num;
		sf::Packet result;
		std::string ip;
		packet >> num >> ip;
		sf::IpAddress ip1(ip);
		std::string names[4] = {"", "", "", ""};
		switch(num){
		case 101 :
			if(this->server){
				eraseSocket(ip1);
			} else {
				setDeconnected(true);
			}
			break;
		case 17 :
			for(int i = 0;i < 4;i++){
				packet >> names[i];
			}
			setName(names, ip1); // methode utilisant des ressources critiques
			break;
		case 19 :
			int j;
			packet >> j;
			setSlot(j, ip1); // methode utilisant des ressources critiques
			break;
		case 21 :
			resume();
			break;
		default : // c'est une demande qui n�cessite une r�ponse
			result = createPacket(num+1);
			
			this->mutexClients.lock();
			try {
				sf::TcpSocket* client = this->findSocket(ip1);
				if (client->send(result) != sf::TcpSocket::Done){
					std::cerr << "la r�ponse n�" << num << " n'� pas pu �tre renvoy�e" << std::endl;
				}
			} catch(PolyBomberException& e) {
				std::cerr << "decrypt packet ne trouve pas le socket" << std::endl;
			}
			this->mutexClients.unlock();
		}
	}

	bool NetworkManager::isConnected(){
		bool result;
		this->mutexConnect.lock();
		result = this->connect;
		this->mutexConnect.unlock();
		return result;
	}

	void NetworkManager::setConnect(bool a) {
		this->mutexConnect.lock();
		this->connect = a;
		this->mutexConnect.unlock();
	}

	void NetworkManager::setPause(int i){
		this->mutexPause.lock();
		this->paused = i;
		this->mutexPause.unlock();
	}

	void NetworkManager::eraseSocket(sf::IpAddress& ip) {
		// suprime le socket � cet adresse ip ; fonction appel� uniquement sur le serveur
		try{
			this->mutexClients.lock();
			std::vector<sf::TcpSocket*>::iterator it = this->findSocketIterator(ip);
			sf::TcpSocket* socket = *it;
			this->selector.remove(*socket);
			this->clients.erase(it);
			this->mutexClients.unlock();
			delete socket;
		} catch(PolyBomberException e) {
			this->mutexClients.unlock();
			std::cerr << e.what() << std::endl;
		}
		this->deletePlayer(ip);
	}

	void NetworkManager::deletePlayer(sf::IpAddress& ip1){
		if(isStarted()){ // on ne peut pas les supprimer, le jeu est lanc�
			for(unsigned int i=0;i<players.size();i++){
				DataPlayer& player = this->players[i];
				if(player.getIp() == ip1)
					player.setConnected(false);
			}
		} else { // il faut les supprimer pour laisser la place � d'autre
			for(std::vector<DataPlayer>::iterator it = players.begin();it<players.end();it++){
				while((it<players.end())&&(it->getIp() == ip1)){ // while car le vector d�cale apr�s la supression et la boucle for augmente. DU coup il y a une occurrence qui �chappe a la v�rification
					players.erase(it); // suppression dans le vecteur
				}
			}
			bool find = false;
			for(int i = 0;i < 4;i++){
				if(!find){
					if(this->ip[i] == ip1)
						find = true;
				} else { // suppression dans les tableaux + d�calage
					this->ip[i-1] = this->ip[i];
					this->nbPlayerByIp[i-1]=this->nbPlayerByIp[i];
				}
			}
			this->ip[3]=sf::IpAddress::None;
			this->nbPlayerByIp[3] = 0;
		}
		
	}

	void NetworkManager::addSocket(sf::TcpSocket* socket) {
		this->mutexClients.lock();
		this->clients.push_back(socket);
		this->mutexClients.unlock();
	}

	/*surcharge des op�rateurs de flux des sf::Packet*/
	sf::Packet& operator<<(sf::Packet& packet, SBoard& b){

		/*Ajout des Boxes*/
		packet << (int)b.boxes.size();
		for (unsigned int i = 0;i < b.boxes.size();i++){
			packet << b.boxes[i].x << b.boxes[i].y;
		}

		/*Ajout des Bonus*/
		packet << (int)b.bonus.size();
		for(unsigned int i = 0;i < b.bonus.size();i++){
			packet << b.bonus[i].coords.x << b.bonus[i].coords.y << b.bonus[i].type;
		}

		/*Ajout des explosifs*/
		packet << (int)b.explosives.size();
		for(unsigned int i = 0;i < b.explosives.size();i++){
			packet << b.explosives[i].coords.x << b.explosives[i].coords.y << b.explosives[i].type;
		}

		/*ajout des players*/
		packet << (int)b.players.size();
		for (unsigned int i = 0;i < b.players.size();i++){
			packet << b.players[i].coords.x << b.players[i].coords.y << b.players[i].orientation << b.players[i].number << b.players[i].state << b.players[i].step;
		}

		/*Ajout des flames*/
		packet << (int)b.flames.size();
		for(unsigned int i = 0;i < b.flames.size();i++){			
			packet << b.flames[i].coords.x << b.flames[i].coords.y << b.flames[i].orientation << b.flames[i].step << b.flames[i].location;
		}

		return packet;
	}

	sf::Packet& operator<<(sf::Packet& packet, SKeyPressed& key){
		bool val;
		for(int i = 0;i<4;i++){
			for(int j = 0;j<7;j++){
				val = key.keys[i][j];
				packet << val;
			}
		}
		return packet;
	}

	sf::Packet& operator>>(sf::Packet& packet, SBoard& board){

		/*Ajout des Boxes*/
		int j;
		int type;
		packet >> j;
		
		for(int i=0;i<j;i++){
			sf::Vector2<int> coord;
			packet >> coord.x >> coord.y;
			board.boxes.push_back(coord);
		}
		
		/*Ajout des Bonus*/
		packet >> j;
		for(int i = 0;i < j;i++){
			SBonus bonus;
			packet >> bonus.coords.x >> bonus.coords.y >> type;
			bonus.type = (EGameBonus)type;
			board.bonus.push_back(bonus);
		}

		/*Ajout des explosifs}*/
		packet >> j;
		for(int i = 0;i < j;i++){
			SExplosive explo;
			packet >> explo.coords.x >> explo.coords.y >> type;
			explo.type = (EExplosiveType)type;
			board.explosives.push_back(explo);
		}

		/*ajout des players*/
		packet >> j;
		int state;
		for(int i=0;i<j;i++){
			SPlayer player;
			packet >> player.coords.x >> player.coords.y >> type >> player.number >> state >> player.step;
			player.orientation = (EOrientation)type;
			player.state = (EPlayerState)state;
			board.players.push_back(player);
		}

		/*Ajout des flames*/
		packet >> j;
		int location;
		for(int i = 0;i < j;i++){
			SFlame flame;
			
			packet >> flame.coords.x >> flame.coords.y >> type >> flame.step >> location ;
			
			flame.orientation = (EOrientation)type;
			flame.location = (EFlameLocation)location;
			board.flames.push_back(flame);
		}
		
		return packet;
	}

	sf::Packet& operator>>(sf::Packet& packet, SKeyPressed& key){
		bool val;
		for(int i = 0;i < 4;i++){
			for(int j = 0;j < 7;j++){
				packet >> val;
				key.keys[i][j] = val;
			}
		}
		return packet;
	}
}
