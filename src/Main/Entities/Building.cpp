/*
 * Building.cpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#include "Building.hpp"

Building::Building(int x, int y, Type type) : x(x), y(y), type(type) {
    width = 0;
    height = 0;
    image = nullptr;
}

void Building::render(sf::RenderWindow* window) {
    window->draw(sprite);
}

void Building::setImage(sf::Texture* image) {
    this->image = image;
    width = image->getSize().x;
    height = image->getSize().y;
    sprite.setTexture(*image);
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(x, y);
    sprite.setScale(2.5, 2.5);
}

Building::~Building() {
    image = nullptr;
}
