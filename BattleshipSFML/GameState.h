#pragma once
#include "Player.h"

class GameState
{
private:
	std::vector<Player> _playerVec;
	//gamestate member objects

public:
	//gamestate ctors/dtors
	GameState();
	~GameState();

	//gamestate member functions
	void mainMenu();
	void startGame(); 
	void changeTurns();
	void placeShips(int currentPlayer);
	void playerTurn(int currentPlayer);
};

