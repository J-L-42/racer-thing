/*
 * Police.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_CARS_POLICE_HPP_
#define MAIN_ENTITIES_CARS_POLICE_HPP_


#define NUM_FRAMES 3

#include "../../Util/Animations/AnimatedSprite.hpp"
#include "../../Util/Animations/Animation.hpp"
#include "Car.hpp"
#include "Player.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

#ifndef SFML_AUDIO
#define SFML_AUDIO

#include <SFML/Audio.hpp>

#endif

class Police : public Car {
private:
    Animation anim;
    AnimatedSprite animSprite;

    int targetRotation;

    Car* target;
    Car* nearest;

    bool roadblock;
public:
    Police(float x, float y, sf::Texture* image, bool roadblock);

    void init();
    void render(sf::RenderWindow* window);
    void update(float delta, const Point* pos, const Tile* currentTile);
    void handleCollisions(Car* other, float delta);
    void handleCollisions(Tree* other, float delta);
    void setTarget(Car* target);
    void setNearest(Car* nearest);
    inline Car* getTarget() const { return target; }
    inline Car* getNearest() const { return nearest; }
    inline sf::Transformable* getSprite() { return &animSprite; }

    ~Police();
};


#endif /* MAIN_ENTITIES_CARS_POLICE_HPP_ */
