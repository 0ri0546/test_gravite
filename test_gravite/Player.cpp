#include "Player.hpp"

Player::Player() {
	shape.setSize(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(400, 200);
	velocityY = 0;
	gravity = 0.5f;
	isOnGround = false;

	//jumpCount = maxJumps;
	//canJump = true;

	lastDepIsLeft = true;

	jetpackEnergy = 1000.f;
	maxJetpackEnergy = 1000.f;
	jetpackPower = -3.f;
	energyConsumption = 0.5f;
	energyRecharge = 0.1f;

	shapeEnergy.setSize(sf::Vector2f(100, 30));
	shapeEnergy.setFillColor(sf::Color::Transparent);
	shapeEnergy.setOutlineColor(sf::Color::White);
	shapeEnergy.setOutlineThickness(2);
	shapeEnergy.setPosition(20, 20);
}

void Player::update(const std::vector<Platform>& platforms, sf::RenderWindow& window, sf::View& view) {
	border();
	collide(platforms);
	//jump();
	useJetpack();
	deplacement();
	attack();
	rangedAttack(window);
	//std::cout << "Nombre de projectiles : " << projectiles.size() << std::endl;

	updateHUDEnergy(view);
	std::cout << "Énergie du Jetpack : " << jetpackEnergy << std::endl;
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

void Player::useJetpack() {
	if (!isOnGround) {
		velocityY += gravity;
	}
	shapeSmoke.setPosition(9999, 9999);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jetpackEnergy > energyConsumption) {
		velocityY = jetpackPower; 
		jetpackEnergy -= energyConsumption;
		shapeSmoke.setSize(sf::Vector2f(30, 50));
		shapeSmoke.setFillColor(sf::Color::Yellow);
		if (lastDepIsLeft) {
			shapeSmoke.setPosition(shape.getPosition().x + shape.getSize().x / 2, shape.getPosition().y + 30);
		}
		else {
			shapeSmoke.setPosition(shape.getPosition().x - 30 + shape.getSize().x / 2, shape.getPosition().y + 30);
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jetpackEnergy < maxJetpackEnergy) {
		jetpackEnergy += energyRecharge; 
	}

	if (jetpackEnergy > maxJetpackEnergy) {
		jetpackEnergy = maxJetpackEnergy;
	}

	shape.move(0, velocityY);
}

void Player::collide(const std::vector<Platform>& platforms) {
	isOnGround = false;

	for (const auto& platform : platforms) {
		if (shape.getGlobalBounds().intersects(platform.getShape().getGlobalBounds())) {
			sf::FloatRect playerBounds = shape.getGlobalBounds();
			sf::FloatRect platformBounds = platform.getShape().getGlobalBounds();

			float playerLeft = playerBounds.left;
			float playerRight = playerBounds.left + playerBounds.width;
			float playerTop = playerBounds.top;
			float playerBottom = playerBounds.top + playerBounds.height;

			float platformLeft = platformBounds.left;
			float platformRight = platformBounds.left + platformBounds.width;
			float platformTop = platformBounds.top;
			float platformBottom = platformBounds.top + platformBounds.height;

			if (velocityY > 0 && playerBottom > platformTop && playerTop < platformTop) { //bas
				isOnGround = true;
				velocityY = 0;
				shape.setPosition(shape.getPosition().x, platformTop - shape.getSize().y);
			}
			else if (velocityY < 0 && playerTop < platformBottom && playerBottom > platformBottom) { //haut
				velocityY = 0;
				shape.setPosition(shape.getPosition().x, platformBottom);
			}
			else if (playerRight > platformLeft && playerLeft < platformLeft && velocityY >= 0) { //gauche
				shape.setPosition(platformLeft - playerBounds.width, shape.getPosition().y);
			}
			else if (playerLeft < platformRight && playerRight > platformRight && velocityY >= 0) { //droite
				shape.setPosition(platformRight, shape.getPosition().y);
			}
		}
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && jetpackEnergy > 1) {
		shapeAtk.setSize(sf::Vector2f(30, 50));
		shapeAtk.setFillColor(sf::Color::Blue);
		if (lastDepIsLeft) {
			shapeAtk.setPosition(shape.getPosition().x - 30, shape.getPosition().y);
		}
		else {
			shapeAtk.setPosition(shape.getPosition().x + shape.getSize().x, shape.getPosition().y);
		}
		jetpackEnergy -= 1.0;
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

void Player::updateHUDEnergy(sf::View& view) {
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();

	float hudX = viewCenter.x - (viewSize.x / 2) + 20;
	float hudY = viewCenter.y - (viewSize.y / 2) + 20;

	shapeFillEnergy.setSize(sf::Vector2f((jetpackEnergy / maxJetpackEnergy) * 100, 30));
	shapeFillEnergy.setFillColor(sf::Color::Green);

	shapeEnergy.setPosition(hudX, hudY);
	shapeFillEnergy.setPosition(hudX, hudY);


	//shapeEnergy.setSize(sf::Vector2f((jetpackEnergy / maxJetpackEnergy) * 100, 30));
}

sf::RectangleShape Player::getShape() const {
	return shape;
}

sf::RectangleShape Player::getShapeAtk() const {
	return shapeAtk;
}

sf::RectangleShape Player::getShapeSmoke() const {
	return shapeSmoke;
}

sf::RectangleShape Player::getShapeHUDEnergy() const {
	return shapeEnergy;
}

sf::RectangleShape Player::getShapeFillEnergy() const {
	return shapeFillEnergy;
}



