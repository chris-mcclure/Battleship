#pragma once
#include "Player.h"

Player::Player()
{
	
}

Player::Player(int shipCount) : shipCount(shipCount), shipSelected(false), shipsPlacedCount(0), allShipsPlaced(false)
{}

bool Player::shipHit(std::pair<int, int> pos)
{
	for (auto & i : ships)
	{
		int boxIndex = 0; //tells the ship which one of its rectangles got hit
		for (auto & k : i.position)
		{
			if (k == pos)
			{
				i.takeDamage(boxIndex);
				return true;
			}
			boxIndex++;
		}

	}
	return false; //attack missed
}
void Player::moveShip(std::pair<int, int> pos)
{
	//look at all ships to see if the chosen position intersects with them
	bool intersectionFound = false;



	for (auto & i : ships)
	{
		for (auto & k : i.position)
		{
			if (k == pos)
			{
				intersectionFound = true;
				i.changeColor(sf::Color::Blue);
				i._isSelected = false;
			} 
		}
	}

	if (!intersectionFound)
	{
		for (auto & i : ships)
		{
			if (i._isSelected && !i._isPlaced)
			{
				i._initialPlacement = false; //has to be here so you can still rotate before placement
				if (i.move(pos))
				{
					shipsPlacedCount++;
					i._isPlaced = true;
				}
				i.changeColor(sf::Color::Blue);
				i._isSelected = false;

				if (shipsPlacedCount == shipCount)
					allShipsPlaced = true;
			}
		}
	}
	shipSelected = false; //put outside loop just incase if statement wasn't met
}

void Player::selectShip(std::pair<int, int> pos)
{
	for (auto & i : ships)
	{
		for (auto & k : i.position)
		{
			if (k == pos && !i._isPlaced)
			{
				i._isSelected = true;
				shipSelected = true;
				i.changeColor(sf::Color::Green);
			}
		}
	}
}

void Player::makeShips(std::pair<int,int> squareSize)
{
	int xPos = 13;
	int yPos = 3;

	for (int i = 0; i < shipCount; i++)
	{
		//make ship objects
		ships.push_back(Ship(i + 1, squareSize));

		//set ship object to right side of board for player to choose where to place
		ships[i].move(std::make_pair(xPos,yPos));

		yPos += 4; 
		if (i == 1) //start new column 
		{
			xPos += 2;
			yPos = 3;
		}
	}
}

void Player::drawShips(sf::RenderWindow &App)
{
	for (auto & i : ships)
	{
		for (auto & k : i.shipBox)
		{
			App.draw(k);
		}
	}
}

void Player::rotateShip()
{
	for (auto & i : ships)
	{
		if (i._isSelected && !i._isPlaced)
		{
			i._isVertical = !i._isVertical; //flip boolean to opposite value
			i.move(i.position[0]); //pass it's own position so it rotates in place
		}
	}
}