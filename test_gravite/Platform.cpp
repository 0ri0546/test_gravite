#include "Platform.hpp"

Platform::Platform() {};

Platform::Platform(float x, float y, float width, float height) {
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(x, y);
}

sf::RectangleShape Platform::getShape() const {
	return shape;
}