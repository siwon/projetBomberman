/*!
 * \file NetworkManager.cpp
 * \brief Impl�mentation de classe NetworkManager
 * \author Brice GUILLERMIC
 */

// Biblioth�ques SFML
#include <SFML/Network.hpp>

//Headers
#include "../../include/network/NetworkManager.hpp"
#include "../../include/controller/ControllerManager.hpp"
#include "../../include/SKeyPressed.hpp"

using namespace PolyBomber;

SKeyPressed NetworkManager::getKeysPressed(){
	return this->controller->getKeysPressed();
}