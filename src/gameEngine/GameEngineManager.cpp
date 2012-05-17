/*!
 * \file GameEngineManager.cpp
 * \brief Implémentation de la classe GameEngineManager
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliothèques standards
#include <Vector>

// Bibliothèques SFML


// Bibliothèques externes


// Headers
#include "../../include/gameEngine/GameEngineManager.hpp"

using namespace PolyBomber;

void GameEngineManager::applyBonus(Bonus bonus, Player player) {
	player.applyBonus(bonus);
}

void GameEngineManager::movePlayer(Player player, EOrientation orientation) {
	player.move(orientation);
}

void GameEngineManager::explode(Explosive explosive) {
	explosive.explode();
}

void GameEngineManager::activateDetonator(Player player) { //a terminer
	for (vector<Explosive>::iterator i = vect.begin() ; i != vect.end() ; i++) {
		if (i.player == player) {
			i.explode();
		}
	}
}

void GameEngineManager::putMine(Player player) {
	if (player.getCapacity()) {
		player.decreaseCapacity();
		//this.board.add(new );
		// TODO : à terminer
	}
}

void GameEngineManager::breakBox(Box box) {
	box.broke();
}

SBoard GameEngineManager::getBoard() {
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
	int nbPlayers = gameConfig->nbPlayers;
	int nbBonus = gameConfig->nbBonus;
	
	this->gameConfigIsSet=true;
}

SBoard GameEngineManager::getBoard() {
	SBoard toReturn;
	
	vector<Player> joueur=board.getPlayer(); /** Liste des joueurs */
	vector<Explosive> bombe=board.getExplosive(); /** Liste des bombes */
	vector<Flame> deflagration=board.getFlame(); /** Liste des déflagrations */
	vector<Bonus> bonus=board.getBonus(); /** Liste des bonus */
	vector<Box> boite=board.getBox(); /** Liste des boites */
	
	for (int i=0; i<boite.size(); i++) { //ajout de toutes les caisses
		int x=boite[i].getLocationX();
		int y=boite[i].getLocationY();
		toReturn->boxes.push_back(new sf:Vector2<int>(x,y));
	}
	
	
	//bonus
	//explosives
	//players
	//flames
	
	return toReturn;
}

void GameEngineManager::run() {
	if (this->gameConfigIsSet) {
		<#statements-if-true#>
	} else {
		//erreur : la partie n'a pas étée paramétrée
	}
}