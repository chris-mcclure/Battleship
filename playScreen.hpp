#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "cScreen.hpp"
#include <vector>

class playScreen : public cScreen
{
private:
	sf::Rect<int> gridSquares[12][12];
	std::vector<Player> playerVec;
	sf::Sprite playerBoats[2][2];
	sf::Text text[2];
	const int BOAT_COUNT = 2; //number of boats that each player has, used for boat related loops
	int currentPlayer = 0;

public:
	playScreen() {};

	void makeBoats(sf::Texture &boat);
	void makeTexts(sf::Font &font);
	void makeGrid(float boardHeight, float boardWidth);
	std::pair<int,int> findCoords(sf::Vector2i pos);

	virtual int Run(sf::RenderWindow &App);
};

int playScreen::Run(sf::RenderWindow &App)
{
	sf::Event event;

	//make background
	sf::Texture grid;
	grid.loadFromFile("grid.jpg");
	sf::Sprite background(grid);

	//make grid objects
	int boardHeight = background.getGlobalBounds().width / 11;
	int boardWidth = background.getGlobalBounds().height / 12;

	makeGrid(boardHeight, boardHeight);

	//make player objects
	Player p1;
	Player p2;
	playerVec.push_back(p1);
	playerVec.push_back(p2);


	//make the boats
	sf::Texture boat;
	boat.loadFromFile("otherboat.png");
	makeBoats(boat);

	//make texts
	sf::Font font;
	font.loadFromFile("Amatic-Bold.ttf");
	makeTexts(font);

	//make plane
	sf::Texture planeImage;
	planeImage.setSmooth(true);
	planeImage.loadFromFile("paper-plane2.png");

	sf::Vector2u plane_size = planeImage.getSize();
	sf::Sprite plane(planeImage);
	plane.setOrigin(0, plane.getTexture()->getSize().y);
	plane.rotate(132.5f);
	plane.scale(0.65f, 0.65f);
	plane.setPosition(sf::Vector2f(-100, 100));

	while (App.isOpen())
	{

		while (App.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed)
			{
				currentPlayer = 1 - currentPlayer; //switch player turns

				if (event.key.code == sf::Keyboard::Key::Escape)
					return(0);//need to fix. this screen object needs to be remake before new game started to avoid bugs
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { //think we need to make this event
			plane.setPosition(sf::Vector2f(sf::Mouse::getPosition(App).x, App.getSize().y + 10));
			//std::pair<float, float> attackLocation = std::make_pair(sf::Mouse::getPosition(App).x, App.getSize().y);
			//playerVec[1 - currentPlayer].targetHit(attackLocation);

			sf::Vector2i attackPos = sf::Mouse::getPosition(App);

			playerVec[1 - currentPlayer].checkShips(attackPos);



			/*
			if (gridSquares[0][1].contains(sf::Vector2i(sf::Mouse::getPosition(App))))
			{
				std::cout <<" hit found\n";
			} */
		}
		plane.move(0,-1);

		App.clear();
		App.draw(background);

		//draw boats
		for (int i = 0; i < BOAT_COUNT; i ++)
		{
			App.draw(playerBoats[currentPlayer][i]);
		}
		App.draw(plane);
		App.draw(text[currentPlayer]);
		App.display();
	}

	return(0);
}


void playScreen::makeBoats(sf::Texture &boat) //make this construct the boats in a loop when i figure out how to set position systematically
{
	playerBoats[0][0].setTexture(boat);
	playerBoats[0][0].setScale(.2f, .2f);

	playerBoats[0][1].setTexture(boat);
	playerBoats[0][1].setScale(.2f, .2f);
	playerBoats[0][1].move(200, 0);

	playerBoats[1][0].setTexture(boat);
	playerBoats[1][0].setScale(.2f, .2f);
	playerBoats[1][0].move(sf::Vector2f(300, 200));

	playerBoats[1][1].setTexture(boat);
	playerBoats[1][1].setScale(.2f, .2f);
	playerBoats[1][1].move(100, 400);
}

void playScreen::makeTexts(sf::Font &font)
{
	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Cyan);
	text[0].setString("Player Ones's turn");
	text[0].setCharacterSize(30);
	text[0].setPosition(sf::Vector2f(800, 50));

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::Green);
	text[1].setString("Player Two's turn");
	text[1].setCharacterSize(30);
	text[1].setPosition(sf::Vector2f(800, 50));
}

void playScreen::makeGrid(float boardHeight, float boardWidth)
{
	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			gridSquares[x][y].height = boardHeight;
			gridSquares[x][y].width = boardWidth;
			gridSquares[x][y].left = x * (boardWidth);
			gridSquares[x][y].top = y * (boardHeight);
		}
	}
}

std::pair<int,int> playScreen::findCoords(sf::Vector2i loc)
{
	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			if (gridSquares[x][y].contains(loc))
			{
				return std::make_pair(x, y);
			}
		}
	}
	//else return something harmless
}
