#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

//#include <iostream>
#include <vector>


/*#include "gameEngine/Board.hpp"
#include "gameEngine/Bonus.hpp"
#include "gameEngine/Player.hpp"
#include "gameEngine/Location.hpp"
#include "gameEngine/Box.hpp"
#include "gameEngine/Explosive.hpp"
#include "gameEngine/RemoteBomb.hpp"
#include "gameEngine/Bomb.hpp"
#include "gameEngine/Mine.hpp"/**/
#include "gameEngine/GameEngineManager.hpp"
//#include "gameEngine/DefineAndFunction.hpp"

#include "EOrientation.hpp"
#include "IGameEngineToNetwork.hpp"
#include "IGameEngineToGameInterface.hpp"
#include "INetworkToGameEngine.hpp"
#include "SBoard.hpp"
#include "SGameConfig.hpp"

using namespace PolyBomber;

int main()
{
	/*sf::Clock horloge = sf::Clock();
	sf::Time tps = horloge.getElapsedTime();
	int temps = horloge.getElapsedTime().asSeconds()+3;
	
	while (horloge.getElapsedTime().asSeconds()<temps) {
		cout << "Waiting ..." << endl;
	}
	cout << "Boom" << endl;/**/
	
	//Board b = new Board();
	/*int nbPlayer = 2;
	int nbBonus = 12;
	int nbBox = 10;
	
	/*Board *board = new Board;
	std::vector<Board> vect = new std::vector<Board>;
	vect->push_back(*board);/**/
	
	/*Board::Board *board = new Board;
	std::vector<Board> vect;
	vect.push_back(*board);
	
	/*for (unsigned int i = 0 ; i < vect.size() ; i++) {
		cout << vect[i] << endl;
	}*/
	//b.generateBoard(nbPlayer,nbBonus,nbBox);
	//b.toString();
	
	GameEngineManager g = GameEngineManager();
	
    return 0;
}
