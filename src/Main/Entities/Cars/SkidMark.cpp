/*
 * SkidMark.cpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#include "SkidMark.hpp"

SkidMark::SkidMark(float x, float y, float rotation) : x(x), y(y), rotation(rotation) {
    image = &AssetLoader::skidImage;

    width = image->getSize().x;
    height = image->getSize().y;
    sprite.setTexture(*image);
    sprite.setOrigin(width / 2.0, height / 2.0);
    sprite.setPosition(x, y);
    sprite.setRotation(rotation);
}

void SkidMark::render(sf::RenderWindow* window) {
    window->draw(sprite);
}

void SkidMark::update(float delta) {
    life -= 1.0 * delta;
    if (life < 0)
        life = 0;
}

SkidMark::~SkidMark() {
    image = nullptr;
}
