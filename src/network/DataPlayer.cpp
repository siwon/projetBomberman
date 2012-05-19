/*!
 * \file DataPlayer.cpp
 * \brief Impl�mentation de classe DataPlayer
 * \author Brice GUILLERMIC
 */

// Biblioth�ques SFML
#include <SFML/Network.hpp>

//Headers
#include "../../include/DataPlayer.hpp"

using namespace PolyBomber;

DataPlayer::DataPlayer(int pId, sf::IpAddress pIp, std::string pName) : id(pId), ip(pId), name(pName){

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