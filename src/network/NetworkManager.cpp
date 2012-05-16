/*!
 * \file NetworkManager.cpp
 * \brief Implémentation de classe NetworkManager
 * \author Brice GUILLERMIC
 */

// Bibliothèques SFML
#include <SFML/Network.hpp>

//Headers
#include "../../include/network/NetworkManager.hpp"
#include "../../include/controller/ControllerManager.hpp"
#include "../../include/SKeyPressed.hpp"

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
	if(this->gameConfig.isLocal){
		this->gameEngine->setGameConfig(this->gameConfig);
		this->createListener();
	}
}

SBoard NetworkManager::getBoard(){
	return this->gameEngine->getBoard();
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

void NetworkManager::createSocket(sf::IpAddress){
	
}

void NetworkManager::createListener(){
	this->listener.listen(55001);
	this->selector.add(listener);

	// Endless loop that waits for new connections
	 while (true)
	 {
		 // Make the selector wait for data on any socket
		 if (this->selector.wait())
		 {
			 // Test the listener
			 if (selector.isReady(listener))
			 {
				 // The listener is ready: there is a pending connection
				 sf::TcpSocket* client = new sf::TcpSocket;
				 if (listener.accept(*client) == sf::Socket::Done)
				 {
					 // Add the new client to the clients list
					 clients.push_back(client);

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
//sf::Packet NetworkManager::createPacket();
//void NetworkManager::decryptPacket(sf::Packet);
//void NetworkManager::sendPacket(sf::Packet, sf::IpAddress);