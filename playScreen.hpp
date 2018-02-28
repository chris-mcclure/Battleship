#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Player.h"
#include "cScreen.hpp"
#include "TextureManager.hpp"
#include <vector>

class playScreen : public cScreen
{
private:
	sf::Rect<int> gridSquares[16][12];
	
	std::vector<Player> players;
	TextureManager textures;
	sf::Sprite background;
	sf::Font font;
	sf::Text text[2]; //for displaying current turn
	sf::Text result[2]; //displays message when the game is over
	sf::Sprite plane;
	sf::Event event;
	sf::Sprite endTurn;
	sf::Sprite bomb;
	sf::Sprite tempBomb;
	sf::Sprite explosion;

	std::pair<int, int> squareSize;
	
	int currentPlayer;
	bool attackPhase;
	bool placingPhase;
	

public:
	playScreen();

	void makeTexts();
	void makeGrid();
	void makePlane();
	void makeTextures();
	void makeButtons();
	void makeBomb();
	sf::Vector2i gridCoords(sf::Vector2i pos);
	std::pair<int, int> getIntCoords(sf::Vector2i pos);
	bool isPlayerDead(int otherPlayer);

	virtual int Run(sf::RenderWindow &App)
	{

		bool startBomb = false;
		bool drawExplosion = false;
		int count = 0;

		sf::Vector2i mousePos;

		while (App.isOpen())
		{

			while (App.pollEvent(event))
			{
				//////////////////////////////////
				//Event: Keyboard button pressed
				//////////////////////////////////
				if (event.type == sf::Event::KeyPressed)
				{
													   //event: press escape to exit game
					if (event.key.code == sf::Keyboard::Key::Escape)
						return(0);

					if (event.key.code == sf::Keyboard::Key::Num7) //suicide button for demonstrating game end
					{
						for (auto & i : players[currentPlayer].ships)
						{
							for (auto k = 0; k < i.position.size(); k++)
								i.takeDamage(k);
						}
					}


				}//----------End of Event: Keyboard button----------


				//////////////////////////////
				//Event: Mouse button pressed
				//////////////////////////////
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					//assign mouseCoords to a Vector2i. 
					mousePos = sf::Mouse::getPosition(App);
					auto intCoords = getIntCoords(mousePos);

					//Was end turn button clicked?
					sf::FloatRect buttonPos = endTurn.getGlobalBounds();

					if (buttonPos.contains(sf::Vector2f(mousePos))) 
					{
						//new turn. reset turn based variables
						currentPlayer = 1 - currentPlayer;
						players[currentPlayer].usedAttack = false;
						endTurn.setTexture(textures.getRef("endturn"));
						return(2);

					}

					//PLACING PHASE//////////////////////////////////////////////////
					if (!players[currentPlayer].allShipsPlaced)
					{
						if (players[currentPlayer].shipSelected) //player has already selected a ship, move it to mousePos
						{
							if (event.key.code == sf::Mouse::Button::Left)
							{
								players[currentPlayer].moveShip(intCoords);
							}
							else if (event.key.code == sf::Mouse::Button::Right)
							{
								players[currentPlayer].rotateShip();
								players[currentPlayer].shipSelected = true;
							}
						}
						else players[currentPlayer].selectShip(intCoords); //ship hasn't been selected, try to select one
						if (players[currentPlayer].allShipsPlaced)
						{
							//Light up end turn button
							endTurn.setTexture(textures.getRef("endturnlit"));
							players[currentPlayer].usedAttack = true; //so it doesnt immediately use an attack
							
						}
					}//END PLACING PHASE//////////////////////////////////////////////


					//ATTACK PHASE////////////////////////////////////////////////////
					if (players[currentPlayer].allShipsPlaced && 
						players[1 - currentPlayer].allShipsPlaced &&
						!players[currentPlayer].usedAttack)
					{
						plane.setPosition(sf::Vector2f(sf::Mouse::getPosition(App).x, App.getSize().y + 10));
						explosion.setPosition(intCoords.first * squareSize.first, intCoords.second * squareSize.second);
						//check other players ships
						if (players[1 - currentPlayer].shipHit(intCoords))
						{
							//if true, calls the ships takeDamage function
							std::cout << "Ship hit \n";
						}else std::cout << "Missed \n";
						players[currentPlayer].usedAttack = true;
						endTurn.setTexture(textures.getRef("endturnlit"));
					}//END of ATTACK PHASE////////////////////////////////////////////

				}//----------End of Event: Mouse pressed----------
			}


			//animations
			
			plane.move(0,-15);
			if (((plane.getPosition().y - mousePos.y) <= 15)
				&& (plane.getPosition().y - mousePos.y) >= 0
				&& (plane.getPosition().y != 10)) {
				bomb.setPosition(mousePos.x, mousePos.y);
				startBomb = true;
			}

			//if enemy player has no more ship, game is over and current player wins
			if (isPlayerDead(1 - currentPlayer))
			{
				auto player = std::to_string(currentPlayer + 1);
				result[0].setString("Player " + player + " wins!");
				result[0].setPosition(300, 220);
				result[1].setString("Press escape to return to main menu");
				result[1].setPosition(300, 320);

			}
			//also checking if currentPlayer is dead because i added a suicide button
			else if (isPlayerDead(currentPlayer)) 
			{
				auto player = std::to_string(1- currentPlayer + 1);
				result[0].setString("Player " + player + " wins!");
				result[0].setPosition(300, 220);
				result[1].setString("Press escape to return to main menu");
				result[1].setPosition(300, 320);
			}

			//draw objects to screen
			App.clear();
			App.draw(background);
			players[currentPlayer].drawShips(App);

			
			if (startBomb) 
			{
				App.draw(bomb);

					bomb.scale(0.98, 0.98);
				if (bomb.getScale().x < .005)
				{
					bomb = tempBomb;
					startBomb = false;
					drawExplosion = true;
					
				}
			}
			if (drawExplosion && count < 500)
			{
				App.draw(explosion);
				count++;
			}

			App.draw(plane);
			App.draw(text[currentPlayer]);
			App.draw(result[0]);
			App.draw(result[1]);
			App.draw(endTurn);

			App.display();
		}
		return(0);
	}
};

