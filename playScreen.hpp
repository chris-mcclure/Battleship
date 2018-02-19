#pragma once
#include <SFML/Graphics.hpp>
#include "cScreen.hpp"

class playScreen : public cScreen
{
public:
	playScreen();

	virtual int Run(sf::RenderWindow &App);
};

playScreen::playScreen()
{
}


int playScreen::Run(sf::RenderWindow &App)
{
	sf::Event event;
	
	sf::CircleShape circle(300);
	circle.setFillColor(sf::Color::Red);
	

	while (App.isOpen())
	{

		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				return(0);
			}
		}
		App.clear();
		App.draw(circle);
		App.display();

	}
}


