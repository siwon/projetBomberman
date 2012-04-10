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

	retour.x = int((sPerso.GetPosition().x + LARGEUR) / (LARGEUR * 2)) * (LARGEUR * 2.f);
	retour.y = int((sPerso.GetPosition().y + HAUTEUR) / (HAUTEUR * 2)) * (HAUTEUR * 2.f);

	return retour;
}

void GererIntersection(touches keys, touches& retour, sf::Sprite& sPerso, float x, float y)
{
	if (keys.left || keys.right)
	{
		sf::Vector2f pos = sPerso.GetPosition();

		if (pos.y > y - HAUTEUR && pos.y <= y - MARGE)
			retour.down = true;
		else if (pos.y >= y + MARGE && pos.y < y + HAUTEUR)
			retour.up = true;
		else if (abs(pos.y - y) < MARGE)
		{
			sPerso.SetY(y);

			retour.left = keys.left;
			retour.right = keys.right;
		}					
	}

	if (keys.up || keys.down)
	{
		sf::Vector2f pos = sPerso.GetPosition();

		if (pos.x > x - LARGEUR && pos.x <= x - MARGE)
			retour.right = true;
		else if (pos.x >= x + MARGE && pos.x < x + LARGEUR)
			retour.left = true;
		else if (abs(pos.x - x) < MARGE)
		{
			sPerso.SetX(x);

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
	app->SetFramerateLimit(60);

    sf::Image iFond;
	iFond.LoadFromFile("fond.png");

	sf::Image iPerso;
	iPerso.LoadFromFile("perso.png");

	sf::Sprite sFond;
	sFond.SetImage(iFond);

	sf::Sprite sPerso;
	sPerso.SetImage(iPerso);

	sf::Sprite sCase;
	sCase.SetColor(sf::Color(0, 255, 0, 128));
	sCase.Resize(LARGEUR * 2.f, HAUTEUR * 2.f);

	sPerso.SetY(120.f);

	const sf::Input& input = app->GetInput();
	touches keys;

    while (app->IsOpened())
    {
		sf::Event event;

		while (app->GetEvent(event))
		{
			if (event.Type == sf::Event::Closed)
				app->Close();
		}

		keys.left = input.IsKeyDown(sf::Key::Left);
		keys.right = input.IsKeyDown(sf::Key::Right);
		keys.up = input.IsKeyDown(sf::Key::Up);
		keys.down = input.IsKeyDown(sf::Key::Down);

		touches retour = touches();

		GererIntersection(keys, retour, sPerso, 80, 120);
		GererIntersection(keys, retour, sPerso, 240, 120);
		
		sPerso.Move(speed * app->GetFrameTime() * (retour.right - retour.left),
					speed * app->GetFrameTime() * (retour.down  - retour.up));

		sCase.SetPosition(GetCase(sPerso));

		app->Clear();

		app->Draw(sFond);
		app->Draw(sCase);
		app->Draw(sPerso);
			
		app->Display();
	}

	delete app;

    return 0;
}
