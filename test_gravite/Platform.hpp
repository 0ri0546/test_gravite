#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#pragma once

#include "Datas.hpp"

class Platform {
public:
	Platform();
	Platform (float x, float y, float width, float height);
	sf::RectangleShape getShape() const;

private:
	sf::RectangleShape shape;
};


#endif

