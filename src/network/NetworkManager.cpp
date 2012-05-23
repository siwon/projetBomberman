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
//#include "../../include/controller/ControllerManager.hpp"
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
//#include "../../include/PolyBomberApp.hpp"

using namespace PolyBomber;

NetworkManager::NetworkManager(){
	for(int i=0;i<4;i++){
		this->ip[i] = sf::IpAddress::None;
		this->nbPlayerByIp[i]=0;
		this->scores[i]=0;
	}
	this->paused=0;
	this->started=false;

	this->server=false;
	for(int i=0;i<4;i++){
		for(int j=0;j<7;j++){
			this->keyPressed.keys[i][j] = false;
		}
	}

	//this->controller = PolyBomberApp::getIControllerToNetwork();
	this->gameEngine = NULL;
}

NetworkManager::~NetworkManager(){
	this->clients.erase(this->clients.begin(),this->clients.end());
	this->packets.erase(this->packets.begin(),this->packets.end());
	this->players.erase(this->players.begin(),this->players.end());
}

SKeyPressed NetworkManager::getKeysPressed(){
	SKeyPressed keys;
	if(this->server){
		SKeyPressed keyPress = this->controller->getKeysPressed();
		memcpy(&).keys,&keyPress.keys, sizeof(SKeyPressed));
		// chercher le nombre de joueur sur le réseau
		unsigned int nbPlayerDone =0;
		for(unsigned int i=0;i<this->players.size();i++){
			if(this->players[i].getIp() == sf::IpAddress::LocalHost)
				nbPlayerDone++;
		}
		// pour chaque joueur en dehors du reseau, demander ces touches
		for(int i=0;i<4;i++){ // on parcourt le tableau d'ip
			if(this->nbPlayerByIp[i]){ // s'il y a une adresse d'enregistrée
				this->mutexClients.lock();
				sf::TcpSocket& client = this->findSocket(this->ip[i]);
				client.send(this->createPacket(3));
				this->mutexClients.unlock();
				std::list<sf::Packet>::iterator it2 = waitPacket(3, client.getRemoteAddress());
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
		}
		//verification de la pause par un joueur
		if(this->paused){
			if(this->keyPressed.keys[this->paused - 1][GAME_PAUSE]) // il était en pause et l'enlève
				this->paused=0;
		} else {
			int i=0;
			while(i<4 && !this->paused){
				if(this->keyPressed.keys[i][GAME_PAUSE])
					this->paused=i+1;
				else
					i++;
			}
		}
	} else { // on est le client
		//message d'erreur car le client ne peut demander les touche au gameEngine
		std::cerr << "le client ne peut demander les touches au gameEngine" << std::endl;
	}

	return this->keyPressed;
}

int NetworkManager::isPaused(){
	int result;
	if(this->server)
		result = this->paused;
	else {
		//demander au serveur
		this->mutexClients.lock();
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(7));
		this->mutexClients.unlock();
		std::list<sf::Packet>::iterator it2 = waitPacket(7, client->getRemoteAddress());
		sf::Packet& thePacket = *it2;
		int num;
		std::string ip;
		thePacket >> num >> ip  >> result;
		this->packets.erase(it2);
	}
	return result;
}

void NetworkManager::joinGame(std::string ip){
	this->server=false;
	sf::TcpSocket* server = new sf::TcpSocket;
	if(server->connect(ip, 55001) == sf::Socket::Error){
		std::cerr << "erreur de connection au serveur " << ip << std::endl;
	} else {
		this->mutexClients.lock();
		this->clients.push_back(server);
		this->mutexClients.unlock();
	}
	sf::Thread thread(&NetworkManager::listenToServer, this);
	thread.launch();
}

int NetworkManager::getFreeSlots(){
	int result;
	if(this->server){
		result = (4 - this->players.size());
	} else {
		// demande au serveur
		this->mutexClients.lock();
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(5));
		this->mutexClients.unlock();
		std::list<sf::Packet>::iterator it2 = waitPacket(5, client->getRemoteAddress());
		sf::Packet& thePacket = *it2;
		int num;
		std::string ip;
		thePacket >> num >> ip  >> result;
		this->packets.erase(it2);
	}
	return result;
}

