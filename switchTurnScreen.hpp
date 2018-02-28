#pragma once
#include <SFML\Graphics.hpp>
#include "cScreen.hpp"

class switchTurnScreen : public cScreen
{
public:
	sf::Text countdown[5];
	sf::Text banner;
	sf::Font font;

	switchTurnScreen();

	virtual int Run(sf::RenderWindow & App)
	{
		sf::Clock clock;
		sf::Time delay = sf::milliseconds(600);
		sf::Time timeSince;
		sf::Time now;

		banner.setFont(font);
		banner.setCharacterSize(50);
		banner.setString("Switching turns...");
		banner.setPosition(sf::Vector2f(380, 220));

		int k = 0;

		std::string numbers[5] = { "5","4","3","2","1" };

		for (int i = 0; i < 5; i++)
		{
			countdown[i].setFont(font);
			countdown[i].setFillColor(sf::Color::Cyan);
			countdown[i].setString(numbers[i]);
			countdown[i].setCharacterSize(90);
			countdown[i].setPosition(500, 330);
			countdown[i].setStyle(sf::Text::Bold);
		}

		while (App.isOpen())
		{
			App.clear();

			now = clock.getElapsedTime();
			//std::cout << "now : "<< now.asSeconds() << std::endl;
			//std::cout <<"timeSince: " << timeSince.asSeconds() << std::endl;

			if ((now - timeSince) >= delay)
			{
				timeSince = now;
				k++;
				if (k == 5)
					return(1);
			}
			App.draw(countdown[k]);
			App.draw(banner);
			App.display();
		}
	};
};
switchTurnScreen::switchTurnScreen()
{
	font.loadFromFile("Amatic-Bold.ttf");
}
