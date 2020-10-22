#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HIGHT = 800.0f;
void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
		view.setSize(VIEW_HIGHT * aspectRatio, VIEW_HIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML turtorial", sf::Style::Close | sf::Style::Resize);
	
	//player
	sf::Texture playerTexture ;
	playerTexture.loadFromFile("C001.png");
	Player player(&playerTexture, sf::Vector2u(3, 2), 0.5f , 250.0f); 
	float detalTime = 0.0f;
	sf::Clock clock;
	sf::Texture Wall;
	//wall paper
	Wall.loadFromFile("wall007.jpg");
	sf::Sprite swall(Wall);
	swall.setScale(1, 1);
	//view  
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HIGHT, VIEW_HIGHT));
	//platform
	sf::Texture D;
	D.loadFromFile("PW.png");
	Platform platform1(&D, sf::Vector2f(172.5f, 250.0f), sf::Vector2f(1200.0f, 500.0f));
	sf::Texture B;
	B.loadFromFile("BP.png");
	Platform platform2(&B, sf::Vector2f(174.0f, 250.0f), sf::Vector2f(700.0f, 500.0f));
	//Platform platform2(nullptr, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(50.0f, 40.0f));


	swall.setPosition(0, 0);

	while (window.isOpen())
	{
		detalTime = clock.restart().asSeconds(); 
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
		player.Update(detalTime);
		Collider b = player.GetCollider();
	    platform1.GetCollinder().CheckCollision(b, 1.0f);
		platform2.GetCollinder().CheckCollision(b, 1.0f);
	   //platform2.GetCollinder().CheckCollision(b, 1.0f);
		view.setCenter(player.GetPosition());
		window.clear(sf::Color(500,500,500));
		window.draw(swall);
		window.setView(view);
		player.Draw(window);	
		platform1.Draw(window);
		platform2.Draw(window);
		//platform2.Draw(window);
	}
	return 0;

}