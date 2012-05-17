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