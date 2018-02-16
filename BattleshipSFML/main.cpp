
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` fromm ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Battleship!");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
   
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "graph.gif")) {
        return EXIT_FAILURE;
    }
    
    texture.setSmooth(true);
    sf::Sprite sprite(texture);

    
    sf::Texture planeImage;
    
    
    planeImage.setSmooth(true);
    if(!planeImage.loadFromFile(resourcePath() + "paper-plane2.png")){
        return EXIT_FAILURE;
    }
    sf::Vector2u plane_size = planeImage.getSize();
    sf::Sprite plane(planeImage);
    plane.scale(0.65f, 0.65f);
    plane.setOrigin(static_cast<float>(plane_size.x/2), static_cast<float>(plane_size.y/2));
    plane.setPosition(window.getSize().x/2, window.getSize().y);
    plane.rotate(70.5f);
    

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "swoosh2.ogg")) {
        return EXIT_FAILURE;
    }

   

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            music.play();
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            plane.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);
        window.draw(plane);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
