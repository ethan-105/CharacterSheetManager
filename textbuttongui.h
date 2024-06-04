#pragma once
#include "interactgui.h"
#include <string>

// Needs to handle: 
//   Needs to display specific text and perform an action when clicked
//   May need to change when hovered
//   
//   


class TextButtonGui : virtual public InteractGui {
	sf::Color backgroundColor;
	sf::RectangleShape textBox;
	sf::Text text;
	sf::Vector2f padPerc = sf::Vector2f(0.5f, 0.5f);

public:
	TextButtonGui(sf::Font& font, std::string textWords, sf::RenderWindow& window, sf::View& view, sf::Shape& canvasShape) 
		: InteractGui(window, view, canvasShape){
		text = sf::Text(textWords, font, 30);
		text.setFillColor(sf::Color::Black);
		textBox.setOutlineThickness(3);
		textBox.setOutlineColor(sf::Color::Black);
	}

	void updateBoundsToText() {
		bounds = text.getLocalBounds();
		bounds = sf::FloatRect(
			(-(padPerc.x * bounds.width) / 2.0f),
			(-(padPerc.y * bounds.height) / 2.0f),
			(padPerc.x + 1) * bounds.width,
			(padPerc.y + 1) * bounds.height
		);
		textBox.setSize(bounds.getSize());
		textBox.setPosition(
			text.getPosition() + sf::Vector2f(bounds.left, bounds.top)
		);
		textBox.setOutlineThickness(text.getCharacterSize()/10);
		bounds = textBox.getGlobalBounds();
	}

	void setTextSize(unsigned int size) {
		text.setCharacterSize(size);
		setNormCenter(normCenter);
	}

	void loadFont(sf::Font& font) {
		text.setFont(font);
	}

	
	sf::Text& getTextRef() {
		return text;
	}

	// Draw the button to the screen
	void draw() {
		sf::View oldView = windowPtr->getView();
		windowPtr->setView(*viewPtr);
		windowPtr->draw(textBox);
		windowPtr->draw(text);
		windowPtr->setView(oldView);
	}

	void updateAllToBounds() {
		sf::Vector2f newPos = sf::Vector2f(
			-(text.getGlobalBounds().getSize().x / 2) + bounds.getPosition().x + (bounds.getSize().x / 2),
			-(text.getGlobalBounds().getSize().y / 2) + bounds.getPosition().y + (bounds.getSize().y / 2)
		);
		text.setPosition(newPos);
		updateBoundsToText();
	}

	// Does nothing with other inputs, just cares about when clicked
	void dealWithInputs(sf::Event& userEvent) {
		return;
	}
};