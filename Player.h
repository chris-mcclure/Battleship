#pragma once

#include <SFML\Graphics.hpp>
#include "Ship.h"

class Player
{
public:

	//ctors,dtors
	Player();
	Player(int shipCount);

	//player member objects
	int shipCount;
	bool shipSelected;
	int shipsPlacedCount;
	bool allShipsPlaced;
	bool usedAttack;
	std::vector<Ship> ships;

	//player functions
	void drawShips(sf::RenderWindow & App);
	void makeShips(std::pair<int, int> squareSize);
	void selectShip(std::pair<int, int> pos); 
	void rotateShip();
	void moveShip(std::pair<int, int> pos);
	bool shipHit(std::pair<int,int> pos); //checks ships to see if they were hit by an enemy attack
};