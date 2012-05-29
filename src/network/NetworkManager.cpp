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
//#include "controller/ControllerManager.hpp"
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
//#include "PolyBomberApp.hpp"

using namespace PolyBomber;

NetworkManager::NetworkManager(){
	this->initialize();
}

NetworkManager::~NetworkManager(){
	this->setConnect(false);

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

	this->server=false;
	for(int i=0;i<4;i++){
		for(int j=0;j<7;j++){
			this->keyPressed.keys[i][j] = false;
		}
	}

	//FIXME: this->controller = PolyBomberApp::getIControllerToNetwork();
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
	client->send(packet);
		
	this->mutexClients.unlock();

	sf::IpAddress address = client->getRemoteAddress();
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
			if(this->nbPlayerByIp[i]){ // s'il y a une adresse d'enregistrée
				try {
					this->mutexClients.lock();
					sf::TcpSocket* client = this->findSocket(this->ip[i]);
					sf::Packet packet = this->createPacket(3);
					client->send(packet);
		
					this->mutexClients.unlock();

					sf::IpAddress address = client->getRemoteAddress();
					std::list<sf::Packet>::iterator it2 = waitPacket(3, address);

					sf::Packet& thePacket =  *it2 ;
					thePacket >> keys; // récupération des touches envoyées
					//ajouter ses touches.
					for(int j=0;j<this->nbPlayerByIp[i];j++){
						for(int k=0;k<7;k++){
							this->keyPressed.keys[nbPlayerDone][k] = keys.keys[j][k];
						}
						nbPlayerDone++;
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
		if(client->send(packet) != sf::TcpSocket::Done) // pas besoin de réponse
			throw PolyBomberException("l'envoie de la reprise à échoué");
		this->mutexClients.unlock();
	}
}

void NetworkManager::cancel(){
	if(this->isConnected()){
		sf::Packet packet;
		packet = createPacket(-1);
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

		// FIXME: this->gameEngine->resetConfig(); // stop le thread run() s'il est commencé
		
		//terminer les threads 
		this->setConnect(false);

		// vider les vecteurs
		this->players.erase(this->players.begin(),this->players.end());
		this->clients.erase(this->clients.begin(),this->clients.end());
		this->packets.erase(this->packets.begin(),this->packets.end());
		// et libérer les threads
		if(this->threadClient != NULL)
		delete this->threadClient;
		if(this->threadRun != NULL)
			delete this->threadRun;
		if(this->threadServer != NULL)
			delete this->threadServer;

		
	}
	this->initialize();
}

void NetworkManager::joinGame(std::string ip){
	this->server=false;
	sf::TcpSocket* server = new sf::TcpSocket;
	sf::IpAddress ip2 = sf::IpAddress(ip);
	if(server->connect(ip, 2222, sf::milliseconds(100)) != sf::TcpSocket::Done){
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
		try {
		std::list<sf::Packet>::iterator it2 = this->askServer(5);
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
		if(client->send(packet) != sf::TcpSocket::Done) // pas besoin de réponse
			throw PolyBomberException("échec de la réservation de slot");
		this->mutexClients.unlock();
	}
	this->mutexSlots.unlock();
}

void NetworkManager::setPlayerName(std::string names[4]){
	this->setName(names);
}

void NetworkManager::setName(std::string names[4], sf::IpAddress ip){
	this->mutexNames.lock();
	if(this->server){
		int i=0;//indice sur le vecteur de joueur
		int j=0;//indice sur le tableau de nom
		while(!(names[j] == "") && i<4){ // tant qu'il y a des noms à enregistrer
			if(this->players[i].getIp() == ip){
				this->players[i].setName(names[j]);
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
		if(client->send(packet) != sf::TcpSocket::Done) // pas besoin de réponse
			throw PolyBomberException("échec lors de l'envoi des noms");
		this->mutexClients.unlock();
	}
	this->mutexNames.unlock();
}

void NetworkManager::getPlayersName(std::string names[4]){
	if(this->server){
		for(unsigned int i=0;i<4;i++) {
			if(i<players.size())
				names[i]=this->players[i].getName();
			else
				names[i]="";
		}
	} else {
		//envoyer un paquet pour demander les noms aux serveur
			try {
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
			catch (PolyBomberException e){
				std::cerr << e.what() <<std::endl;
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
	//FIXME: this->gameEngine = PolyBomberApp::getIGameEngineToNetwork();

	this->gameConfig = pGameConfig;
	
	this->server=true; //l'ordinateur sera le serveur

	//FIXME: this->gameEngine->setGameConfig(this->gameConfig);// on envoie également au gameEngine
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
					 // Add the new client to the clients list
					 this->addSocket(client);

					 // Add the new client to the selector so that we will
					 // be notified when he sends something
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
	while(this->isConnected()){
		sf::Packet packet;
		if (server->receive(packet) == sf::Socket::Done){
			//Vérifier le premier numéro s'il est impaire
			sf::Packet testPacket = packet; // recopie du paquet reçu
			int num;
			testPacket >> num;
			if(num==-1) {// signal d'arrêt
				this->setConnect(false);
				this->mutexClients.lock();
				this->clients.pop_back(); // il n'y a qu'une seul socket
				this->mutexClients.unlock();
			} else {
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
}

sf::Packet NetworkManager::createPacket(int i, int j){
	sf::Packet packet;
	sf::IpAddress ipLocal = sf::IpAddress::getLocalAddress();
	packet << i << ipLocal.toString();
	switch(i){
		case 1 : // demande de getboard d'un client
			break;
		case 2 : // envoi d'un SBoard
			if(this->server){
				SBoard gameBoard = this->gameEngine->getBoard();
				packet <<  gameBoard;
			} else {
				std::cerr << "le plateau ne peut être obtenu car un Client n'a pas accès à un GameEngine" << std::endl;
			}
			break;
		case 3 : // demande des touches pressées

			break;
		case 4 : // envoi d'un SKeyPressed
			if(this->server){
				SKeyPressed keys = this->getKeysPressed();
				packet << keys;
			} else {
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
	std::vector<sf::TcpSocket*>::iterator it = findSocketIterator(ip);
	return *it;
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
	if(!find)
		throw PolyBomberException ("Le serveur n'a pas pu trouver le socket pour communiquer avec le client "+ip.toString());
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
			if(type==(num+1) && ip==ipAddr.toString()){
				find=true;
			} else {
				it++;
			}
		}
		this->mutexPacket.unlock();
	}
	if(!find){
		throw PolyBomberException("Echec de la réception du paquet de l'expéditeur "+ipAddr.toString()+". Temps d'attente de 100 millisecondes dépassé");
	}
	return it;
}

void NetworkManager::decryptPacket(sf::Packet& packet){
	int num;
	sf::Packet result;
	std::string ip;
	packet >> num >> ip;
	sf::IpAddress ip1(ip);
	std::string names[4];
	switch(num){
	case -1 :
		if(this->server){
			std::cerr << "le client " << ip <<" vient de se déconnecter" << std::endl;
			eraseSocket(ip1);
		} else {
			this->setConnect(false);
		}
		break;
	case 17 :
		for(int i=0;i<4;i++){
			packet >> names[i];
		}
		setName(names, ip1); // methode utilisant des ressources critiques
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
		sf::TcpSocket* client = this->findSocket(ip1);
		if (!client->send(result) == sf::TcpSocket::Done)
			std::cerr << "la réponse n°" << num << " n'à pas pu être renvoyée" << std::endl;
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
	std::vector<sf::TcpSocket*>::iterator it = this->findSocketIterator(ip);
	sf::TcpSocket* socket = *it;
	this->selector.remove(*socket);
	this->mutexClients.lock();
	this->clients.erase(it);
	this->mutexClients.unlock();
	this->deletePlayer(ip);
}

void NetworkManager::deletePlayer(sf::IpAddress& ip){
	for(unsigned int i=0;i<players.size();i++){

	}
}

void NetworkManager::addSocket(sf::TcpSocket* socket) {
	this->mutexClients.lock();
	this->clients.push_back(socket);
	this->mutexClients.unlock();
}

namespace PolyBomber
{
	/*surcharge des opérateurs de flux des sf::Packet*/
	sf::Packet& operator<<(sf::Packet& packet, SBoard& b){
		std::vector<sf::Vector2<int> > boxes = b.boxes;
		std::vector<SBonus> bonus = b.bonus;
		std::vector<SExplosive> explosive = b.explosives;
		std::vector<SPlayer> player= b.players;
		std::vector<SFlame> flame = b.flames;

		/*Ajout des Boxes*/
		packet << (int)boxes.size();
		for (unsigned int i=0;i<boxes.size();i++){
			sf::Vector2<int> tempVect = boxes[i];
			packet << tempVect.x << tempVect.y;
		}

		/*Ajout des Bonus*/
		packet << (int)bonus.size();
		for(unsigned int i=0;i<bonus.size();i++){
			sf::Vector2<int> tempCoord = bonus[i].coords;
			int tempBonus = bonus[i].type;
			packet << tempCoord.x << tempCoord.y << tempBonus;
		}

		/*Ajout des explosifs*/
		packet << (int)explosive.size();
		for(unsigned int i=0;i<explosive.size();i++){
			sf::Vector2<int> tempCoord = explosive[i].coords;
			int tempExplo = explosive[i].type;
			packet << tempCoord.x << tempCoord.y << tempExplo;
		}

		/*ajout des players*/
		packet << (int)player.size();
		for (unsigned int i=0;i<player.size();i++){
			sf::Vector2<int> tempCoord = player[i].coords;
			int tempOrient = player[i].orientation;
			unsigned int tempNum = player[i].number;
			int tempState = player[i].state;
			unsigned int tempStep = player[i].step;

			packet << tempCoord.x << tempCoord.y << tempOrient << tempNum << tempState << tempStep;
		}

		/*Ajout des flames*/
		packet << (int)flame.size();
		for(unsigned int i=0;i<flame.size();i++){
			sf::Vector2<int> tempCoord = flame[i].coords;
			int tempOrient = flame[i].orientation;
			unsigned int tempStep = flame[i].step;
			int tempLocat = flame[i].location;
			
			packet << tempCoord.x << tempCoord.y << tempOrient << tempStep << tempLocat;
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
			sf::Vector2<int>* coord = new sf::Vector2<int>;
			packet >> coord->x >> coord->y;
			board.boxes.push_back(*coord);
		}

		/*Ajout des Bonus*/
		packet >> j;
		for(int i=0;i<j;i++){
			SBonus* bonus = new SBonus;
			packet >> bonus->coords.x >> bonus->coords.y >> type;
			bonus->type = (EGameBonus)type;
			board.bonus.push_back(*bonus);
		}


		/*Ajout des explosifs}*/
		packet >> j;
		for(int i=0;i<j;i++){
			SExplosive* explo = new SExplosive;
			packet >> explo->coords.x >> explo->coords.y >> type;
			explo->type = (EExplosiveType)type;
			board.explosives.push_back(*explo);
		}

		/*ajout des players*/
		packet >> j;
		int state;
		for(int i=0;i<j;i++){
			SPlayer* player = new SPlayer;
			packet >> player->coords.x >> player->coords.y >> type >> player->number >> state >> player->step;
			player->orientation = (EOrientation)type;
			player->state = (EPlayerState)state;
			board.players.push_back(*player);
		}

		/*Ajout des flames*/
		packet >> j;
		int location;
		for(int i=0;i<j;i++){
			SFlame* flame = new SFlame;
			
			packet >> flame->coords.x >> flame->coords.y >> type >> flame->step >> location ;
			
			flame->orientation = (EOrientation)type;
			flame->location = (EFlameLocation)location;
			board.flames.push_back(*flame);
		}

		return packet;
	}

	sf::Packet& operator>>(sf::Packet& packet, SKeyPressed& key){
		bool val;
		for(int i=0;i<4;i++){
			for(int j=0;j<7;i++){
				packet >> val;
				key.keys[i][j]=val;
			}
		}
		return packet;
	}
}
