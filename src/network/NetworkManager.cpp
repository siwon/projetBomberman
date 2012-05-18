/*!
 * \file NetworkManager.cpp
 * \brief Implémentation de classe NetworkManager
 * \author Brice GUILLERMIC
 */
#define NBNETWORKMAX 4

// Bibliothèques SFML
#include <SFML/Network.hpp>

//Headers
#include <iostream>
#include <vector>
#include "../../include/network/NetworkManager.hpp"
#include "../../include/controller/ControllerManager.hpp"
#include "../../include/SKeyPressed.hpp"
#include "../../include/SBonus.hpp"
#include "../../include/EGameBonus.hpp"
#include "../../include/SExplosive.hpp"
#include "../../include/EExplosiveType.hpp"
#include "../../include/SPlayer.hpp"
#include "../../include/EOrientation.hpp"
#include "../../include/EPlayerState.hpp"
#include "../../include/SFlame.hpp"

using namespace PolyBomber;

SKeyPressed NetworkManager::getKeysPressed(){
	SKeyPressed keys;
	if(this->server){
		memcpy(&this->keyPressed.keys,&this->controller->getKeysPressed().keys, sizeof(SKeyPressed));
		// chercher le nombre de joueur sur le réseau
		unsigned int nbPlayerDone =0;
		for(unsigned int i=0;i<this->players.size();i++){
			if(this->players[i].getIp() == sf::IpAddress::LocalHost)
				nbPlayerDone++;
		}
		// pour chaque joueur en dehors du reseau, demander ces touches
		for(int i=0;i<NBNETWORKMAX;i++){
			if(this->nbPlayerByIp[i]){
				sf::TcpSocket& client = this->findSocket(this->ip[i]);
				client.send(this->createPacket(3));
				std::list<sf::Packet>::iterator it2 = waitPacket(3, client.getRemoteAddress());
				sf::Packet& thePacket =  *it2 ;
				thePacket >> keys;
				//ajouter ses touches.
				for(int j=0;j<this->nbPlayerByIp[i];j++){
					for(int k=0;k<7;k++){
						this->keyPressed.keys[nbPlayerDone][k] = keys.keys[j][k];
					}
					nbPlayerDone++;
					
				}
			}
		}
	} else {
		//demander au serveur
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(3));
		std::list<sf::Packet>::iterator it2 = waitPacket(3, client->getRemoteAddress());
		sf::Packet& thePacket = *it2;
		thePacket >> this->keyPressed;
		this->packets.erase(it2);
	}
	return this->keyPressed;
}

int NetworkManager::isPaused(){
	int result;
	if(this->server)
		result = this->paused;
	else {
		//demander au serveur
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(7));
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
		this->clients.push_back(server);
	}
}

int NetworkManager::getFreeSlots(){
	int result;
	if(this->server){
		result = (4 - this->players.size());
	} else {
		// demande au serveur
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(5));
		std::list<sf::Packet>::iterator it2 = waitPacket(5, client->getRemoteAddress());
		sf::Packet& thePacket = *it2;
		int num;
		std::string ip;
		thePacket >> num >> ip  >> result;
		this->packets.erase(it2);
	}
	return result;
}

void NetworkManager::setBookedSlots(unsigned int nb){
	if(this->server){
		for(unsigned int i=0;i<nb;i++){
			DataPlayer* aPlayer = new DataPlayer(i, sf::IpAddress::LocalHost);
			this->players.push_back(*aPlayer);
		}
	} else {
		// envoyer au serveur
		std::list<sf::TcpSocket*>::iterator it = this->clients.begin();
		sf::TcpSocket* client = *it;
		client->send(createPacket(11,nb)); // pas besoin de réponse
	}
}
//void NetworkManager::setPlayerName(string[]);
//int* NetworkManager::getScores();

bool NetworkManager::isStarted(){
	return this->started;
}
void NetworkManager::startGame() {//threader la fonction de run
	if(this->server){
		this->gameEngine->run();
		this->started=true;
	}
}

std::string NetworkManager::getIpAddress(){
	sf::IpAddress address = sf::IpAddress::getLocalAddress();
	return address.toString();
}

void NetworkManager::setGameConfig(SGameConfig& pGameConfig){
	memcpy(&this->gameConfig,&pGameConfig, sizeof(SGameConfig));
	this->server=true;//l'ordinateur sera le serveur

	this->gameEngine->setGameConfig(this->gameConfig);// on envoie également au gameEngine
	this->createServerSocket(); // création du listener qui écoute tous les clients

}

