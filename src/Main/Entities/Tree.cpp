/*
 * Tree.cpp
 *
 *  Created on: 26 Apr 2017
 *      Author: james
 */

#include "Tree.hpp"

Tree::Tree(float x, float y, sf::Texture* image) : x(x), y(y), image(image) {
    imageWidth = 0;
    imageHeight = 0;
}

void Tree::init() {
    imageWidth = image->getSize().x;
    imageHeight = image->getSize().y;
    sprite.setTexture(*image);
    sprite.setOrigin(imageWidth / 2, imageHeight / 2);
    sprite.setPosition(x, y);
    sprite.setScale(2, 2);
}

void Tree::render(sf::RenderWindow* window) {
    window->draw(sprite);
}

void Tree::update(float delta) {

}

Tree::~Tree() {

}
