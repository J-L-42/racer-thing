/*
 * Car.hpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_CARS_CAR_HPP_
#define MAIN_ENTITIES_CARS_CAR_HPP_


#include <random>

#include "../../Util/ExtraMath.hpp"
#include "../../Util/Instanceof.hpp"
#include "../../Util/Collisions/TransformedBoundingBox.hpp"
#include "../../Util/Point.hpp"
#include "../../Tiles/Tile.hpp"
#include "../../Entities/Tree.hpp"
#include "../../Assets.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

#ifndef SFML_AUDIO
#define SFML_AUDIO

#include <SFML/Audio.hpp>

#endif

class Tile;

class Car {
protected:
    /* Car's position */
    float x, y, prevX, prevY;
    /* Car's size */
    int width, height;
    /* Car's rotation */
    float rotation, prevRotation;

    bool crashed = false, collision = false, inCrashQueue = false;

    float speed;

    sf::Sprite sprite;
    sf::Texture* image;

    /* Generator for AI */
    std::mt19937_64 random;
public:
    Car(float x, float y, sf::Texture* image);

    void init();
    virtual void render(sf::RenderWindow* window);
    virtual void update(float delta, const Point* pos, const Tile* currentTile) = 0;
    virtual void handleCollisions(Car* other, float delta) = 0;
    virtual void handleCollisions(Tree* other, float delta) = 0;
    inline float getX() const { return x; }
    inline float getY() const { return y; }
    inline float getRotation() const { return rotation; }
    inline float getSpeed() const { return speed; }
    inline bool isCrashed() const { return crashed; }
    void putInCrashQueue(bool inCrashQueue);
    inline bool isInCrashQueue() const { return inCrashQueue; }
    inline virtual sf::Transformable* getSprite() { return &sprite; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }

    virtual ~Car();
};


#endif /* MAIN_ENTITIES_CARS_CAR_HPP_ */
