#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

using namespace std;

#include <vector>

//#include "Board.hpp"
#include "Board.cpp"

int main()
{
	/*sf::Clock horloge = sf::Clock();
	//sf::Time tps = horloge.getElapsedTime();
	int temps = horloge.getElapsedTime().asSeconds()+3;
	
	while (horloge.getElapsedTime().asSeconds()<temps) {
		cout << "Waiting ..." << endl;
	}
	cout << "Boom" << endl;*/
	
	//Board b = new Board();
	int nbPlayer = 2;
	int nbBonus = 12;
	int nbBox = 10;
	std::vector<Board> vect = std::vector<Board>::vector();
	vect.push_back(Board());
	/*for (unsigned int i = 0 ; i < vect.size() ; i++) {
		cout << vect[i] << endl;
	}*/
	//b.generateBoard(nbPlayer,nbBonus,nbBox);
	//b.toString();
	
    return 0;
}
