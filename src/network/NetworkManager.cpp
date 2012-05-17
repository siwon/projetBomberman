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
	memcpy(&this->keyPressed,&this->controller->getKeysPressed(), sizeof(SKeyPressed));
	// chercher le nombre de joueur sur le réseau
	//chercher le nombre de joueur total
	// pour chaque joueur en dehors du reseau, demander ces touches
	//ajouter ses touches.
}

int NetworkManager::isPaused(){
	if(this->server)
		return this->paused;
	else {
		//demander au serveur
		std::list<sf::TcpSocket*>::iterator client = this->clients.begin();
		*client->send(createPacket(7));
		sf::Packet thePacket = waitPacket(7, *client->getRemoteAddress());
	}
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
	if(this->server){
		return (4 - this->players.size());
	} else {
		// demande au serveur
		std::list<sf::TcpSocket*>::iterator client = this->clients.begin();
		*client->send(createPacket(5));
		sf::Packet thePacket = waitPacket(5, *client->getRemoteAddress());
	}
}

void NetworkManager::setBookedSlots(unsigned int nb){
	if(this->server){
		for(unsigned int i=0;i<nb;i++){
			DataPlayer* aPlayer = new DataPlayer(i, sf::IpAddress::getLocalAddress());
			this->players.push_back(*aPlayer);
		}
	} else {
		// envoyer au serveur
		std::list<sf::TcpSocket*>::iterator client = this->clients.begin();
		*client->send(createPacket(11,nb)); // pas besoin de réponse
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
		return this->board;
	} else {
		std::list<sf::TcpSocket*>::iterator client = this->clients.begin();
		*client->send(createPacket(1));
		sf::Packet thePacket = waitPacket(1, *client->getRemoteAddress());
	}
}

int NetworkManager::isFinished(){
	if(this->server){
		if(this->started && this->gameEngine->isFinished()==1){
			this->started=false;
			return 1;
		} else
			return 0;
		} else {
		//demander au réseau
			std::list<sf::TcpSocket*>::iterator client = this->clients.begin();
			*client->send(createPacket(9));
			sf::Packet thePacket = waitPacket(9, *client->getRemoteAddress());
	}
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
//void NetworkManager::decryptPacket(sf::Packet);

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
	for(int i=0;i<4;i++){
		for(int j=0;j<7;j++){
			packet << key.keys[i][j];
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

sf::Packet& NetworkManager::waitPacket(int num, sf::IpAddress& ipAddr){
	bool find=false;
	int type;
	std::string ip;
	std::list<sf::Packet>::iterator it = this->packets.begin();
	while(!find){
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
	return *it;
}

