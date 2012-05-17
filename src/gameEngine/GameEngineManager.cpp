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
  
}

SBoard GameEngineManager::getBoard() {
	SBoard toReturn;
	
	toReturn->boxes=board.getBox();
	toReturn->bonus=board.getBonus();
	toReturn->explosives=board.getExplosive();
	toReturn->players=board.getPlayer();
	toReturn->flames=board.getFlame();
	
	return toReturn;
}