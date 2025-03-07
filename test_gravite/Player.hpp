#ifndef PLAYER_HPP
#define PLAYER_HPP
#pragma once

#include "Datas.hpp"
#include "Platform.hpp"
#include "Projectiles.hpp"

class Player {
public:
	Player(); 
	void update(const std::vector<Platform>& platforms, sf::RenderWindow& window, sf::View& view);
	void jump();
	void useJetpack();
	void deplacement();
	void border();
	void collide(const std::vector<Platform>& platforms);
	float attack();
	void rangedAttack(sf::RenderWindow& window);
	void updateHUDEnergy(sf::View& view);

	sf::RectangleShape getShape() const;
	sf::RectangleShape getShapeAtk() const;
	sf::RectangleShape getShapeSmoke() const;
	sf::RectangleShape getShapeHUDEnergy() const;
	sf::RectangleShape getShapeFillEnergy() const;

private:
	sf::RectangleShape shape, shapeAtk, shapeRangedAtk, shapeSmoke, shapeEnergy, shapeFillEnergy;
	sf::Clock attackClock;
	sf::Clock attackDurationClock;


	float velocityY;
	float gravity;
	bool isOnGround;
	int jumpCount;
	const int maxJumps = 2;
	bool canJump;
	bool lastDepIsLeft;

	float energy;
	float maxJetpackEnergy;
	float jetpackPower;
	float energyConsumption;
	float energyRecharge;
	float damage;

	int hp;

	std::vector<Projectiles> projectiles;
};

#endif
