#pragma once
#include <vector>
#include <utility>

class Ship
{
public:
	const std::pair<int, int> DEFAULT_POS = std::make_pair(0, 0);
	//ship member objects
	int _size;
	bool _isAlive;
	std::vector<std::pair<int, int>> _position;
	//std::pair<int, int> _position;
	
public:
	//ship ctors/dtors
	Ship();
	Ship(int size);
	~Ship();

	//ship member functions
	void placeShip(std::pair<int,int> setPos);
};

