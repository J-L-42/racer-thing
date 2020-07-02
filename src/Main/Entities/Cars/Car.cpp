/*
 * Car.cpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#include "Car.hpp"

Car::Car(float x, float y, sf::Texture* image) : x(x), y(y), image(image) {
    sprite.setPosition(x, y);
    width = 0;
    height = 0;
    rotation = 0;
    speed = 0;

    prevX = 0;
    prevY = 0;
    prevRotation = 0;
}

void Car::init() {
    speed = 0;
    width = image->getSize().x;
    height = image->getSize().y;
    sprite.setTexture(*image);
    sprite.setOrigin((float) width * (5.0 / 6.0), (float) height / 2.0);
}

void Car::render(sf::RenderWindow* window) {
    sprite.setPosition(x, y);
    sprite.setRotation(rotation);
    window->draw(sprite);
}

void Car::putInCrashQueue(bool inCrashQueue) {
    this->inCrashQueue = inCrashQueue;
}

Car::~Car() {
    image = nullptr;
}
