#pragma once
#include <vector>
#include "Ship.h"

class Player
{
private:
	const int SHIPCOUNT = 4;
	std::vector<Ship> _shipVec; //contains all the ships for the player

public:
	//player ctors/dtors
	Player();
	~Player();

	//player member functions
	void showPlayerBoard();
	bool targetHit(std::pair<int,int> attackLocation);
};