//playScreen constructor. All changes made here persist through changing to another screen
playScreen::playScreen() 
{
	//load all textures that will be used for this screen
	makeTextures();

	//make buttons 
	makeButtons();
	makeBomb();
	//make game board and find the size of one square
	background.setTexture(textures.getRef("grid"));
	squareSize.first = background.getGlobalBounds().width / 12;
	squareSize.second = background.getGlobalBounds().height / 12;

	//make grid objects
	makeGrid();

	//make player vector
	players.push_back(Player(4));
	players.push_back(Player(4));
	currentPlayer = 0;
	//make ships using Player method
	players[0].makeShips(squareSize);
	players[1].makeShips(squareSize);

	//make texts
	makeTexts();

	//make plane
	makePlane();

	placingPhase = true;
	attackPhase = false;

}

void playScreen::makeTexts()
{
	font.loadFromFile("Amatic-Bold.ttf");

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

	for (auto & i : result)
	{
		i.setFont(font);
		i.setFillColor(sf::Color::White);
		i.setOutlineColor(sf::Color::Black);
		i.setOutlineThickness(4);
		i.setCharacterSize(60);
		i.setPosition(-10, -10); //off screen until game over
		//string gets set when winner is determined
	}



}

void playScreen::makeGrid()
{
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			gridSquares[x][y].height = squareSize.second;
			gridSquares[x][y].width = squareSize.first;
			gridSquares[x][y].left = x * (squareSize.first);
			gridSquares[x][y].top = y * (squareSize.second);
		}
	}
}

std::pair<int, int> playScreen::getIntCoords(sf::Vector2i pos)
{
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			if (gridSquares[x][y].contains(pos))
			{
				return std::make_pair(x,y);
				
			}
		}
	}
}

sf::Vector2i playScreen::gridCoords(sf::Vector2i loc)
{
	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			if (gridSquares[x][y].contains(loc))
			{
				return sf::Vector2i(gridSquares[x][y].left, gridSquares[x][y].top);
				
			}
		}
	}
	//else return something harmless
}


void playScreen::makePlane()
{
	textures.getRef("plane").setSmooth(true);
	plane.setTexture(textures.getRef("plane"));
	plane.setOrigin(0, plane.getTexture()->getSize().y);
	plane.rotate(132.5f);
	plane.scale(0.65f, 0.65f);
	plane.setPosition(sf::Vector2f(-100, 100));
}

void playScreen::makeTextures()
{
	textures.loadTexture("grid", "grid.jpg");
	textures.loadTexture("plane", "paper-plane2.png");
	textures.loadTexture("endturn", "endturn.png");
	textures.loadTexture("endturnlit", "endturnlit.png");
	textures.loadTexture("bomb", "bomb.png");
	textures.loadTexture("explode", "explode.png");
	//textures.loadTexture("shipFront", "shipFront.png");
	//textures.loadTexture("shipMid", "shipMid.png");
	//textures.loadTexture("shipBack", "shipBack.png");

}

bool playScreen::isPlayerDead(int otherPlayer)
{
	for (auto & i : players[otherPlayer].ships)
	{
		if (i._isAlive)
			return false;
	}
	return true; //if none of the ships are alive
}

void playScreen::makeButtons()
{
	endTurn.setTexture(textures.getRef("endturn"));
	endTurn.setPosition(sf::Vector2f(29,720));
}

void playScreen::makeBomb()
{
	textures.getRef("bomb").setSmooth(true);
	bomb.setTexture(textures.getRef("bomb"));
	bomb.setOrigin(bomb.getTexture()->getSize().x / 3, bomb.getTexture()->getSize().y / 1.5);
	bomb.scale(0.1, 0.1);
	tempBomb = bomb;

	explosion.setTexture(textures.getRef("explode"));
	
}