void NetworkManager::setBookedSlots(unsigned int nb, sf::IpAddress ip){
	if(this->server){
		if(ip != sf::IpAddress::getLocalAddress()){
			int i =0;
			while(i<4 && !(this->ip[i] == sf::IpAddress::None)){
				i++;
			}
			this->ip[i]=ip;
		}
		for(unsigned int i=0;i<nb;i++){
			DataPlayer* aPlayer = new DataPlayer(i, ip);
			this->players.push_back(*aPlayer);
		}
	} else {
		// envoyer au serveur
		this->mutexClients.lock();
		std::list<sf::TcpSocket*>::iterator it = this->clients.begin();
		sf::TcpSocket* client = *it;
		client->send(createPacket(15,nb)); // pas besoin de réponse
		this->mutexClients.unlock();
	}
}

void NetworkManager::setPlayerName(std::string names[4], sf::IpAddress ip){
	if(this->server){
		int i=0;//indice sur le vecteur de joueur
		int j=0;//indice sur le tableau de nom
		while(i<4 && !(ip==this->players[i].getIp())){ //recherche la bonne adresse ip
			i++;
		}
		while(j<(4-i) && !(names[j] == "")){
			this->players[j].setName(names[j]);
			j++;
		}
	} else { // envoyer la demande au serveur
		this->mutexClients.lock();
		std::list<sf::TcpSocket*>::iterator it = this->clients.begin();
		sf::TcpSocket* client = *it;
		sf::Packet packet; //paquet créé sur place car modification de createPacket pour passer les params
		packet << 17 << sf::IpAddress::getLocalAddress().toString();
		for(int i=0;i<4;i++){
			packet << names[i];
		}
		client->send(packet); // pas besoin de réponse
		this->mutexClients.unlock();
	}
}

int* NetworkManager::getScores(){
	if(!this->server){
		//demander au serveur
		this->mutexClients.lock();
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(7));
		this->mutexClients.unlock();
		std::list<sf::Packet>::iterator it2 = waitPacket(7, client->getRemoteAddress());
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
			this->mutexClients.lock();
			std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
			sf::TcpSocket* client = *it1;
			client->send(createPacket(11));
			this->mutexClients.unlock();
			std::list<sf::Packet>::iterator it2 = waitPacket(9, client->getRemoteAddress());
			sf::Packet& thePacket = *it2;
			int num;
			std::string ip;
			thePacket >> num >> ip  >> result;
			this->packets.erase(it2);
	}
	return result;
}

void NetworkManager::startGame() {//threader la fonction de run
	if(this->server){
		sf::Thread thread(&IGameEngineToNetwork::run, this->gameEngine);
		thread.launch();
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
	//this->gameEngine = PolyBomberApp::getIGameEngineToNetwork();
	memcpy(&this->gameConfig,&pGameConfig, sizeof(SGameConfig));
	memcpy(this->gameConfig.playersName,pGameConfig.playersName, sizeof(std::string)*4);
	memcpy(this->gameConfig.nbBonus,pGameConfig.nbBonus, sizeof(unsigned int)*18);
	this->server=true;//l'ordinateur sera le serveur

	this->gameEngine->setGameConfig(this->gameConfig);// on envoie également au gameEngine
	// création du listener qui écoute tous les clients
	sf::Thread thread(&NetworkManager::createServerSocket, this);
	thread.launch();
}

SBoard NetworkManager::getBoard(){
	if(this->server){
		return this->gameEngine->getBoard();
	} else {
		//demande au serveur
		this->mutexClients.lock();
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(1));
		this->mutexClients.unlock();
		std::list<sf::Packet>::iterator it2 = waitPacket(1, client->getRemoteAddress());
		sf::Packet& thePacket = *it2;
		SBoard aBoard;
		thePacket >> aBoard;
		this->packets.erase(it2);
		return aBoard;
	}
	
}

