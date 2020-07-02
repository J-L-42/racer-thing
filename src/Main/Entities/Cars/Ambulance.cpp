/*
 * Ambulance.cpp
 *
 *  Created on: 18 Apr 2017
 *      Author: james
 */

#include "Ambulance.hpp"

Ambulance::Ambulance(float x, float y, sf::Texture* image) : OnRoad(x, y, image) {
    target = nullptr;
    nearest = nullptr;
}

void Ambulance::init() {
    speed = 4;
    targetRotation = 0;

    width = image->getSize().x / NUM_FRAMES;
    height = image->getSize().y;

    anim.setSpriteSheet(*image);
    for (int i = 0; i < NUM_FRAMES; i++) {
        anim.addFrame(sf::IntRect(i * width, 0, width, height));
    }
    animSprite.setOrigin(width / 2.0, height / 2.0);
    animSprite.setAnimation(anim);
    animSprite.setFrame(1);
}

void Ambulance::render(sf::RenderWindow* window) {
    animSprite.setPosition(x + offsetX, y + offsetY);
    animSprite.setRotation(rotation);
    window->draw(animSprite);
}

void Ambulance::update(float delta, const Point* pos, const Tile* currentTile) {
    prevX = x;
    prevY = y;
    prevOffsetX = offsetX;
    prevOffsetY = offsetY;
    prevRotation = rotation;

    if (crashed) {
        animSprite.stop();
        animSprite.setFrame(1);

        if (speed > 0)
            speed -= currentTile->getFriction();
        else
            speed = 0;

        x += lengthDirX(speed, targetRotation) * delta;
        y += lengthDirY(speed, targetRotation) * delta;
    } else {
        float maxSpeed = 4;
        if (target == nullptr) {
            // We have nothing to do, so behave like a normal AI
            onRoad = true;
            animSprite.stop();
            animSprite.setFrame(1);

            speed = maxSpeed;

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

                if (prevNode != nullptr) {
                    x = prevNode->getX();
                    y = prevNode->getY();
                }

                findNode = false;
            } else {
                // If we get close to the current target, request a new one
                if (pointDistance2(x, y, (float) currentNode->getX(), (float) currentNode->getY()) <= sqr(speed * delta)) {
                    currentNode->addVisited(this);

                    findNode = true;
                }
            }
        } else {
            onRoad = false;
            if (!animSprite.isPlaying())
                animSprite.play();

            // We do not need an offset anymore since the ambulance is moving to a
            // crashed car
            if (offsetX > 0)
                offsetX -= offsetSpeed * delta;
            if (offsetX < 0)
                offsetX += offsetSpeed * delta;
            if (offsetY > 0)
                offsetY -= offsetSpeed * delta;
            if (offsetY < 0)
                offsetY += offsetSpeed * delta;

            maxSpeed = 10;
            // Reduce speed in order to avoid other cars
            if (nearest != nullptr && pointDistance2(x, y, nearest->getX(), nearest->getY()) <= 50000)
                maxSpeed = 5;

            if (pointDistance2(x, y, target->getX(), target->getY()) <= sqr(TILE_SIZE)) {
                if (speed > 0)
                    speed -= currentTile->getFriction();
                else
                    speed = 0;
            } else {
                if (speed < maxSpeed)
                    speed += 0.2;
                if (speed > maxSpeed)
                    speed -= 0.8;
                if (speed > maxSpeed - 0.2 && speed < maxSpeed + 0.2)
                    speed = maxSpeed;
            }

            // Avoid other police cars if they are too close
            if (nearest == nullptr)
                targetRotation = (int) pointDirection(x, y, target->getX(), target->getY());
            else
                targetRotation = (int) pointDirection(x, y, nearest->getX(), nearest->getY()) + 180;//90 * (random.nextInt(4) + 1);
        }

        if (rotation <= 5 && (targetRotation >= 265 && targetRotation <= 275))
            rotation = 360;
        if (rotation >= 355 && (targetRotation >= 85 && targetRotation <= 95))
            rotation = 0;
        if ((rotation >= 85 && rotation <= 95) && targetRotation >= 355)
            targetRotation = 0;
        if ((rotation >= 265 && rotation <= 275) && targetRotation <= 5)
            targetRotation = 360;

        // Ensure 0 <= rotation < 360
        if (rotation > 360)
            rotation -= 360;
        if (rotation < 0)
            rotation += 360;

        if (targetRotation > 360)
            targetRotation -= 360;
        if (targetRotation < 0)
            targetRotation += 360;

        if (speed > 0) {
            // Smoothly rotate
            if (rotation > targetRotation)
                rotation -= 4 * delta;
            if (rotation < targetRotation)
                rotation += 4 * delta;
            if (rotation > targetRotation - 4 * delta && rotation < targetRotation + 4 * delta)
                rotation = targetRotation;
        }

        if (onRoad) {
            x += lengthDirX(speed, targetRotation) * delta;
            y += lengthDirY(speed, targetRotation) * delta;
        } else {
            x += lengthDirX(speed, rotation) * delta;
            y += lengthDirY(speed, rotation) * delta;
        }
    }

    animSprite.update(delta);
}

void Ambulance::handleCollisions(Car* other, float delta) {
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
                speed = player->getSpeed() * 2;
                targetRotation = (int) player->getRotation();

                if (!crashed)
                    AssetLoader::crashSounds[randomInt(&random, NUM_CRASH_SOUNDS)].play();
                crashed = true;
            }
        }
    }

    if (isType<Ambulance, Car>(other)) {
        Ambulance* amb = (Ambulance*) other;
        if (near && intersects(getSprite(), getWidth(), getHeight(),
                amb->getSprite(), amb->getWidth(), amb->getHeight())) {
            if (amb->crashed) {
                x = prevX;
                y = prevY;
                offsetX = prevOffsetX;
                offsetY = prevOffsetY;
                rotation = prevRotation;
                speed = 0;

                if (!crashed)
                    AssetLoader::crashSounds[randomInt(&random, NUM_CRASH_SOUNDS)].play();
                crashed = true;
            } else {
                nearest = amb;
            }
        }
    }
}

void Ambulance::handleCollisions(Tree* other, float delta) {
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

void Ambulance::setTarget(Car* target) {
    this->target = target;
}

void Ambulance::setNearest(Car* nearest) {
    this->nearest = nearest;
}

Ambulance::~Ambulance() {
    target = nullptr;
    nearest = nullptr;
}
