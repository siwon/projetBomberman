#include <SFML/Graphics.hpp>

const float MARGE = 2.f;
const float LARGEUR = 20.f;
const float HAUTEUR = 20.f;

struct touches
{
	bool left;
	bool right;
	bool up;
	bool down;

	touches() : left(false), right(false), up(false), down(false) {}
};

sf::Vector2f GetCase(sf::Sprite& sPerso)
{
	sf::Vector2f retour;

	retour.x = int((sPerso.getPosition().x + LARGEUR) / (LARGEUR * 2)) * (LARGEUR * 2.f);
	retour.y = int((sPerso.getPosition().y + HAUTEUR) / (HAUTEUR * 2)) * (HAUTEUR * 2.f);

	return retour;
}

void gererIntersection(touches keys, touches& retour, sf::Sprite& sPerso, float x, float y)
{
	if (keys.left || keys.right)
	{
		sf::Vector2f pos = sPerso.getPosition();

		if (pos.y > y - HAUTEUR && pos.y <= y - MARGE)
			retour.down = true;
		else if (pos.y >= y + MARGE && pos.y < y + HAUTEUR)
			retour.up = true;
		else if (abs(pos.y - y) < MARGE)
		{
			sPerso.setPosition(pos.x, y);

			retour.left = keys.left;
			retour.right = keys.right;
		}					
	}

	if (keys.up || keys.down)
	{
		sf::Vector2f pos = sPerso.getPosition();

		if (pos.x > x - LARGEUR && pos.x <= x - MARGE)
			retour.right = true;
		else if (pos.x >= x + MARGE && pos.x < x + LARGEUR)
			retour.left = true;
		else if (abs(pos.x - x) < MARGE)
		{
			sPerso.setPosition(x, pos.y);

			retour.up = keys.up;
			retour.down = keys.down;
		}
	}
}

sf::RenderWindow* app;
const float speed = 200.f;

int main()
{
    app = new sf::RenderWindow(sf::VideoMode(360, 200, 32), "Bomberman - Test deplacement");
	app->setFramerateLimit(60);

    sf::Texture tFond;
	tFond.loadFromFile("fond.png");

	sf::Texture tPerso;
	tPerso.loadFromFile("perso.png");

	sf::Sprite sFond;
	sFond.setTexture(tFond);

	sf::Sprite sPerso;
	sPerso.setTexture(tPerso);

	sf::Sprite sCase;
	sCase.setColor(sf::Color(0, 255, 0, 128));
	sCase.scale(LARGEUR * 2.f, HAUTEUR * 2.f);

	sPerso.setPosition(0.f, 120.f);

	touches keys;

	sf::Clock clock;

    while (app->isOpen())
    {
		sf::Time elapsed = clock.restart();

		sf::Event event;

		while (app->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app->close();
		}

		keys.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		keys.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		keys.up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		keys.down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

		touches retour = touches();

		gererIntersection(keys, retour, sPerso, 80, 120);
		gererIntersection(keys, retour, sPerso, 240, 120);
		
		sPerso.move(speed * elapsed.asSeconds() * (retour.right - retour.left),
					speed * elapsed.asSeconds() * (retour.down  - retour.up));

		sCase.setPosition(GetCase(sPerso));

		app->clear();

		app->draw(sFond);
		app->draw(sCase);
		app->draw(sPerso);
			
		app->display();
	}

	delete app;

    return 0;
}
