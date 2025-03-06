#include "Game.hpp"

Game::Game() : window(sf::VideoMode(WIDTH, HEIGHT), "tests gravite") {
	window.setFramerateLimit(60);
	platform = Platform(0, 550, 800, 20);
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void Game::update() {
	player.update(platform, window);
}

void Game::render() {
	window.clear();
	window.draw(player.getShape());
	window.draw(player.getShapeAtk());
	window.draw(platform.getShape());
	window.display();
}