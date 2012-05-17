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

void GererIntersection(touches keys, touches& retour, sf::Sprite& sPerso, float x, float y)
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
			sPerso.setY(y);

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
			sPerso.setX(x);

			retour.up = keys.up;
			retour.down = keys.down;
		}
	}
}

sf::RenderWindow* app;
const float speed = 200.f;

int main()
{
    app = new sf::RenderWindow(sf::videoMode(360, 200, 32), "Bomberman - Test deplacement");
	app->setFramerateLimit(60);

    sf::Image iFond;
	iFond.loadFromFile("fond.png");

	sf::Image iPerso;
	iPerso.loadFromFile("perso.png");

	sf::Sprite sFond;
	sFond.setImage(iFond);

	sf::Sprite sPerso;
	sPerso.setImage(iPerso);

	sf::Sprite sCase;
	sCase.setColor(sf::Color(0, 255, 0, 128));
	sCase.resize(LARGEUR * 2.f, HAUTEUR * 2.f);

	sPerso.setY(120.f);

	const sf::Input& input = app->getInput();
	touches keys;

    while (app->isOpened())
    {
		sf::Event event;

		while (app->getEvent(event))
		{
			if (event.Type == sf::Event::Closed)
				app->close();
		}

		keys.left = input.isKeyDown(sf::Key::Left);
		keys.right = input.isKeyDown(sf::Key::Right);
		keys.up = input.isKeyDown(sf::Key::Up);
		keys.down = input.isKeyDown(sf::Key::Down);

		touches retour = touches();

		gererIntersection(keys, retour, sPerso, 80, 120);
		gererIntersection(keys, retour, sPerso, 240, 120);
		
		sPerso.move(speed * app->GetFrameTime() * (retour.right - retour.left),
					speed * app->GetFrameTime() * (retour.down  - retour.up));

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
