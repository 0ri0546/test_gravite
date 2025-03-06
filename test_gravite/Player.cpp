#include "Player.hpp"

Player::Player() {
	shape.setSize(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(400, 200);
	velocityY = 0;
	gravity = 0.5f;
	isOnGround = false;
	jumpCount = maxJumps;
	canJump = true;
	lastDepIsLeft = true;
}

void Player::update(const Platform& platform, sf::RenderWindow& window) {
	border();
	collide(platform);
	jump();
	deplacement();
	attack();
	rangedAttack(window);
	//std::cout << "Nombre de projectiles : " << projectiles.size() << std::endl;
}

void Player::jump() {
	if (!isOnGround) {
		velocityY += gravity;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumpCount > 0 && canJump) {
		velocityY = -10.0f;
		jumpCount--;
		canJump = false;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		canJump = true;
	}

	shape.move(0, velocityY);
}


void Player::collide(const Platform& platform) {
	if (shape.getGlobalBounds().intersects(platform.getShape().getGlobalBounds())) {
		if (velocityY > 0) {
			isOnGround = true;
			velocityY = 0;
			shape.setPosition(shape.getPosition().x, platform.getShape().getPosition().y - shape.getSize().y);
			jumpCount = maxJumps;
		}
	}
	else {
		isOnGround = false;
	}
}


void Player::deplacement() {
	sf::Vector2f nPos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		nPos.x = 10.0f;
		lastDepIsLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		nPos.x = -10.0f;
		lastDepIsLeft = true;
	}
	shape.move(nPos);
}

void Player::border() {
	if (shape.getPosition().x <= 0) {
		shape.setPosition(0, shape.getPosition().y);
	}
	if (shape.getPosition().x + shape.getSize().x >= WIDTH) {
		shape.setPosition(WIDTH - shape.getSize().x, shape.getPosition().y);
	}
}

void Player::attack() {
	shapeAtk.setSize(sf::Vector2f(1, 1));
	shapeAtk.setFillColor(sf::Color::Transparent);
	shapeAtk.setPosition(9999, 9999);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		shapeAtk.setSize(sf::Vector2f(30, 50));
		shapeAtk.setFillColor(sf::Color::Blue);
		if (lastDepIsLeft) {
			shapeAtk.setPosition(shape.getPosition().x - 30, shape.getPosition().y);
		}
		else {
			shapeAtk.setPosition(shape.getPosition().x + shape.getSize().x, shape.getPosition().y);
		}
	}
}

void Player::rangedAttack(sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) { 
		projectiles.push_back(Projectiles(lastDepIsLeft, shape));
	}
	
	for (auto& projectile : projectiles) {
		projectile.update();
		std::cout << "Projectile position: " << projectile.getShape().getPosition().x << ", " << projectile.getShape().getPosition().y << std::endl;
		window.draw(projectile.getShape());
	}


	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectiles& p) {
		return p.getShape().getPosition().x < 0 || p.getShape().getPosition().x > WIDTH;
		}), projectiles.end());


}

sf::RectangleShape Player::getShape() const {
	return shape;
}

sf::RectangleShape Player::getShapeAtk() const {
	return shapeAtk;
}

