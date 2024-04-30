// Main.cpp : Holds the main() function and needs all others through include
//

#include <iostream>
#include <SFML/Graphics.hpp> // This includes SFML/Window.hpp
#include <windows.h> // MUST BE AFTER SFML INCLUDES

int main()
{
    // Cout something to console so it is shown to be running
    std::cout << "Hello World! Starting window..." << std::endl;

    // Create a window and make it the size of the screen resolution and maximize it
    // (can and should be modified later)
    sf::RenderWindow startingMenu(sf::VideoMode::getDesktopMode(), "Character Sheet Manager | Start");
    ::ShowWindow(startingMenu.getSystemHandle(), SW_MAXIMIZE);
    startingMenu.setFramerateLimit(60);

    // Load the font
    sf::Font fullFont;
    fullFont.loadFromFile("Merriweather-Regular.ttf");

    // Set up the placeholder and its position
    sf::Text holderText("thing", fullFont);
    holderText.setFillColor(sf::Color::Black);
    holderText.setPosition(sf::Vector2f(
        (startingMenu.getSize().x / 2) - (holderText.getGlobalBounds().width / 2),
        (startingMenu.getSize().y / 2) - (holderText.getGlobalBounds().height / 2)
    ));
    holderText.setStyle(sf::Text::Regular);
    
    // Perform the loop for the starting menu window (eventually will be sent to a header file)
    while (startingMenu.isOpen()) {

        // Check for all events occuring within window
        sf::Event event;
        while (startingMenu.pollEvent(event)) {

            // In the event it is closed, cleanly run closing process and exit loops
            if (event.type == sf::Event::Closed) {
                startingMenu.close();
                break;
            }
        }

        startingMenu.clear(sf::Color(100, 255, 255));
        startingMenu.draw(holderText);

        startingMenu.display();
    }

    return 0;
}