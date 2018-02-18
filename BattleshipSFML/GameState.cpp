#include "GameState.h"
#include "Player.h"
#include <vector>

GameState::GameState()
{
	_playerVec.reserve(2);
	for (auto i : _playerVec)
	{
		_playerVec.push_back(Player());
	}
}


GameState::~GameState()
{
}

//mainMenu()
//displays the main menu and allows the user to choose to start a game in one player or two player mode
void GameState::mainMenu()
{
	//display menu
	//take input from user: one player or two player start game
	startGame();

}
//startGame()
//initializes a new game
void GameState::startGame()
{
	auto currentPlayer = 0;
	bool isGameOver = false;
	//display on screen: player one place ships
	placeShips(0);
	changeTurns(); //delay screen
	//display on screen: player two place ships
	placeShips(1);

	while (!isGameOver)
	{ 
		playerTurn(currentPlayer);
		currentPlayer = 1 - currentPlayer; //alternates the player turns
		//check for game over

	}
	//game is over at this point
	//promt player with play again buttons
	//if yes, call mainMenu()
	//if no, exit

}

//changeTurns()
//clears the screen, and gives the user a 5 second delay to switch seats
void GameState::changeTurns()
{
	//display: next players turn, change seats
	//display countdown from 5 
}


void GameState::playerTurn(int currentPlayer)
{
	std::pair<int, int> attackPos;
	//prompt user for attack position
	if (_playerVec[1 - currentPlayer].targetHit(attackPos))//check OTHER players ships for damage
	{
		//display message: target hit wowie great job champ
	}
}

//first turn of game player will choose where to put their ships
void GameState::placeShips(int currentPlayer)
{
	//take mouse input from user
	//set location of ship coordinates
}
