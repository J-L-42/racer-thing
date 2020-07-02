/*
 * Tile.cpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#include "Tile.hpp"

Tile::Tile(int x, int y, Type type) : x(x), y(y), type(type) {
    width = 0;
    height = 0;
    image = nullptr;

    if (type == PLAZA)
        friction = 0.4;

    setWalls();
}

void Tile::render(sf::RenderWindow* window) {
    window->draw(sprite);
}

void Tile::setImage(sf::Texture* image) {
    this->image = image;
    width = image->getSize().x;
    height = image->getSize().y;
    sprite.setTexture(*image);
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(x, y);
    sprite.setScale(2.5, 2.5);
}

void Tile::setWalls() {
    switch (type) {
    case EW:
        wallUp = true;
        wallDown = true;
        break;
    case NE:
        wallLeft = true;
        wallDown = true;
        break;
    case NEWS:
        break;
    case NS:
        wallLeft = true;
        wallRight = true;
        break;
    case NW:
        wallRight = true;
        wallDown = true;
        break;
    case PLAZA:
        break;
    case SE:
        wallLeft = true;
        wallUp = true;
        break;
    case SW:
        wallRight = true;
        wallUp = true;
        break;
    case TE:
        wallLeft = true;
        break;
    case TN:
        wallDown = true;
        break;
    case TS:
        wallUp = true;
        break;
    case TW:
        wallRight = true;
        break;
    }
}

void Tile::addVisited(Car* npc) {
    visited.add(npc);
}

void Tile::removeVisited(Car* npc) {
    visited.remove(npc);
}

Tile::~Tile() {
    visited.clear();
    image = nullptr;
}
