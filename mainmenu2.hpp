#ifndef main_menu
#define main_menu


#include <SFML/Graphics.hpp>
#include "cScreen.hpp"
#include "menu.h"
#include <iostream>
#define NUM_OF_SELECTIONS 3
using std::cout;
using std::endl;

class mainMenu : public cScreen
{
public:
    mainMenu();
    virtual int Run(sf::RenderWindow &App);
};

mainMenu::mainMenu()
{
}


int mainMenu::Run(sf::RenderWindow &App)
{
    Menu menu(App);
    sf::Event event;
    while (App.isOpen())
    {
        while (App.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyReleased:
                    switch(event.key.code)
                {
                    case sf::Keyboard::Key::Up:
                        menu.moveUp();
                        break;
                    case sf::Keyboard::Key::Down:
                        menu.moveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch(menu.getKeyPressed())
                    {
                        case 0:
                            std::cout << "play button pressed." << std::endl;
                            break;//return(1);
                        case 1:
                            std::cout << "option button pressed." << std::endl;
                            break;
                        case 2:
                            App.close();
                            break;
                    }
                }
        }
        App.clear();
       // menu.draw(App);
        App.display();
        
    }
        return -1;
}

#endif /* main menu */