int NetworkManager::isFinished(){
	int result;
	if(this->server){
		result = this->gameEngine->isFinished();
	} else {
	//demander au réseau
		this->mutexClients.lock();
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(9));
		this->mutexClients.unlock();
		std::list<sf::Packet>::iterator it2 = waitPacket(9, client->getRemoteAddress());
		sf::Packet& thePacket = *it2;
		int num;
		std::string ip;
		thePacket >> num >> ip  >> result;
		this->packets.erase(it2);
	}
	return result;
}


/******méthode ne provenant pas d'interface***/

/*!
 * \brief Création d'un Listener pour le serveur
 */
void NetworkManager::createServerSocket(){
	sf::TcpListener listener;
	sf::SocketSelector selector;

	listener.listen(55001);
	selector.add(listener);

	// Endless loop that waits for new connections
	 while (true)
	 {
		 // Make the selector wait for data on any socket
		 if (selector.wait())
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
					 this->mutexClients.lock();
					 this->clients.push_back(client);
					 this->mutexClients.unlock();

					 // Add the new client to the selector so that we will
					 // be notified when he sends something
					 selector.add(*client);
				 }
			 }
			 else
			 {
				 // The listener socket is not ready, test all other sockets (the clients)
				 this->mutexClients.lock();
				 for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
				 {
					 sf::TcpSocket& client = **it;
					 if (selector.isReady(client))
					 {
						 // The client has sent some data, we can receive it
						 sf::Packet* packet = new sf::Packet;
						 if (client.receive(*packet) == sf::Socket::Done)
						 {
							 //Vérifier le premier numéro s'il est impaire
							 sf::Packet testPacket = *packet; // recopie du paquet reçu
							 int num;
							 testPacket >> num;
							 if(num%2){ // si c'est impaire
								 decryptPacket(*packet);
							 } else { //ajouter le packet !!!!! mutex !!!!
								 this->mutexPacket.lock();
								 this->packets.push_back(*packet);
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
	std::list<sf::TcpSocket*>::iterator it = clients.begin();
	sf::TcpSocket* server = *it;
	while(true){
		sf::Packet* packet = new sf::Packet;
		if (server->receive(*packet) == sf::Socket::Done){
			//Vérifier le premier numéro s'il est impaire
			sf::Packet testPacket = *packet; // recopie du paquet reçu
			int num;
			testPacket >> num;
			if(num%2){ // si c'est impaire
				decryptPacket(*packet);
			} else { //ajouter le packet !!!!! mutex !!!!
				this->mutexPacket.lock();
				this->packets.push_back(*packet);
				this->mutexPacket.unlock();
			}
		}
	}
}

sf::Packet NetworkManager::createPacket(int i, int j){
	sf::Packet packet;
	sf::IpAddress ipLocal = sf::IpAddress::getLocalAddress();
	packet << i << ipLocal.toString();
	switch(i){
		case 1 : { // demande de getboard d'un client
			
			break;
				 }
		case 2 : { // envoi d'un SBoard
			if(this->server){
				packet <<  this->gameEngine->getBoard();
			} else {
				std::cerr << "le plateau ne peut être obtenu car un Client n'a pas accès à un GameEngine" << std::endl;
			}
			break;
				 }
		case 3 : { // demande des touches pressées

			break;
				 }
		case 4 : { // envoi d'un SKeyPressed
			if(this->server)
				packet << this->getKeysPressed();
			else
				packet << this->controller->getKeysPressed();
			break;
				 }
		case 5 : { // demande des slots disponible

			break;
				 }
		case 6 : { // envoi des slots disponibles
			packet << this->getFreeSlots();
			break;
				 }
		case 7 : { // demande s'il y a une pause

			break;
				 }
		case 8 : { // envoi s'il y a une pause
			packet << this->paused;
			break;
				 }
		case 9 : { // demande s'il c'est fini

			break;
				 }
		case 10 : { // envoi si c'est fini
			packet << this->isFinished();
			break;
				 }
		case 11 : { // demande si c'est commencé

			break;
				 }
		case 12 : { // envoi si c'est commencé
			packet << this->isStarted();
			break;
				 }
		case 13 : { // demande du score

			break;
				 }
		case 14 : { // envoi du score
			for(int i=0;i<4;i++){
				packet << this->scores[i];
			}
			break;
				 }

		case 15 : { // envoi réservation d'un slot
			packet << j;
			break;
				 }

	}
	return packet;
}

sf::TcpSocket& NetworkManager::findSocket(sf::IpAddress& ip){
	bool find = false;
	int i =0;
	std::list<sf::TcpSocket*>::iterator it = clients.begin();
	while( it != clients.end() && !find){
		sf::TcpSocket& client = **it;
		if(client.getRemoteAddress()== ip)
			find=true;
		else
			it++;
	}
	if(!find)
		std::cerr << "Le serveur n'a pas pu trouver le socket pour communiquer avec le client "<< ip.toString() << std::endl;
	return **it;
}

std::list<sf::Packet>::iterator NetworkManager::waitPacket(int num, sf::IpAddress& ipAddr){
	bool find=false;
	int type;
	std::string ip;
	std::list<sf::Packet>::iterator it;
	while(!find){
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
	return it;
}

void NetworkManager::decryptPacket(sf::Packet& packet){
	int num;
	sf::Packet result;
	std::string ip;
	packet >> num >> ip;
	if(num < 15){ // c'est une demande qui nécessite une réponse
		sf::IpAddress ip2 = ip;
		result = createPacket(num+1);
		sf::TcpSocket& client = this->findSocket(ip2);
		client.send(result);
	} else if(num==15){ // c'est un 15
		int j;
		packet >> j;
		setBookedSlots(j, ip);
	} else { // c'est un 17
		std::string names[4];
		for(int i=0;i<4;i++){
			packet >> names[i];
		}
		setPlayerName(names, ip);
	}
}



/*surcharge des opérateurs de flux des sf::Packet*/
sf::Packet& operator<<(sf::Packet& packet, SBoard& b){
	std::vector<sf::Vector2<int>> boxes = b.boxes;
	std::vector<SBonus> bonus = b.bonus;
	std::vector<SExplosive> explosive = b.explosives;
	std::vector<SPlayer> player= b.players;
	std::vector<SFlame> flame = b.flames;

	/*Ajout des Boxes*/
	packet << boxes.size();
	for (unsigned int i=0;i<boxes.size();i++){
		sf::Vector2<int> tempVect = boxes[i];
		packet << tempVect.x << tempVect.y;
	}

	/*Ajout des Bonus*/
	packet << bonus.size();
	for(unsigned int i=0;i<bonus.size();i++){
		sf::Vector2<int> tempCoord = bonus[i].coords;
		int tempBonus = bonus[i].type;
		packet << tempCoord.x << tempCoord.y << tempBonus;
	}

	/*Ajout des explosifs*/
	packet << explosive.size();
	for(unsigned int i=0;i<explosive.size();i++){
		sf::Vector2<int> tempCoord = explosive[i].coords;
		int tempExplo = explosive[i].type;
		packet << tempCoord.x << tempCoord.y << tempExplo;
	}

	/*ajout des players*/
	packet << player.size();
	for (unsigned int i=0;i<player.size();i++){
		sf::Vector2<int> tempCoord = player[i].coords;
		int tempOrient = player[i].orientation;
		unsigned int tempNum = player[i].number;
		int tempState = player[i].state;
		unsigned int tempStep = player[i].step;

		packet << tempCoord.x << tempCoord.y << tempOrient << tempNum << tempState << tempStep;
	}

	/*Ajout des flames*/
	packet << flame.size();
	for(unsigned int i=0;i<flame.size();i++){
		sf::Vector2<int> tempCoord = flame[i].coords;
		int tempOrient = flame[i].orientation;
		unsigned int tempStep = flame[i].step;
		int tempLocat = flame[i].location;
		
		packet << tempCoord.x << tempCoord.y << tempStep << tempLocat;
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
