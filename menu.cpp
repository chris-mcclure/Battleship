//
//  menu.cpp
//  BattleshipSFML
//
//  Created by Chris McClure on 2/18/18.
//  Copyright © 2018 Chris McClure & AJ Carvajal. All rights reserved.
//


#include "menu.h"
#include <iostream>
Menu::Menu(sf::RenderWindow &App){
    if(!menuBackground.loadFromFile(resourcePath() + "graph.png"))
        return EXIT_FAILURE;
    
    
    if(!font.loadFromFile(resourcePath() + "Amatic-Bold.ttf")){
        return EXIT_FAILURE;
    }
    
    menuBackground.setSmooth(true);
    sf::Sprite board(menuBackground);
    board.setScale(1.425f, 1.425f);
    
    
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play Game!");
    menu[0].setCharacterSize(100);
    menu[0].setPosition(sf::Vector2f(App.getSize().x/2, App.getSize().y/(NUM_OF_SELECTIONS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setCharacterSize(100);
    menu[1].setPosition(sf::Vector2f(App.getSize().x/2, App.getSize().y/(NUM_OF_SELECTIONS + 1) * 2));
    
 
    
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Close");
    menu[2].setCharacterSize(100);
    menu[2].setPosition(sf::Vector2f(App.getSize().x/2, App.getSize().y/(NUM_OF_SELECTIONS + 1) * 3));

    std::cout << "here i am" << std::endl;
    selectedItemIndex = 0;
    

}

Menu::~Menu(){
    
}

void Menu::draw(sf::RenderWindow &window){
    for(int choice = 0; choice < NUM_OF_SELECTIONS; choice++){
        window.draw(menu[choice]);
    }
}

void Menu::moveUp(){
    if(selectedItemIndex - 1 >= 0){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown(){
    if(selectedItemIndex + 1 < NUM_OF_SELECTIONS){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
