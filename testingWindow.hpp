#pragma once
#include <iostream>
#include <SFML/Graphics.hpp> // This includes SFML/Window.hpp
#include <windows.h> // MUST BE AFTER SFML INCLUDES
#include "textbuttongui.h"

bool dragging = false;
bool zooming = false;
bool buttonBig = true;

void runTestWindow() {
    // Create a window and make it the size of the screen resolution and maximize it
    // (can and should be modified later)
    sf::Vector2f relativeOrigin(0, 0);
    sf::Vector2i lastPixPos(0, 0);
    sf::Vector2u origSize(0, 0);

    sf::RenderWindow startingMenu(sf::VideoMode(1600, 900), "Character Sheet Manager | Start");
    origSize = { 1600, 900 };
    sf::RectangleShape testingBg;
    testingBg.setFillColor(sf::Color(155, 155, 155));
    sf::View testingPage;
    testingBg.setSize(sf::Vector2f(960, 540));
    testingPage.reset(sf::FloatRect(0, 0, testingBg.getSize().x, testingBg.getSize().y));

    //::ShowWindow(startingMenu.getSystemHandle(), SW_MAXIMIZE);
    startingMenu.setFramerateLimit(60);

    // Load the font
    sf::Font fullFont;
    fullFont.loadFromFile("Merriweather-Regular.ttf");

    // Set up the placeholder and its position
    sf::Text holderText("thing", fullFont);
    //holderText.setCharacterSize();
    holderText.setFillColor(sf::Color::Black);
    holderText.setPosition(sf::Vector2f(
        (testingPage.getSize().x / 2) - (holderText.getGlobalBounds().width / 2),
        (testingPage.getSize().y / 2) - (holderText.getGlobalBounds().height / 2)
    ));
    sf::View defaultView = startingMenu.getDefaultView();
    TextButtonGui testText(fullFont, "Thing!", startingMenu, testingPage, testingBg);
    /*
    testText.getTextRef().setPosition(sf::Vector2f(
        (testingPage.getSize().x / 2) - (testText.getTextRef().getGlobalBounds().width / 2),
        (testingPage.getSize().y / 2) - (testText.getTextRef().getGlobalBounds().height / 2)
    ));
    */
    //testText.updateBoundsToText();
    testText.setNormCenter(sf::Vector2f(0.5f, 0.5f));

    unsigned int oldWidth = startingMenu.getSize().x;
    unsigned int oldHeight = startingMenu.getSize().y;

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

            // Check for when the window is resized
            else if (event.type == sf::Event::Resized) {
                sf::Vector2u newSize(event.size.width, event.size.height);
                sf::Vector2f ratio(
                    (float)origSize.x / (float)newSize.x,
                    (float)origSize.y / (float)newSize.y
                );

                // Set the view to maintain its ratio relative to the window
                testingPage.setViewport(sf::FloatRect(
                    (-ratio.x / 2.0f) + 0.5f,
                    (-ratio.y / 2.0f) + 0.5f,
                    ratio.x, ratio.y)
                );
            }

            // For all key pressed
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::LShift ||
                    event.key.code == sf::Keyboard::RShift) {
                    zooming = true;
                }
            }

            // For all key released
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::LShift ||
                    event.key.code == sf::Keyboard::RShift) {
                    zooming = false;
                }
            }

            // Check if they are scrolling (zooming)
            else if (event.type == sf::Event::MouseWheelScrolled) {
                if (!zooming) {
                    continue;
                }
                if (event.mouseWheelScroll.delta > 0) {
                    testingPage.zoom(0.75f);
                }
                else {
                    testingPage.zoom(4.0f / 3.0f);
                }
            }

            else if ((event.type == sf::Event::MouseButtonPressed)
                && (event.mouseButton.button == sf::Mouse::Left)) {
                // Check first if it is free grabbing territory, ignoring for now
                // Then get ready for dragging

                lastPixPos = sf::Mouse::getPosition();
                dragging = true;
            }

            else if ((event.type == sf::Event::MouseButtonReleased)
                && (event.mouseButton.button == sf::Mouse::Left)) {
                // Check first if it is free grabbing territory, ignoring for now
                // Then get ready for dragging
                dragging = false;
            }

            else if ((event.type == sf::Event::MouseMoved) && dragging) {
                // It works! (for the one view)
                sf::Vector2i curPixPos = sf::Mouse::getPosition();

                // MAP CENTER TO PIXELS
                // THEN DO PIXEL MATH
                // THEN MAP PIXELS BACK TO VIEW
                // THEN SET VIEW TO NEW COORDS

                sf::Vector2i centerPixPos = startingMenu.mapCoordsToPixel(testingPage.getCenter(), testingPage);
                sf::Vector2i newPixCenter(
                    centerPixPos.x + (lastPixPos.x - curPixPos.x),
                    centerPixPos.y + (lastPixPos.y - curPixPos.y)
                );
                lastPixPos = curPixPos;
                sf::Vector2f newRelCenter = startingMenu.mapPixelToCoords(newPixCenter, testingPage);

                testingPage.setCenter(newRelCenter);
            }

        }
        startingMenu.setView(startingMenu.getDefaultView());
        startingMenu.clear(sf::Color(0, 0, 0));
        startingMenu.setView(testingPage);
        startingMenu.draw(testingBg);
        testText.draw();
        //startingMenu.draw(holderText);


        startingMenu.display();
    }
}

