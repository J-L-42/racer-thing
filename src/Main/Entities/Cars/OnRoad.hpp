/*
 * OnRoad.hpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_CARS_ONROAD_HPP_
#define MAIN_ENTITIES_CARS_ONROAD_HPP_


#include "../../Util/ArrayList.hpp"
#include "Car.hpp"
#include "Player.hpp"
#include "Police.hpp"

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

/* Parent for cars that drive on roads - should be treated as abstract */
class OnRoad : public Car {
protected:
    /* The offset to the car's position to ensure the car moves along roads */
    int offsetX, offsetY, prevOffsetX, prevOffsetY;
    /* Speed to move to a new offset */
    int offsetSpeed = 8;

    /* The tile to move to next */
    Tile* currentNode;
    Tile* prevNode;
    /* The final direction to rotate to */
    int targetRotation;

    /* List of nodes close to this npc */
    ArrayList<Tile*> nodes;

    /* Whether to request a new tile from the hash map */
    bool findNode = false;

    /* Whether this car should follow roads */
    bool onRoad = true;

    /* Change the offset to move along roads */
    void findOffsets(float delta);
public:
    OnRoad(float x, float y, sf::Texture* image);

    inline int getTargetRotation() { return targetRotation; }
    void setCurrentNode(Tile* node);
    void setNodes(ArrayList<Tile*> nodes);
    inline bool shouldFindNode() { return findNode; }
    inline bool isOnRoad() { return onRoad; }

    virtual ~OnRoad();
};


#endif /* MAIN_ENTITIES_CARS_ONROAD_HPP_ */
