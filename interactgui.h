#pragma once
#include <iostream>
#include <SFML/Graphics.hpp> // This includes SFML/Window.hpp

// Needs to handle: 
//   Being clicked/selected
//   Drawing self onto window/view(dependent on specific gui)
//   Ignoring input when not selected and being able to toggle selection
//   Needs a hitbox for clicks
//   Needs a thing to deal with any input events
//   


class InteractGui {
protected:
	bool selected = false;
	sf::FloatRect bounds = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
	sf::Vector2f normCenter = sf::Vector2f(0.0f, 0.0f);
	sf::Shape* canvasShapePtr = nullptr;
	sf::View* viewPtr = nullptr;
	sf::RenderWindow* windowPtr = nullptr;
public:
	InteractGui(sf::RenderWindow& window, sf::View& view, sf::Shape& canvasShape) {
		selected = false;
		viewPtr = &view;
		windowPtr = &window;
		canvasShapePtr = &canvasShape;
	}

	// Return the pixel bounds of the relative ones
	sf::IntRect getPixelBounds() {
		sf::Vector2i topLeft = sf::Vector2i(
			windowPtr->mapCoordsToPixel(
				bounds.getPosition(),
				*viewPtr
			)
		);
		sf::Vector2i bottomRight = sf::Vector2i(
			windowPtr->mapCoordsToPixel(
				bounds.getPosition() + bounds.getSize(),
				*viewPtr
			)
		);
		return sf::IntRect(topLeft, (bottomRight - topLeft));
	}

	// Returns if selected was changed
	bool forceselect() {
		bool selectedChanging = !selected;
		selected = true;
		return selectedChanging;
	}

	// Returns if selected was changed
	bool deselect() {
		bool selectedChanging = !selected;
		selected = true;
		return selectedChanging;
	}
	
	// Set the bounds for the click checks (Within a specific view)
	void setBounds(sf::FloatRect newBounds) {
		bounds = newBounds;
	}

	// Stores the view for a particular window which the image is drawn onto
	// (Necessary for size and position to stay consistent)
	void setView(sf::View& view) {
		viewPtr = &view;
	}

	void setWindow(sf::RenderWindow& window) {
		windowPtr = &window;
	}

	void setCanvasShape(sf::Shape& canvasShape) {
		canvasShapePtr = &canvasShape;
	}

	// Just in case this is needed for some reason
	void resetView() {
		viewPtr = nullptr;
	}

	void resetWindow() {
		windowPtr = nullptr;
	}

	void resetCanvasShape() {
		canvasShapePtr = nullptr;
	}

	// Return whether or not it was clicked
	bool checkIfClicked(sf::Vector2i mousePos) {
		// Transform the mouse positions to view coordinates
		sf::Vector2f relClickPos = windowPtr->mapPixelToCoords(mousePos);

		bool clickIsInBounds = bounds.contains(relClickPos);
		if (clickIsInBounds) {
			selected = true;
		}
		return clickIsInBounds;
	}

	// Call the above check with slightly different arguments
	bool checkIfClicked(int mouseX, int mouseY) {
		return checkIfClicked(sf::Vector2i(mouseX, mouseY));
	}

	// An accessor for selected
	bool isSelected() {
		return selected;
	}

	void setNormCenter(sf::Vector2f newNormCenter) {
		normCenter = newNormCenter;
		sf::Vector2f size = bounds.getSize();
		bounds = sf::FloatRect(
			sf::Vector2f(
				-(size.x / 2) + (newNormCenter.x * canvasShapePtr->getGlobalBounds().getSize().x),
				-(size.y / 2) + (newNormCenter.y * canvasShapePtr->getGlobalBounds().getSize().y)
			),
			size
		);
		updateAllToBounds();
	}

	// Must be implemented in derived classes
	virtual void draw() = 0;
	virtual void updateAllToBounds() = 0;
	virtual void dealWithInputs(sf::Event& userEvent) = 0;
};