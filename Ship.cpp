#include "Ship.h"

Ship::Ship(int boatSize, std::pair<int, int> squareSize) :
	_size(boatSize), _health(boatSize), _squareSize(squareSize)
{	
	position.reserve(_size);
	shipBox.reserve(_size); 

	
	
	for (int i = 0; i < _size; i++)
	{
		position.push_back(std::make_pair(0, 0));
		shipBox.push_back(sf::RectangleShape((sf::Vector2f(squareSize.first, squareSize.second))));
		shipBox[i].setFillColor(sf::Color::Blue);
		shipBox[i].setOutlineColor(sf::Color::Black);
		shipBox[i].setOutlineThickness(2);

	}

	_isAlive = true;
	_isPlaced = false;
	_isSelected = false;
	_isVertical = true;
	_initialPlacement = true;

}

//doot
bool Ship::move(std::pair<int, int> pos)
{
	bool result = true;
	bool legalMove;

	if (_isVertical)
	{
		legalMove = ((pos.first >= 0 && pos.first < 12 &&
			pos.second >= 0 && pos.second + _size-1 < 12)
			|| _initialPlacement);
	}
	else
	{
		legalMove = ((pos.first >= 0 && pos.first + _size-1 < 12 &&
			pos.second >= 0 && pos.second < 12)
			|| _initialPlacement);
	}


	for (int i = 0; i < _size; i++)
	{
		if (_isVertical)
		{
			if (legalMove) //skips out of bounds check if it hasnt been set to the side of the board yet
			{
				position[i].first = pos.first;
				position[i].second = pos.second + i;

				shipBox[i].setPosition(sf::Vector2f(pos.first * _squareSize.first, (pos.second + i) * _squareSize.second));

			}
			else result = false;
		}
		else //its horizontal
		{
			if (legalMove)
			{
				position[i].first = pos.first + i;
				position[i].second = pos.second;

				shipBox[i].setPosition(sf::Vector2f((pos.first + i) * _squareSize.first, pos.second * _squareSize.second));

			}
			else result = false;
		}
	}
	return result;
}

void Ship::takeDamage(int boxHit)
{
	_health--;
	shipBox[boxHit].setFillColor(sf::Color::Red);
	position[boxHit] = std::make_pair(-100, -100); //sets the boxes model off the screen so it cant be hit again
													//note: does not move the Box that is drawn to screen
	
	if (_health == 0)
	{
		_isAlive = false;
		std::cout << "ship exploded! " << std::endl;

	}
}

void Ship::changeColor(sf::Color newColor)
{
	for (auto &i : shipBox)
	{
		i.setFillColor(newColor);
	}
}