SBoard NetworkManager::getBoard(){
	if(this->server){
		memcpy(&this->board,&gameEngine->getBoard(), sizeof(SBoard));
	} else {
		//demande au serveur
		std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
		sf::TcpSocket* client = *it1;
		client->send(createPacket(1));
		std::list<sf::Packet>::iterator it2 = waitPacket(1, client->getRemoteAddress());
		sf::Packet& thePacket = *it2;
		thePacket >> this->board;
		this->packets.erase(it2);
	}
	return this->board;
}

int NetworkManager::isFinished(){
	int result;
	if(this->server){
		if(this->started && this->gameEngine->isFinished()==1){
			this->started=false;
			result = 1;
		} else
			result = 0;
		} else {
		//demander au réseau
			std::list<sf::TcpSocket*>::iterator it1 = this->clients.begin();
			sf::TcpSocket* client = *it1;
			client->send(createPacket(9));
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

sf::IpAddress NetworkManager::getIp(){
	if(this->server){
		return sf::IpAddress::LocalHost;
	} else {
		return sf::IpAddress::getLocalAddress();
	}
}

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
					 this->clients.push_back(client);

					 // Add the new client to the selector so that we will
					 // be notified when he sends something
					 selector.add(*client);
				 }
			 }
			 else
			 {
				 // The listener socket is not ready, test all other sockets (the clients)
				 for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
				 {
					 sf::TcpSocket& client = **it;
					 if (selector.isReady(client))
					 {
						 // The client has sent some data, we can receive it
						 sf::Packet* packet;
						 if (client.receive(*packet) == sf::Socket::Done)
						 {
							 //ajouter le packet !!!!! mutex !!!!
							 this->packets.push_back(*packet);
						 }
					 }
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
		case 1 : { // demande de getboard d'un client
			
			break;
				 }
		case 2 : { // envoi d'un SBoard
			if(this->server){
				packet <<  this->board;
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
		case 11 : { // envoi réservation d'un slot
			packet << j;
			break;
				 }

	}
	return packet;
}

std::list<sf::Packet>::iterator NetworkManager::waitPacket(int num, sf::IpAddress& ipAddr){
	bool find=false;
	int type;
	std::string ip;
	std::list<sf::Packet>::iterator it;
	while(!find){
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
	}
	return it;
}

sf::Packet& operator<<(sf::Packet& packet, const SBoard& b){
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

sf::Packet& operator<<(sf::Packet& packet, const SKeyPressed& key){
	bool val;
	for(int i=0;i<4;i++){
		for(int j=0;j<7;j++){
			val = key.keys[i][j];
			packet << val;
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
	return **it;
}

sf::Packet& operator>>(sf::Packet& packet, SBoard& board){

	/*Ajout des Boxes*/
	unsigned int j;
	int type;
	packet >> j;
	for(unsigned i=0;i<j;i++){
		sf::Vector2<int>* coord = new sf::Vector2<int>;
		packet >> coord->x >> coord->y;
		board.boxes.push_back(*coord);
	}

	/*Ajout des Bonus*/
	packet >> j;
	for(unsigned int i=0;i<j;i++){
		SBonus* bonus = new SBonus;
		packet >> bonus->coords.x >> bonus->coords.y >> type;
		bonus->type = type;
		board.bonus.push_back(*bonus);
	}


	/*Ajout des explosifs}*/
	packet >> j;
	SExplosive* explo = new SExplosive;
	for(unsigned int i=0;i<j;i++){
		packet >> explo->coords.x >> explo->coords.y >> type;
		explo->type = type;
		board.explosives.push_back(*explo);
	}

	/*ajout des players*/
	packet >> j;
	SPlayer* player = new SPlayer;
	for(unsigned int i=0;i<j;i++){
		packet >> player->coords.x >> player->coords.y >> type >> player->number >> player->state >> player->step;
		player->orientation = type;
		board.players.push_back(*player);
	}

	/*Ajout des flames*/
	packet >> j;
	SFlame* flame = new SFlame;
	for(unsigned int i=0;i<j;i++){
		packet >> flame->coords.x >> flame->coords.y >> type >> flame->step >> flame->location;
		flame->orientation =type;
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

