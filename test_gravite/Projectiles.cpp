#include "Projectiles.hpp"

Projectiles::Projectiles(bool lastDepIsLeft, sf::RectangleShape player) : lastDepIsLeft(lastDepIsLeft) {
	shape.setSize(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color::Magenta);

	if (lastDepIsLeft) {
		shape.setPosition(player.getPosition().x - 20, player.getPosition().y + player.getSize().y / 2 - shape.getSize().y / 2);
	}
	else {
		shape.setPosition(player.getPosition().x + player.getSize().x, player.getPosition().y + player.getSize().y / 2 - shape.getSize().y / 2);
	}
}

void Projectiles::update() {
	if (lastDepIsLeft) {
		shape.move(-speed, 0);
	}
	else {
		shape.move(speed, 0);
	}
}

const sf::RectangleShape& Projectiles::getShape() const {
	return shape;
}