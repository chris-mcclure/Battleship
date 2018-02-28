#pragma once
#include <SFML/Graphics.hpp>
#include "cScreen.hpp"
#include <iostream>

#define NUM_OF_SELECTIONS 3

class mainMenu : public cScreen
{
public:
	mainMenu() {};

	virtual int Run(sf::RenderWindow &App);
};

int mainMenu::Run(sf::RenderWindow &App)
{
	sf::Event event;
	sf::Texture menuBackground;
	int selectedItemIndex = 0;
	sf::Font font;
	sf::Text menu[NUM_OF_SELECTIONS];


	font.loadFromFile("Amatic-Bold.ttf");

	menuBackground.setSmooth(true);
	sf::Sprite board(menuBackground);
	board.setScale(1.425f, 1.425f);


	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play Game!");
	menu[0].setCharacterSize(100);
	menu[0].setPosition(sf::Vector2f(App.getSize().x / 2 , App.getSize().y / (NUM_OF_SELECTIONS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setCharacterSize(100);
	menu[1].setPosition(sf::Vector2f(App.getSize().x / 2, App.getSize().y / (NUM_OF_SELECTIONS + 1) * 2));



	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Close");
	menu[2].setCharacterSize(100);
	menu[2].setPosition(sf::Vector2f(App.getSize().x / 2, App.getSize().y / (NUM_OF_SELECTIONS + 1) * 3));


	while (App.isOpen())
	{
		

		while (App.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Up:
					if (selectedItemIndex - 1 >= 0) {
						menu[selectedItemIndex].setFillColor(sf::Color::White);
						selectedItemIndex--;
						menu[selectedItemIndex].setFillColor(sf::Color::Red);
					}
					break;
				case sf::Keyboard::Key::Down:
					if (selectedItemIndex + 1 < NUM_OF_SELECTIONS) {
						menu[selectedItemIndex].setFillColor(sf::Color::White);
						selectedItemIndex++;
						menu[selectedItemIndex].setFillColor(sf::Color::Red);
					}
					break;
				case sf::Keyboard::Return:

					switch (selectedItemIndex)
					{
					case 0:
						return(1);
					case 1:
						return(0);
					case 2:
						return(-1); //closes game
					}
				}
			}
		}
		App.clear();
		App.draw(board);
		App.draw(menu[0]);
		App.draw(menu[1]);
		App.draw(menu[2]);
		App.display();
	}
}
