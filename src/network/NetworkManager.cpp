/*!
 * \file NetworkManager.cpp
 * \brief Implémentation de classe NetworkManager
 * \author Brice GUILLERMIC
 */

// Bibliothèques SFML
#include <SFML/Network.hpp>

//Headers
#include <iostream>
#include <vector>

#include "../../include/network/NetworkManager.hpp"
#include "../../include/SKeyPressed.hpp"
#include "../../include/SBonus.hpp"
#include "../../include/EGameBonus.hpp"
#include "../../include/SExplosive.hpp"
#include "../../include/EExplosiveType.hpp"
#include "../../include/SPlayer.hpp"
#include "../../include/EOrientation.hpp"
#include "../../include/EPlayerState.hpp"
#include "../../include/SFlame.hpp"
#include "../../include/EGameKeys.hpp"
#include "../../include/PolyBomberException.hpp"

#include "../../include/PolyBomberApp.hpp"

namespace PolyBomber
{
	NetworkManager::NetworkManager(){
		this->initialize();
	}

	NetworkManager::~NetworkManager(){		
		for(unsigned int i=0;i<this->clients.size();i++){
			//delete this->clients[i]; // destruction des clients créé dynamiquements
		}
		

		if(this->threadClient != NULL)
			delete this->threadClient;
		if(this->threadRun != NULL)
			delete this->threadRun;
		if(this->threadServer != NULL)
			delete this->threadServer;
	}

	void NetworkManager::initialize(){
		for(int i=0;i<4;i++){
			this->ip[i] = sf::IpAddress::None;
			this->nbPlayerByIp[i]=0;
			this->scores[i]=0;
		}
		this->setPause(0);
		this->started=false;
		this->setConnect(false);
		this->server=false;
		for(int i=0;i<4;i++){
			for(int j=0;j<7;j++){
				this->keyPressed.keys[i][j] = false;
			}
		}

		this->controller = PolyBomberApp::getIControllerToNetwork();//FIXME: 
		this->gameEngine = NULL;
		this->threadClient = NULL;
		this->threadRun =NULL;
		this->threadServer =NULL;
	}

	std::list<sf::Packet>::iterator NetworkManager::askServer(int num){
		if(this->isConnected()){
			std::list<sf::Packet>::iterator it;
			this->mutexClients.lock();
			sf::TcpSocket* client = this->clients[0];

			sf::Packet packet = this->createPacket(num);
			std::cout << "packet n° " << num <<" pret a envoyer" << std::endl; 
			if(client->send(packet) != sf::TcpSocket::Done){
				this->mutexClients.unlock();
				std::cerr << "packet n° " << num <<" n'a pas pu etre envoye" << std::endl; 
				throw PolyBomberException("meme pas pu envoyer le paquet");
			}

			sf::IpAddress address = client->getRemoteAddress();
			this->mutexClients.unlock();
			std::cout << "packet n° " << num <<" a ete envoye" << std::endl; 
			it = waitPacket(num, address);
			return it;
		} else {
			throw PolyBomberException("Aucune connexion n'a été trouvée vers un serveur");
		}
	}

