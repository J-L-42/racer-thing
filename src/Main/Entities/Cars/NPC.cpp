/*
 * NPC.cpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#include "NPC.hpp"

NPC::NPC(float x, float y, sf::Texture* image, int id) : OnRoad(x, y, image), id(id) {
    offsetX = 0;
    offsetY = 0;
    prevOffsetX = 0;
    prevOffsetY = 0;
}

void NPC::init() {
    Car::init();

    speed = id + 2;
    targetRotation = 0;
    sprite.setOrigin(width / 2.0, height / 2.0);

    currentNode = nullptr;
    prevNode = nullptr;
}

void NPC::render(sf::RenderWindow* window) {
    sprite.setPosition(x + offsetX, y + offsetY);
    sprite.setRotation(rotation);
    window->draw(sprite);
}

void NPC::update(float delta, const Point* pos, const Tile* currentTile) {
    prevX = x;
    prevY = y;
    prevOffsetX = offsetX;
    prevOffsetY = offsetY;
    prevRotation = rotation;

    if (crashed) {
        if (speed > 0)
            speed -= currentTile->getFriction();
        else
            speed = 0;
    } else {
        // Ensure that the car always follows a lane by changing offsets
        findOffsets(delta);

        if (findNode) {
            prevNode = currentNode;
            // We have gained a new set of valid nodes, so pick one
            currentNode = nodes[randomInt(&random, nodes.size())];

            // Ensure integer rotations to prevent cumulative rounding errors
            Point pL(pos->getX() - 1, pos->getY());
            Point pR(pos->getX() + 1, pos->getY());
            Point pU(pos->getX(), pos->getY() - 1);
            Point pD(pos->getX(), pos->getY() + 1);

            if (currentNode->getPos()->equals(pL))
                targetRotation = 180;
            if (currentNode->getPos()->equals(pR)) {
                if (targetRotation >= 355)
                    targetRotation = 360;
                else
                    targetRotation = 0;
            }
            if (currentNode->getPos()->equals(pU))
                targetRotation = 270;
            if (currentNode->getPos()->equals(pD))
                targetRotation = 90;

            // Ensure 90 turns only by fixing rotation to be either 0 or 360 as necessary
            if (rotation <= 5 && (targetRotation >= 265 && targetRotation <= 275))
                rotation = 360;
            if (rotation >= 355 && (targetRotation >= 85 && targetRotation <= 95))
                rotation = 0;
            if ((rotation >= 85 && rotation <= 95) && targetRotation >= 355)
                targetRotation = 0;
            if ((rotation >= 265 && rotation <= 275) && targetRotation <= 5)
                targetRotation = 360;

            // Make sure positions are exact to avoid rounding errors
            if (prevNode != nullptr) {
                x = prevNode->getX();
                y = prevNode->getY();
            }

            findNode = false;
        } else {
            // If we get close to the current target, request a new one
            if (pointDistance2(x, y, (float) currentNode->getX(), (float) currentNode->getY()) <= sqr(speed)) {
                currentNode->addVisited(this);

                findNode = true;
            }
        }

        // Ensure 0 <= rotation < 360
        if (rotation > 360)
            rotation -= 360;
        if (rotation < 0)
            rotation += 360;

        if (targetRotation > 360)
            targetRotation -= 360;
        if (targetRotation < 0)
            targetRotation += 360;

        // Smoothly rotate round corners
        if (rotation > targetRotation)
            rotation -= 4 * delta;
        if (rotation < targetRotation)
            rotation += 4 * delta;
        if (rotation > targetRotation - 4 * delta && rotation < targetRotation + 4 * delta)
            rotation = targetRotation;
    }

    x += lengthDirX(speed, targetRotation) * delta;
    y += lengthDirY(speed, targetRotation) * delta;
}

void NPC::handleCollisions(Car* other, float delta) {
    bool near = (pointDistance2(x, y, other->getX(), other->getY()) <= sqr(TILE_SIZE / 2));

    if (isType<Player, Car>(other)) {
        Player* player = (Player*) other;
        if (near && intersects(getSprite(), getWidth(), getHeight(),
                player->getSprite(), player->getWidth(), player->getHeight())) {
            x = prevX;
            y = prevY;
            offsetX = prevOffsetX;
            offsetY = prevOffsetY;
            rotation = prevRotation;
            speed = 0;

            if (std::abs(player->getSpeed() > 2)) {
                speed = player->getSpeed() * 2 - (id + 2) / 2;
                targetRotation = (int) player->getRotation();

                if (!crashed)
                    AssetLoader::crashSounds[randomInt(&random, NUM_CRASH_SOUNDS)].play();
                crashed = true;
            }
        }
    }

    if (isType<NPC, Car>(other)) {
        NPC* npc = (NPC*) other;
        if (near) {
            if (intersects(getSprite(), getWidth(), getHeight(),
                    npc->getSprite(), npc->getWidth(), npc->getHeight())) {
                if (crashed) {
                    x = prevX;
                    y = prevY;
                    offsetX = prevOffsetX;
                    offsetY = prevOffsetY;
                    rotation = prevRotation;
                    speed = 0;
                    offsetSpeed = 0;
                } else {
                    if (npc->crashed) {
                        speed = 0;
                        offsetSpeed = 0;

                        if (!crashed)
                            AssetLoader::crashSounds[randomInt(&random, NUM_CRASH_SOUNDS)].play();
                        crashed = true;
                    } else {
                        if (npc->getTargetRotation() == targetRotation) {
                            if (speed > npc->getSpeed()) {
                                x = prevX;
                                y = prevY;
                                offsetX = prevOffsetX;
                                offsetY = prevOffsetY;
                                rotation = prevRotation;
                                speed = 0;
                                offsetSpeed = 0;
                            }
                        } else {
                            //if (!npc->collision) {
                            //	//x = prevX;
                            //	//y = prevY;
                            //	speed = 0;
                            //	offsetSpeed = 0;
                            //	collision = true;
                            //}
                        }
                    }
                }
            } else {
                if (!crashed) {
                    speed = id + 2;
                    offsetSpeed = 8;

                    collision = false;
                }
            }
        }
    }

    if (isType<Police, Car>(other)) {
        Police* pol = (Police*) other;
        if (near && intersects(getSprite(), getWidth(), getHeight(),
                pol->getSprite(), pol->getWidth(), pol->getHeight())) {
            if (crashed) {
                x = prevX;
                y = prevY;
                offsetX = prevOffsetX;
                offsetY = prevOffsetY;
                rotation = prevRotation;
                speed = 0;
                offsetSpeed = 0;
            } else {
                if (pol->isCrashed()) {
                    speed = 0;
                    offsetSpeed = 0;

                    if (!crashed)
                        AssetLoader::crashSounds[randomInt(&random, NUM_CRASH_SOUNDS)].play();
                    crashed = true;
                }
            }
        }
    }
}

void NPC::handleCollisions(Tree* other, float delta) {
    bool near = (pointDistance2(x, y, other->getX(), other->getY()) <= sqr(TILE_SIZE / 2));

    if (near && intersects(getSprite(), getWidth(), getHeight(),
            other->getSprite(), other->getWidth(), other->getHeight())) {
        x = prevX;
        y = prevY;
        speed = 0;
        rotation = prevRotation;

        AssetLoader::crashSounds[randomInt(&random, NUM_CRASH_SOUNDS)].play();
    }
}

NPC::~NPC() {

}
