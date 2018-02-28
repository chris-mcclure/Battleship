
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "screens.hpp"

int main(int, char const**)
{
	std::vector<cScreen*> Screens;
	int currentScreen = 0;

	//Window creation
	sf::RenderWindow App(sf::VideoMode(1000, 800, 32), "Battleship!");
	App.setKeyRepeatEnabled(false);
	App.setFramerateLimit(60);

	//Screens preparations
	mainMenu s0;
	Screens.push_back(&s0);
	playScreen s1;
	Screens.push_back(&s1);
	switchTurnScreen s2;
	Screens.push_back(&s2);



	 
	//Main loop
	while (currentScreen >= 0)
	{
		currentScreen = Screens[currentScreen]->Run(App);
		if (currentScreen == 0) //if return to main menu, reset the game state
		{
			//write a reset function for playScreen that will be called here
		}
	}

	return EXIT_SUCCESS;
}
