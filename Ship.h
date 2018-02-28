#pragma once
#include <vector>
#include <utility>
#include "SFML\Graphics.hpp"
#include <iostream>

class Ship
{
public:
	//ship member objects
	int _size;
	int _health;
	bool _isAlive;
	bool _isPlaced;
	bool _isSelected;
	bool _isVertical;
	bool _initialPlacement;

	std::pair<int, int> _squareSize; //(x,y) 

	std::vector<std::pair<int, int>> position;
	std::vector<sf::RectangleShape> shipBox;
	
	//ship ctors/dtors
	Ship() {};
	Ship(int boatSize, std::pair<int,int> squareSize);

	//ship functions
	bool move(std::pair<int, int> pos);
	void takeDamage(int boxHit);
	void changeColor(sf::Color newColor);

};
