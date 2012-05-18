/*!
 * \file GameEngineManager.cpp
 * \brief Implémentation de la classe GameEngineManager
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards
#include <vector>

// Bibliothèques SFML
#include <SFML/System/Vector2.hpp>

// Bibliothèques externes


// Headers
#include "../../include/gameEngine/DefineAndFunction.hpp"
#include "../../include/gameEngine/Board.hpp"
#include "../../include/gameEngine/Bonus.hpp"
#include "../../include/gameEngine/Player.hpp"
#include "../../include/gameEngine/GameEngineManager.hpp"
#include "../../include/IGameEngineToNetwork.hpp"
#include "../../include/IGameEngineToGameInterface.hpp"
#include "../../include/INetworkToGameEngine.hpp"

using namespace PolyBomber;

void GameEngineManager::applyBonus(Bonus bonus, Player player) {
	//TODO : à faire
}

void GameEngineManager::movePlayer(Player player, EOrientation orientation) {
	//TODO : à faire
}

void GameEngineManager::activateDetonator(Player player) {
	//TODO : à faire
}

void GameEngineManager::putMine(Player player) {
	if (player.getCapacity()) {
		player.decreaseCapacity();
		//this.board.add(new );
		// TODO : à terminer
	}
}

SBoard IGameEngineToGameInterface::getBoard() {
	SBoard toReturn;
	
	// TODO : à terminer
	
	return toReturn;
}

bool GameEngineManager::isFinished() {
	int nbSurvivant;
	bool toReturn;
	
	// TODO : à terminer
	
	return toReturn;
}

void GameEngineManager::setGameConfig(SGameConfig gameConfig) {
	unsigned int nbPlayers = gameConfig.nbPlayers;
	unsigned int nbBonus[17];
	
	for (int i=0; i<17; i++) {
		nbBonus[i]=gameConfig.nbBonus[i];
	}
	
	this->setGameConfigIsSet(true);
}

SBoard GameEngineManager::getBoard() {
	SBoard toReturn;
	
	std::vector<Player> joueur=board.getPlayer(); /** Liste des joueurs */
	std::vector<Explosive> bombe=board.getExplosive(); /** Liste des bombes */
	std::vector<Flame> deflagration=board.getFlame(); /** Liste des déflagrations */
	std::vector<Bonus> bonus=board.getBonus(); /** Liste des bonus */
	std::vector<Box> boite=board.getBox(); /** Liste des boites */
	
	for (unsigned int i=0; i<boite.size(); i++) { //ajout de toutes les caisses
		sf::Vector2<int> loc=boite[i].getLocation();
		
		toReturn.boxes.push_back(loc);
	}
	
	
	//bonus
	//explosives
	//players
	//flames
	
	return toReturn;
}

void GameEngineManager::run() {
	if (this->gameConfigIsSet) {
		//fonctionnement normal
	} else {
		//erreur : la partie n'a pas étée paramétrée
	}
}