/*
 * Ambulance.hpp
 *
 *  Created on: 18 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_CARS_AMBULANCE_HPP_
#define MAIN_ENTITIES_CARS_AMBULANCE_HPP_


#define NUM_FRAMES 3

#include "../../Util/Animations/AnimatedSprite.hpp"
#include "../../Util/Animations/Animation.hpp"
#include "OnRoad.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

#ifndef SFML_AUDIO
#define SFML_AUDIO

#include <SFML/Audio.hpp>

#endif

class Ambulance : public OnRoad {
private:
    Animation anim;
    AnimatedSprite animSprite;

    Car* target;
    Car* nearest;
public:
    Ambulance(float x, float y, sf::Texture* image);

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

    ~Ambulance();
};


#endif /* MAIN_ENTITIES_CARS_AMBULANCE_HPP_ */
