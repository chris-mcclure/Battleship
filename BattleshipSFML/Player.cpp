#include "Player.h"
#include "Ship.h"

Player::Player()
{
	_shipVec.reserve(SHIPCOUNT);
	for (auto i : _shipVec) 
	{
		_shipVec.push_back(Ship(i));
	}
}


Player::~Player()
{
}

void Player::showPlayerBoard()
{

}

bool Player::targetHit(std::pair<int,int> attackLocation)
{
	for (int i = 0; i <= _shipVec.size(); i++)
	{
		for (int k = 0; k <= _shipVec[i]._position.size(); i++)
		{
			if (_shipVec[i]._position[k] == attackLocation)
			{
				//hit found
				_shipVec[i]._position[k] = _shipVec[i].DEFAULT_POS;
				_shipVec[i]._size--;
				//check to see if it destroyed it
				if (_shipVec[i]._size == 0)
				{
					_shipVec[i]._isAlive = false;
					//display message that ship has been blown up
				}
				return true;
			}
		}
	}

	return false;
}
