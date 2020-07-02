/*
 * Police.cpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#include "Police.hpp"

Police::Police(float x, float y, sf::Texture* image, bool roadblock) : Car(x, y, image) {
    this->roadblock = roadblock;

    targetRotation = 0;
    target = nullptr;
    nearest = nullptr;
}

void Police::init() {
    speed = 10;
    targetRotation = 0;

    width = image->getSize().x / NUM_FRAMES;
    height = image->getSize().y;

    anim.setSpriteSheet(*image);
    for (int i = 0; i < NUM_FRAMES; i++) {
        anim.addFrame(sf::IntRect(i * width, 0, width, height));
    }
    animSprite.setOrigin((float) width * (5.0 / 6.0), (float) height / 2.0);
    animSprite.setAnimation(anim);
    animSprite.play();
}

void Police::render(sf::RenderWindow* window) {
    animSprite.setPosition(x, y);
    animSprite.setRotation(rotation);
    window->draw(animSprite);
}

void Police::update(float delta, const Point* pos, const Tile* currentTile) {
    prevX = x;
    prevY = y;
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
        if (roadblock) {
            // Car should be stationary if in a roadblock
            speed = 0;
            rotation = 0;
        } else {
            // Set the maximum speed initially to the player's if they are going fast enough
            float maxSpeed = target->getSpeed() > 10 ? std::abs(target->getSpeed()) : 10;
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

            x += lengthDirX(speed, rotation) * delta;
            y += lengthDirY(speed, rotation) * delta;
        }
    }

    animSprite.update(delta);
}

void Police::handleCollisions(Car* other, float delta) {
    bool near = (pointDistance2(x, y, other->getX(), other->getY()) <= sqr(TILE_SIZE / 2));

    if (isType<Player, Car>(other)) {
        Player* player = (Player*) other;
        if (near && intersects(getSprite(), getWidth(), getHeight(),
                player->getSprite(), player->getWidth(), player->getHeight())) {
            x = prevX;
            y = prevY;
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

    if (isType<Police, Car>(other)) {
        Police* pol = (Police*) other;
        if (near && intersects(getSprite(), getWidth(), getHeight(),
                pol->getSprite(), pol->getWidth(), pol->getHeight())) {
            if (pol->crashed) {
                x = prevX;
                y = prevY;
                rotation = prevRotation;
                speed = 0;

                if (std::abs(speed) > 5) {
                    if (!crashed)
                        AssetLoader::crashSounds[randomInt(&random, NUM_CRASH_SOUNDS)].play();
                    crashed = true;
                }
            } else {
                nearest = pol;
            }
        }
    }
}

void Police::handleCollisions(Tree* other, float delta) {
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

void Police::setTarget(Car* target) {
    this->target = target;
}

void Police::setNearest(Car* nearest) {
    this->nearest = nearest;
}

Police::~Police() {
    target = nullptr;
    nearest = nullptr;
}
