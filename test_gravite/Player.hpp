#ifndef PLAYER_HPP
#define PLAYER_HPP
#pragma once

#include "Datas.hpp"
#include "Platform.hpp"
#include "Projectiles.hpp"

class Player {
public:
	Player(); 
	void update(const Platform& platform, sf::RenderWindow& window);
	void jump();
	void deplacement();
	void border();
	void collide(const Platform& platform);
	void attack();
	void rangedAttack(sf::RenderWindow& window);

	sf::RectangleShape getShape() const;
	sf::RectangleShape getShapeAtk() const;

private:
	sf::RectangleShape shape, shapeAtk, shapeRangedAtk;
	float velocityY;
	float gravity;
	bool isOnGround;
	int jumpCount;
	const int maxJumps = 2;
	bool canJump;
	bool lastDepIsLeft;

	std::vector<Projectiles> projectiles;
};

#endif
