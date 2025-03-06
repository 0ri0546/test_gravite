#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include "Datas.hpp"
#include "Player.hpp"
#include "Platform.hpp"

class Game {
public:
	Game();
	void run();

private:
	sf::RenderWindow window;
	Player player;
	Platform platform;

	void processEvents();
	void update();
	void render();
};

#endif