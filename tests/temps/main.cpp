#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

using namespace std;

int main()
{
	sf::Clock horloge = sf::Clock();
	//sf::Time tps = horloge.getElapsedTime();
	int temps = horloge.getElapsedTime().asSeconds()+3;
	
	while (horloge.getElapsedTime().asSeconds()<temps) {
		cout << "Waiting ..." << horloge.getElapsedTime().asSeconds() << endl;
	}
	cout << "Boom" << endl;
	
    return 0;
}
