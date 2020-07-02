/*
 * Player.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_CARS_PLAYER_HPP_
#define MAIN_ENTITIES_CARS_PLAYER_HPP_


#include <memory>

#include "../../Util/ArrayList.hpp"
#include "Car.hpp"
#include "SkidMark.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

#ifndef SFML_AUDIO
#define SFML_AUDIO

#include <SFML/Audio.hpp>

#endif

class Player : public Car {
private:
    /* Initial values for reseting */
    float origX, origY, origRotation;

    /* Speed upper/lower bounds (upper for top speed, lower for min handling speed) */
    int maxSpeed = 30, minSpeed = 4;
    float baseAcceleration = 0.2, acceleration = 0;

    /* Max amount in degrees the car can turn */
    int baseMaxTurn = 4, maxTurn = 4;
    float baseHandling = 0.4, handling = 0.4;
    float turn = 0;

    /* Which actions should be performed */
    bool throttle = false, brake = false, handbrake = false,
            left = false, right = false;

    float enginePitch = 1;
    sf::Sound* engine;
    float engineTimer = 1;

    sf::Sound* skid;
    ArrayList<std::shared_ptr<SkidMark>> skidMarks;
public:
    Player(float x, float y, sf::Texture* image);

    void update(float delta, const Point* pos, const Tile* currentTile);
    void handleCollisions(Car* other, float delta);
    void handleCollisions(Tree* other, float delta);
    void setInput(bool throttle, bool brake, bool handbrake, bool left, bool right);
    inline ArrayList<std::shared_ptr<SkidMark>>* getSkidMarks() { return &skidMarks; }
    void reset();

    ~Player();
};


#endif /* MAIN_ENTITIES_CARS_PLAYER_HPP_ */
