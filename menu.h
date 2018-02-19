//
//  menu.h
//  BattleshipSFML
//
//  Created by Chris McClure on 2/18/18.
//  Copyright © 2018 Chris McClure & AJ Carvajal. All rights reserved.
//

#ifndef menu_h
#define menu_h

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"


#define NUM_OF_SELECTIONS 3
class Menu{
public:
    sf::Texture menuBackground;
    
    Menu(sf::RenderWindow &App);
    ~Menu();
    
    void draw(sf::RenderWindow &App);
    void moveUp();
    void moveDown();
    int getKeyPressed() { return selectedItemIndex; }
    
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[NUM_OF_SELECTIONS];
};

#endif /* menu_h */

