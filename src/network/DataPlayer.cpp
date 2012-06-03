/*!
 * \file DataPlayer.cpp
 * \brief Implémentation de classe DataPlayer
 * \author Brice GUILLERMIC
 */

// Bibliothèques SFML
#include <SFML/Network.hpp>

//Headers
#include "network/DataPlayer.hpp"

using namespace PolyBomber;

DataPlayer::DataPlayer(int pId, sf::IpAddress pIp, std::string pName) : id(pId), ip(pIp), name(pName){

}

DataPlayer::~DataPlayer(){

}
DataPlayer::DataPlayer(const DataPlayer &obj){
	this->id=obj.id;
	this->ip=obj.ip;
	this->name=obj.name;
}
DataPlayer& DataPlayer::operator=(const DataPlayer &obj){
	this->id=obj.id;
	this->ip=obj.ip;
	this->name=obj.name;
	return *this;
}
