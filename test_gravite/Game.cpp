#include "Game.hpp"

Game::Game() : window(sf::VideoMode(WIDTH, HEIGHT), "tests gravite") {
	window.setFramerateLimit(60);
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(player.getShape().getPosition());

}

void Game::addPlatform(float x, float y, float width, float height) {
	platforms.push_back(Platform(x, y, width, height));
}

void Game::run() {
	addPlatform(0, 550, 800, 20);
	addPlatform(300, 400, 500, 20);
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

	player.update(platforms, window, view);
	view.setCenter(player.getShape().getPosition());
}

void Game::render() {
	window.clear();

	window.draw(player.getShape());
	window.draw(player.getShapeAtk());
	window.draw(player.getShapeSmoke());
	window.draw(player.getShapeHUDEnergy());
	window.draw(player.getShapeFillEnergy());

	for (auto platform : platforms) {
		window.draw(platform.getShape());
	}

	window.setView(view);
	
	window.display();
}