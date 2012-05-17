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
	return this->controller->getKeysPressed();
}

int NetworkManager::isPaused(){
	return this->paused;
}

//void NetworkManager::joinGame(string ip);
//int NetworkManager::getFreeSlots();
//void NetworkManager::setBookedSlots(unsigned int nb);
//void NetworkManager::setPlayerName(string[]);
//int* NetworkManager::getScores();
bool NetworkManager::isStarted(){
	return this->started;
}
//void NetworkManager::startGame(); //threader la fonction de run
std::string NetworkManager::getIpAddress(){
	sf::IpAddress address = sf::IpAddress::getLocalAddress();
	return address.toString();
}

void NetworkManager::setGameConfig(SGameConfig& pGameConfig){
	memcpy(&this->gameConfig,&pGameConfig, sizeof(SGameConfig));

	if(this->gameConfig.isLocal){ //l'ordinateur sera le serveur
		this->gameEngine->setGameConfig(this->gameConfig);
		this->createServerSocket(); // création du listener qui écoute tous les clients
	} else {
		// créer le socket vers le serveur
	}
}

SBoard NetworkManager::getBoard(){
	if(this->gameConfig.isLocal){
		memcpy(this->board,gameEngine->getBoard(), sizeof(SBoard));
		return this->board;
	} else {
		// envoyer une demande de getBoard au serveur
	}
}

int NetworkManager::isFinished(){
	if(this->started && this->gameEngine->isFinished()==1){
		this->started=false;
		return 1;
	} else
		return 0;
}


/******méthode ne provenant pas d'interface***/

sf::IpAddress NetworkManager::getIp(){
	if(this->gameConfig.isLocal){
		return sf::IpAddress::LocalHost;
	} else {
		return sf::IpAddress::getLocalAddress();
	}
}

/*!
 * \brief Création d'un socket entre le client et le serveur
 */
void NetworkManager::createSocket(sf::IpAddress ip){
	sf::TcpSocket* server = new sf::TcpSocket;
	if(server->connect(ip, 55001) == sf::Socket::Error){
		std::cerr << "erreur de connection au serveur " << ip.toString << std::endl;
	} else {
		this->clients.push_back(server);
	}
}

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
						 sf::Packet packet;
						 if (client.receive(packet) == sf::Socket::Done)
						 {
							 //décrypter le packet
							 decryptPacket(packet);
						 }
					 }
				 }
			 }
		 }
	 }
}
sf::Packet NetworkManager::createPacket(int i){
	sf::Packet packet;
	sf::IpAddress ipLocal = sf::IpAddress::getLocalAddress();
	packet << i << ipLocal.toString();
	switch(i){
		case 1 : { // demande de getboard d'un client
			
			break;
				 }
		case 2 : { // envoi d'un SBoard
			if(this->gameConfig.isLocal){
		
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

	}
	return packet;
}
//void NetworkManager::decryptPacket(sf::Packet);
//void NetworkManager::sendPacket(sf::Packet, sf::IpAddress);
sf::Packet& operator<<(sf::Packet& packet, const SBoard& b){
	std::vector<sf::Vector2<int>> boxes = b.boxes;
	std::vector<SBonus> bonus = b.bonus;
	std::vector<SExplosive> explosive = b.explosives;
	std::vector<SPlayer> player= b.players;
	std::vector<SFlame> flame = b.flames;

	/*Ajout des Boxes*/
	packet << boxes.size();
	for (int i=0;i<boxes.size();i++){
		sf::Vector2<int> tempVect = boxes[i];
		packet << tempVect.x << tempVect.y;
	}

	/*Ajout des Bonus*/
	packet << bonus.size();
	for(int i=0;i<bonus.size();i++){
		sf::Vector2<int> tempCoord = bonus[i].coords;
		int tempBonus = bonus[i].type;
		packet << tempCoord.x << tempCoord.y << tempBonus;
	}

	/*Ajout des explosifs*/
	packet << explosive.size();
	for(int i=0;i<explosive.size();i++){
		sf::Vector2<int> tempCoord = explosive[i].coords;
		int tempExplo = explosive[i].type;
		packet << tempCoord.x << tempCoord.y << tempExplo;
	}

	/*

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