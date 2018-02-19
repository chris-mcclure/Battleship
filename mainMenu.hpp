#pragma once
#include <SFML/Graphics.hpp>
#include "cScreen.hpp"

class mainMenu : public cScreen
{
public:
	mainMenu();

	virtual int Run(sf::RenderWindow &App);
};

mainMenu::mainMenu()
{

}


int mainMenu::Run(sf::RenderWindow &App)
{
	sf::Event event;

	sf::CircleShape circle(200);
	circle.setFillColor(sf::Color::Blue);

	while (App.isOpen())
	{

		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				return(1);
			}
		}
		App.clear();
		App.draw(circle);
		App.display();

	}
}


