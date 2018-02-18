#include "Ship.h"


Ship::Ship()
{
}

Ship::Ship(int size) : _size(size)
{
	_position.reserve(size);
	for (auto i : _position)
	{
		_position.push_back(DEFAULT_POS);
	}

}


Ship::~Ship()
{
}


void Ship::placeShip(std::pair<int,int> setPos)
{
	for (int i = 0; i <= _position.size(); i++)
	{
		_position.assign(i,setPos);
		//fills the other positions in adjacent based on how big the ship is
		setPos.first++;
		setPos.second++;
	}
}
