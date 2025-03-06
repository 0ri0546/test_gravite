#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP
#pragma once

#include "Datas.hpp"

class Projectiles {
public:
	Projectiles(bool lastDepIsLeft, sf::RectangleShape player);
	const sf::RectangleShape& getShape() const;
	void update();

private:
	float speed = 5.f;
	bool lastDepIsLeft;
	
	sf::RectangleShape shape, player;
};


#endif

