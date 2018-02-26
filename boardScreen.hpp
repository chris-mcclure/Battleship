//
//  boardScreen.hpp
//  BattleshipSFML_v2
//
//  Created by Chris McClure on 2/19/18.
//  Copyright © 2018 Chris McClure & AJ Carvajal. All rights reserved.
//

#ifndef boardScreen_h
#define boardScreen_h
#include "cScreen.hpp"

class BoardScreen : public cScreen{
public:
    BoardScreen();
    virtual int Run(sf::RenderWindow &App);
    sf::Time elapsed;
};

BoardScreen::BoardScreen(){}

int BoardScreen::Run(sf::RenderWindow &App){
    //board
    sf::Texture board_texture;
    if(!board_texture.loadFromFile(resourcePath() + "graph.png"))
        return EXIT_FAILURE;
 
    
    board_texture.setSmooth(true);
    sf::Sprite board(board_texture);
    board.setScale(1.89f, 1.425f);
     
    //plane
    sf::Texture planeImage;
    if(!planeImage.loadFromFile(resourcePath() + "paper-plane2.png")){
        return EXIT_FAILURE;
    }
    planeImage.setSmooth(true);
    sf::Sprite plane(planeImage);
    plane.setOrigin(110, plane.getTexture()->getSize().y-100);
    plane.rotate(132.5f);
    plane.scale(0.65f, 0.65f);
    plane.setPosition(sf::Vector2f(-100, 100));
    sf::Vector2f planeCoords;
    
    //bomb
    sf::Texture bombImage;
    if(!bombImage.loadFromFile(resourcePath() + "bomb.png"))
        return EXIT_FAILURE;
    bombImage.setSmooth(true);
    sf::Sprite bomb(bombImage);
    bomb.setOrigin(bomb.getTexture()->getSize().x/3, bomb.getTexture()->getSize().y/1.5);
    bomb.scale(0.1,0.1);
    bool flag = false;
    sf::Sprite tempBomb = bomb;
    
    
    //event loop
    sf::Event event;
    while (App.isOpen()) {
        while(App.pollEvent(event))
        {
            //close window
            if(event.type == sf::Event::Closed)
                App.close();
            
            //Escape pressed: exit
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                return(0);
            }
            
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                planeCoords = sf::Vector2f(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
                plane.setPosition(planeCoords.x, App.getSize().y+30);
            }
        }
        
  
        plane.move(sf::Vector2f(0, -15));

        
        App.clear(); 
        App.draw(board);
        
        
        if(((plane.getPosition().y - planeCoords.y) <= 15)
           && (plane.getPosition().y - planeCoords.y) >= 0
           && (plane.getPosition().y != 10)){
            bomb.setPosition(planeCoords.x, planeCoords.y);
            flag = true;
        }
        
        if(flag){
            App.draw(bomb);
            bomb.scale(0.9, 0.9);
            if(bomb.getScale().x < .001){
                bomb = tempBomb;
                flag = false;
            }
        }
        
        
        App.draw(plane);
        App.display();
    }
    return 2;
}

#endif /* boardScreen_h */