	SKeyPressed NetworkManager::getKeysPressed(){
		SKeyPressed keys;
		if(this->server){
			this->keyPressed = this->controller->getKeysPressed();

			// chercher le nombre de joueur sur le réseau
			unsigned int nbPlayerDone =0;
			for(unsigned int i=0;i<this->players.size();i++){
				if(this->players[i].getIp() == sf::IpAddress::getLocalAddress()) // l'adresse local est celle du serveur
					nbPlayerDone++;
			}
			// pour chaque joueur en dehors du reseau, demander ces touches
			for(int i=0;i<4;i++){ // on parcourt le tableau d'ip
				if(this->nbPlayerByIp[i] != 0){ // s'il y a une adresse d'enregistrée
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
							thePacket >> a >> s >> keys; // récupération des touches envoyées
							this->mutexPacket.lock();
							this->packets.erase(it);
							this->mutexPacket.unlock();
							
							//ajouter ses touches.
							//std::cout << "nbPlayerByIp[i]" <<i<<";"<<this->nbPlayerByIp[i]<< std::endl;
							for(int j=0;j<this->nbPlayerByIp[i];j++){


								for(int k=0;k<7;k++){
									//std::cout << "nbplayerdone et j" <<nbPlayerDone<<j<< std::endl;
									this->keyPressed.keys[nbPlayerDone][k] = keys.keys[j][k];
								}
								nbPlayerDone++;
							}
						} else {
							std::cerr << "le joueur n'est plus accessible pour demander ses touches" << std::endl;
							for(int j=0;j<this->nbPlayerByIp[i];j++){
								for(int k=0;k<7;k++){
									this->keyPressed.keys[nbPlayerDone][k] = false;
								}
								nbPlayerDone++;
							}
						}
					}
					catch(PolyBomberException e) {
						std::cerr << e.what() << std::endl;
						for(int j=0;j<this->nbPlayerByIp[i];j++){
							for(int k=0;k<7;k++){
								this->keyPressed.keys[nbPlayerDone][k] = false;
							}
							nbPlayerDone++;
						}
					}
				}
			}
			//verification de la pause par un joueur
			unsigned int i=0;
			while(i<this->gameConfig.nbPlayers && !this->paused){
				if(this->keyPressed.keys[i][GAME_PAUSE]) {
					this->setPause(i+1);
				}
				else
					i++;
			}
		} else { // on est le client
			//message d'erreur car le client ne peut demander les touche au gameEngine
			std::cerr << "le client ne peut demander les touches au gameEngine" << std::endl;
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
			try {
				std::list<sf::Packet>::iterator it2 = this->askServer(7);
				sf::Packet& thePacket = *it2;
				int num;
				std::string ip;
				thePacket >> num >> ip  >> result;
				this->packets.erase(it2);
			}
			catch(PolyBomberException e){
				std::cerr << e.what() << std::endl;
			}
		}
		return result;
	}

	void NetworkManager::resume(){
		if(this->server){

			this->setPause(0);

		} else {
			//envoyer un paquet (sans réponse) au serveur pour lui dire de reprendre
			this->mutexClients.lock();
			sf::TcpSocket* client = this->clients[0];

			sf::Packet packet = this->createPacket(21);
			if(client->send(packet) != sf::TcpSocket::Done) {// pas besoin de réponse
				this->mutexClients.unlock();
				throw PolyBomberException("l'envoie de la reprise à échoué");
			}
			this->mutexClients.unlock();
		}
	}

	void NetworkManager::cancel(){
	etatNetwork();
		if(this->isConnected()){
			sf::Packet packet;
			packet = createPacket(101);
			if(this->server){ // on prévient les clients
				if(!this->gameConfig.isLocal){
					this->mutexClients.lock();
					for(unsigned int i=0;i<this->clients.size();i++){
						if(this->clients[i]->send(packet) != sf::TcpSocket::Done){
							std::cerr << ("Le client "+this->clients[i]->getRemoteAddress().toString() +" n'a pas pu être contacté pour appeler sa méthode Cancel")<< std::endl;
						}
					}
					this->mutexClients.unlock();
					
				}
			} else { // on prévient le serveur
				if(this->clients[0]->send(packet) != sf::TcpSocket::Done){
						std::cerr << ("Le serveur "+this->clients[0]->getRemoteAddress().toString() +" n'a pas pu être contacté pour le prévenir d'un Cancel")<< std::endl;
				}
			}
			
			//terminer les threads 
			this->setConnect(false);

			// vider les vecteurs
			for(unsigned int i=0;i<this->clients.size();i++){
				delete this->clients[i]; // destruction des clients créé dynamiquements
			}
			this->clients.clear();;
			this->packets.clear();
			this->selector.clear();
			// et libérer les threads
			if(this->threadClient != NULL)
			delete this->threadClient;
			if(this->threadRun != NULL)
				delete this->threadRun;
			if(this->threadServer != NULL)
				delete this->threadServer;

			
		}
		if(this->server){
			this->gameEngine->resetConfig(); // stop le thread run() s'il est commencé
			std::cout << "Le gameEngine a ete averti" << std::endl;
		}
		this->players.clear();
		this->initialize();
		etatNetwork();
	}

	void NetworkManager::joinGame(std::string ip){
		this->server=false;
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
			std::list<sf::Packet>::iterator it2 = this->askServer(5);
			sf::Packet& thePacket = *it2;
			int num;
			std::string ip;
			thePacket >> num >> ip  >> result;
			this->packets.erase(it2);
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
				while(i<4 && !(this->ip[i] == sf::IpAddress::None)){ // on cherche un emplacement libre dans le tableau d'ip
					i++;
				}
				this->ip[i]=ip;
				this->nbPlayerByIp[i]=nb;
			}
			for(unsigned int i=0;i<nb;i++){
				DataPlayer aPlayer(i, ip);
				this->players.push_back(aPlayer);
			}
		} else {
			// envoyer au serveur
			this->mutexClients.lock();
			sf::TcpSocket* client = this->clients[0];

			sf::Packet packet = this->createPacket(19,nb);
			if(client->send(packet) != sf::TcpSocket::Done) {// pas besoin de réponse
				this->mutexClients.unlock();
				throw PolyBomberException("échec de la réservation de slot");
			}
			this->mutexClients.unlock();
		}
		this->mutexSlots.unlock();
	}

	void NetworkManager::setPlayerName(std::string names[4]){
		this->setName(names);
	}

	void NetworkManager::setName(std::string names[4], sf::IpAddress ip){
		if(this->server){
			int i=0;//indice sur le vecteur de joueur
			int j=0;//indice sur le tableau de nom
			while(i<4 && !(names[j] == "")){ // tant qu'il y a des noms à enregistrer
				if(this->players[i].getIp() == ip){
					this->mutexNames.lock();
					this->players[i].setName(names[j]);
					this->mutexNames.unlock();
					j++;
				}
				i++;
			}
		} else { // envoyer la demande au serveur
			this->mutexClients.lock();
			sf::TcpSocket* client = this->clients[0];
			sf::Packet packet; //paquet créé sur place car modification de createPacket pour passer les params
			packet << 17 << sf::IpAddress::getLocalAddress().toString();
			for(int i=0;i<4;i++){
				packet << names[i];
			}
			if(client->send(packet) != sf::TcpSocket::Done) {// pas besoin de réponse
				this->mutexClients.unlock();
				throw PolyBomberException("échec lors de l'envoi des noms");
			}
			this->mutexClients.unlock();
		}
	}

	void NetworkManager::getPlayersName(std::string names[4]){
		if(this->server){
			for(unsigned int i=0;i<4;i++) {
				if(i<players.size()){
					this->mutexNames.lock();
					names[i]=this->players[i].getName();
					this->mutexNames.unlock();
				}
				else
					names[i]="";
			}
		} else {
			try {
				//envoyer un paquet pour demander les noms aux serveur	
				std::list<sf::Packet>::iterator it = this->askServer(15);
				sf::Packet& thePacket = *it;
				int num;
				std::string ip;
				thePacket >> num >> ip;
				for(int i=0;i<4;i++){
					thePacket >> names[i];
				}
				this->packets.erase(it);	
			}
			catch(PolyBomberException& e){
				throw PolyBomberException(e.what());
			}
		}
	}

	int* NetworkManager::getScores(){
		if(!this->server){
			//demander au serveur
			std::list<sf::Packet>::iterator it2 = this->askServer(7);
			sf::Packet& thePacket = *it2;
			int num;
			std::string ip;
			thePacket >> num >> ip;
			for(int i=0;i<4;i++){
				thePacket >> this->scores[i];
			}
			this->packets.erase(it2);
		}
		return this->scores;
	}

	bool NetworkManager::isStarted(){
		bool result;
		if(this->server){
			result = this->started;
			} else {
			//demander au serveur
				try {
					std::list<sf::Packet>::iterator it2 = this->askServer(11);
					sf::Packet& thePacket = *it2;
					int num;
					std::string ip;
					thePacket >> num >> ip  >> result;
					this->packets.erase(it2);
				}
				catch (PolyBomberException e){
					std::cerr << e.what() <<std::endl;
				}
		}
		return result;
	}

	void NetworkManager::startGame() {//threader la fonction de run
		if(this->server){
			std::cout << "c'est parti" << std::endl;
			
			threadRun = new sf::Thread(&IGameEngineToNetwork::run, this->gameEngine);
			threadRun->launch();
			this->started=true;
		} else {
			std::cerr << "le client ne peut pas donner le départ du jeu. Appel de startGame interdit" << std::endl;
		}
	}

	std::string NetworkManager::getIpAddress(){
		sf::IpAddress address = sf::IpAddress::getLocalAddress();
		return address.toString();
	}

	void NetworkManager::setGameConfig(SGameConfig& pGameConfig){
		this->gameEngine = PolyBomberApp::getIGameEngineToNetwork();//FIXME: 

		this->gameConfig = pGameConfig;

		this->server=true; //l'ordinateur sera le serveur

		this->gameEngine->setGameConfig(this->gameConfig);//FIXME: // on envoie également au gameEngine
		// création du listener qui écoute tous les clients
		
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
		int result;
		if(this->server){
			result = this->gameEngine->isFinished();
		} else {
		//demander au réseau
			try {
				std::list<sf::Packet>::iterator it2 = this->askServer(9);
				sf::Packet& thePacket = *it2;
				int num;
				std::string ip;
				thePacket >> num >> ip  >> result;
				this->packets.erase(it2);
			}
			catch(PolyBomberException e) {
				std::cerr << e.what() << std::endl;
			}
		}
		return result;
	}


	/******méthode ne provenant pas d'interface***/

	/*!
	 * \brief Création d'un Listener pour le serveur
	 */
	void NetworkManager::createServerSocket(){
		sf::TcpListener listener;
		this->setConnect(true);

		listener.listen(2222);
		this->selector.add(listener);

		// Endless loop that waits for new connections
		while (this->isConnected())
		 {
			 // Make the selector wait for data on any socket
			 if (selector.wait(sf::milliseconds(100)))
			 {
				
				 // Test the listener
				 if (selector.isReady(listener))
				 {
					 // The listener is ready: il y a une connexion en attente
					 sf::TcpSocket* client = new sf::TcpSocket;
					 if (listener.accept(*client) == sf::Socket::Done)
					 {
						 std::cout << "nouveau client " << client->getRemoteAddress() << std::endl;
						 // ajout à la liste des sockets connectés
						 this->addSocket(client);

						 // ajout au sélector pour être averti lors de l'activité du socket
						 selector.add(*client);
					 }
				 }
				 else
				 {
					 // The listener socket is not ready, test all other sockets (the clients)
					 this->mutexClients.lock();
					 for (unsigned int i=0;i<this->clients.size();i++)
					 {
						 sf::TcpSocket* client = this->clients[i];
						 if (this->selector.isReady(*client))
						 {
							 // The client has sent some data, we can receive it
							 sf::Packet packet;
							 if (client->receive(packet) == sf::Socket::Done)
							 {
								 //Vérifier le premier numéro s'il est impaire
								 sf::Packet testPacket = packet; // recopie du paquet reçu
								 int num;
								 testPacket >> num;
								 if(num%2){ // si c'est impaire
									 decryptPacket(packet);
								 } else { //ajouter le packet !!!!! mutex !!!!
									 this->mutexPacket.lock();
									 std::cout << "AJOUT DU PAQUET NUMERO "<<num<< std::endl;
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
		std::cout << "fin du thread serveur" << std::endl;
	}

	void NetworkManager::listenToServer(){
		sf::TcpSocket* server = this->clients[0];
		server->setBlocking(false);
		sf::Packet packet;
		while(this->isConnected()){
			//sf::sleep(sf::milliseconds(2));
			if (server->receive(packet) == sf::Socket::Done){
				//Vérifier le premier numéro s'il est impaire
				sf::Packet testPacket = packet; // recopie du paquet reçu
				int num;
				testPacket >> num;
				std::cout << "reception d'un paquet numero "<< num << std::endl;
				if(num%2){ // si c'est impaire
					decryptPacket(packet);
				} else { //ajouter le packet !!!!! mutex !!!!
					this->mutexPacket.lock();
					this->packets.push_back(packet);
					this->mutexPacket.unlock();
				}
			}
		}
		std::cout << "fin du thread client" << std::endl;
	}

	void NetworkManager::etatNetwork(){
		std::cout << "sf::IpAddress ip[4] ";
		for(int i=0;i<4;i++)
			std::cout << ip[i] << "|";
		std::cout << std::endl <<"nbPlayerByIp[4] ";
		for(int i=0;i<4;i++)
			std::cout << nbPlayerByIp[i] << "|";
		
		std::cout << std::endl <<"Pause : " << paused << std::endl;
		std::cout <<"Started ? : " << started << std::endl;
		std::cout <<"connect ? : " << connect << std::endl;
		std::cout <<"serveur ? : " << server << std::endl;

		std::cout << "taille Vecteur Players : " << players.size() << std::endl;
		for(unsigned int i=0;i<players.size();i++)
			std::cout << players[i].getIp() << " | " ;


		std::cout << std::endl << "taille Vecteur clients : " << clients.size() << std::endl;
		for(unsigned int i=0;i<clients.size();i++)
			std::cout << clients[i]->getRemoteAddress() << " | " ;
		
		std::cout << std::endl << "taille list packets : " << packets.size() << std::endl;
		for(std::list<sf::Packet>::iterator it= packets.begin();it!=packets.end();it++)
			std::cout << *it << " | " ;

		std::cout << std::endl;
	}

	sf::Packet NetworkManager::createPacket(int i, int j){
		sf::Packet packet;
		sf::IpAddress ipLocal = sf::IpAddress::getLocalAddress();
		packet << i << ipLocal.toString();
		std::cout << "creation du paquet numero : " << i << std::cout;
		switch(i){
			case 1 : // demande de getboard d'un client
			std::cout << "demande du plateau" << std::endl;
				break;
			case 2 : // envoi d'un SBoard
				if(this->server){
					std::cout << "debut denvoie du plateau" << std::endl;
					SBoard gameBoard = this->gameEngine->getBoard();
					packet <<  gameBoard;
				} else {
					std::cerr << "le plateau ne peut être obtenu car un Client n'a pas accès à un GameEngine" << std::endl;
				}
				break;
			case 3 : // demande des touches pressées
				std::cout << "demande des touches" << std::endl;
				break;
			case 4 : // envoi d'un SKeyPressed
				if(!this->server){
					std::cout << "debut denvoie des touches" << std::endl;
					SKeyPressed keys = this->controller->getKeysPressed();
					packet << keys;
					
				}
				break;
			case 5 : // demande des slots disponible

				break;
			case 6 : // envoi des slots disponibles
				packet << this->getFreeSlots();
				break;
			case 7 : // demande s'il y a une pause
				std::cout << "demande de la pause" << std::endl;
				break;
			case 8 : // envoi s'il y a une pause
				this->mutexPause.lock();
				packet << this->paused;
				this->mutexPause.unlock();
				break;
			case 9 : // demande s'il c'est fini
				break;
			case 10 : // envoi si c'est fini
				packet << this->isFinished();
				break;
			case 11 : // demande si c'est commencé
				break;
			case 12 : // envoi si c'est commencé
				packet << this->isStarted();
				break;
			case 13 : // demande du score
				break;
			case 14 : // envoi du score
				for(int i=0;i<4;i++)
					packet << this->scores[i];
				break;
			case 15 : // demande des noms
				break;
			case 16 : // envoi des noms
				for(unsigned int i=0;i<4;i++) {
					if(i<players.size())
						packet << this->players[i].getName();
					else
						packet << "";
				}
				break;
			//le cas 17 est directement géré dans la fonction setPlayersName
			case 19 : // envoi réservation d'un slot
				packet << j;
				break;
			case 21 : // envoi de la reprise du jeu
				break;
			
		}
		return packet;
	}

	sf::TcpSocket* NetworkManager::findSocket(sf::IpAddress& ip){
		if(!this->server){
			return this->clients[0];
		} else {
			std::vector<sf::TcpSocket*>::iterator it = findSocketIterator(ip);
			return *it;
		}
	}

	std::vector<sf::TcpSocket*>::iterator NetworkManager::findSocketIterator(sf::IpAddress& ip){
		bool find = false;
		sf::TcpSocket* client= NULL;
		std::vector<sf::TcpSocket*>::iterator it = clients.begin();
		while( it != clients.end() && !find){
			client = *it;
			if(client->getRemoteAddress()== ip)
				find=true;
			else
				it++;
		}
		if(!find) {
			std::cerr << "taille du vecteur de socket : "<<this->clients.size() << std::endl;
			if(this->clients.size() !=0){
				std::cerr << "addrr ip  : "<<this->clients[0]->getRemoteAddress()<<std::endl;
			}
			this->mutexClients.unlock();
			throw PolyBomberException ("Le serveur n'a pas pu trouver le socket pour communiquer avec le client "+ip.toString());
		}
		return it;
	}

	std::list<sf::Packet>::iterator NetworkManager::waitPacket(int num, sf::IpAddress& ipAddr){
		bool find=false;
		int type;
		std::string ip;
		std::list<sf::Packet>::iterator it;
		sf::Clock clock;
		while(!find && clock.getElapsedTime().asMilliseconds() < 100){
			
			this->mutexPacket.lock();
			it = this->packets.begin();
			while(it!=this->packets.end() && !find){
				sf::Packet aPacket = *it; // duplique le paquet pour pouvoir le regarder
				aPacket >> type >> ip;
				std::cout << "lecture dans la file d'attente du packet n° " << type  <<std::endl; 
				if(type==(num+1) && ip==ipAddr.toString()){
					find=true;
				} else {
					it++;
				}
			}
			this->mutexPacket.unlock();
		}
		if(!find){
			std::cerr << "PAS TROUVE packet n° " << num  <<std::endl; 
			throw PolyBomberException(num+"Echec de la réception du paquet de l'expéditeur "+ipAddr.toString()+". Temps d'attente de 100 millisecondes dépassé");
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
				std::cerr << "le client " << ip <<" vient de se deconnecter" << std::endl;
				eraseSocket(ip1);
			} else {
				throw PolyBomberException("Le serveur vient de quitter la partie");
			}
			etatNetwork();
			break;
		case 17 :
			for(int i=0;i<4;i++){
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
		default : // c'est une demande qui nécessite une réponse
			result = createPacket(num+1);
			
			this->mutexClients.lock();
			try {
				sf::TcpSocket* client = this->findSocket(ip1);
				if (client->send(result) != sf::TcpSocket::Done){
					std::cerr << "la réponse n°" << num << " n'à pas pu être renvoyée" << std::endl;
				}
				std::cout << "fin envoi "<< num+1 << std::endl;
			} catch(PolyBomberException e) {
				std::cout << "decrypt packet ne trouve pas le socket" << std::endl;
			}
			this->mutexClients.unlock();
		}
	}

	bool NetworkManager::isConnected(){
		bool result;
		this->mutexConnect.lock();
		result=this->connect;
		this->mutexConnect.unlock();
		return result;
	}

	void NetworkManager::setConnect(bool a) {
		this->mutexConnect.lock();
		this->connect=a;
		this->mutexConnect.unlock();
	}

	void NetworkManager::setPause(int i){
		this->mutexPause.lock();
		this->paused=i;
		this->mutexPause.unlock();
	}

	void NetworkManager::eraseSocket(sf::IpAddress& ip) {
		// suprime le socket à cet adresse ip ; fonction appelé uniquement sur le serveur
		try{
			std::vector<sf::TcpSocket*>::iterator it = this->findSocketIterator(ip);
			sf::TcpSocket* socket = *it;
			this->selector.remove(*socket);
			this->mutexClients.lock();
			this->clients.erase(it);
			this->mutexClients.unlock();
			delete socket;
			std::cout << "ok pour la suppression du socket" << std::endl;
		} catch(PolyBomberException e) {
			std::cerr << e.what() << std::endl;
		}
		this->deletePlayer(ip);
	}

	void NetworkManager::deletePlayer(sf::IpAddress& ip1){
		if(isStarted()){ // on ne peut pas les supprimer, le jeu est lancé
			for(unsigned int i=0;i<players.size();i++){
				DataPlayer& player = this->players[i];
				if(player.getIp() == ip1)
					player.setConnected(false);
			}
		} else { // il faut les supprimer pour laisser la place à d'autre
			for(std::vector<DataPlayer>::iterator it = players.begin();it<players.end();it++){
				while((it<players.end())&&(it->getIp() == ip1)){ // s'il y a plusieurs joueurs, obligé de faire un while car le vector décale après la supression et la boucle for augmente. DU coup il y a une occurrence qui échappe a la vérification
					players.erase(it); // suppression dans le vecteur
				}
			}
			bool find = false;
			for(int i=0;i<4;i++){
				if(!find){
					if(this->ip[i]==ip1)
						find=true;
				} else { // suppression dans les tableaux + décalage
					this->ip[i-1]=this->ip[i];
					this->nbPlayerByIp[i-1]=this->nbPlayerByIp[i];
				}
			}
			this->ip[3]=sf::IpAddress::None;
			this->nbPlayerByIp[3]=0;
			std::cout << "ok deleteplayer fin" << std::endl;
		}
		
	}

	void NetworkManager::addSocket(sf::TcpSocket* socket) {
		this->mutexClients.lock();
		this->clients.push_back(socket);
		this->mutexClients.unlock();
	}

	/*surcharge des opérateurs de flux des sf::Packet*/
	sf::Packet& operator<<(sf::Packet& packet, SBoard& b){

		/*Ajout des Boxes*/
		packet << (int)b.boxes.size();
		for (unsigned int i=0;i<b.boxes.size();i++){
			packet << b.boxes[i].x << b.boxes[i].y;
		}

		/*Ajout des Bonus*/
		packet << (int)b.bonus.size();
		for(unsigned int i=0;i<b.bonus.size();i++){
			packet << b.bonus[i].coords.x << b.bonus[i].coords.y << b.bonus[i].type;
		}

		/*Ajout des explosifs*/
		packet << (int)b.explosives.size();
		for(unsigned int i=0;i<b.explosives.size();i++){
			packet << b.explosives[i].coords.x << b.explosives[i].coords.y << b.explosives[i].type;
		}

		/*ajout des players*/
		packet << (int)b.players.size();
		for (unsigned int i=0;i<b.players.size();i++){
			packet << b.players[i].coords.x << b.players[i].coords.y << b.players[i].orientation << b.players[i].number << b.players[i].state << b.players[i].step;
		}

		/*Ajout des flames*/
		packet << (int)b.flames.size();
		for(unsigned int i=0;i<b.flames.size();i++){			
			packet << b.flames[i].coords.x << b.flames[i].coords.y << b.flames[i].orientation << b.flames[i].step << b.flames[i].location;
		}

		return packet;
	}

	sf::Packet& operator<<(sf::Packet& packet, SKeyPressed& key){
		bool val;
		for(int i=0;i<4;i++){
			for(int j=0;j<7;j++){
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
		for(int i=0;i<j;i++){
			SBonus bonus;
			packet >> bonus.coords.x >> bonus.coords.y >> type;
			bonus.type = (EGameBonus)type;
			board.bonus.push_back(bonus);
		}

		/*Ajout des explosifs}*/
		packet >> j;
		for(int i=0;i<j;i++){
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
		for(int i=0;i<j;i++){
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
		for(int i=0;i<4;i++){
			for(int j=0;j<7;j++){
				packet >> val;
				key.keys[i][j]=val;
			}
		}
		return packet;
	}
}
