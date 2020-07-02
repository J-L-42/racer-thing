/*
 * Player.cpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#include "Player.hpp"

Player::Player(float x, float y, sf::Texture* image) : Car(x, y, image) {
    origX = this->x;
    origY = this->y;
    origRotation = this->rotation;

    engine = &AssetLoader::engineSound;
    skid = &AssetLoader::skidSound;

    skid->setVolume(70);
}

void Player::update(float delta, const Point* pos, const Tile* currentTile) {
    prevX = x;
    prevY = y;
    prevRotation = rotation;

    float friction = currentTile->getFriction();

    acceleration = baseAcceleration * (float) (std::abs((float) maxSpeed - speed) / (float) maxSpeed);

    if (throttle) {
        // Burn some rubber when initially accelerating
        if (speed < (maxSpeed / 4)) {
            if (skid->getStatus() == sf::Sound::Stopped && !handbrake)
                skid->play();
        } else {
            if (!handbrake && !left && !right)
                skid->stop();
        }

        if (speed < maxSpeed)
            speed += acceleration;
        else
            speed = maxSpeed;
    } else if (brake) {
        if (speed > -(maxSpeed / 4)) {
            if (skid->getStatus() == sf::Sound::Stopped && !handbrake)
                skid->play();
        } else {
            if (!handbrake && !left && !right)
                skid->stop();
        }

        if (speed > -(maxSpeed / 3))
            speed -= acceleration;
        else
            speed = -(maxSpeed / 3);
    } else {
        if (speed > 0)
            speed -= friction;
        if (speed < 0)
            speed += friction;

        // Ensure car does not vibrate if speed is close to 0
        if (speed >= -friction && speed <= friction)
            speed = 0;
    }

    if (handbrake) {
        if (speed > 0)
            speed -= baseAcceleration * 4;
        if (speed < 0)
            speed += baseAcceleration * 2;

        if (speed >= -baseAcceleration * 2 && speed <= baseAcceleration * 2)
            speed = 0;

        if (throttle)
            handling = baseHandling;
    } else {
        // Handling is determined by speed (unless handbrake is on)
        if (speed == 0) {
            handling = 0;
            maxTurn = 0;
        } else {
            handling = baseHandling * (float) (std::abs(speed * 2) / (float) maxSpeed);
            maxTurn = baseMaxTurn;
        }
    }

    if (left) {
        if (speed != 0 || handbrake) {
            if (turn > -maxTurn)
                turn -= handling;
            else
                turn = -maxTurn;
        } else {
            if (turn < 0) {
                turn += baseHandling;
            } else {
                turn = 0;
                if (!throttle && !brake)
                    skid->stop();
            }

        }

        if (!handbrake) {
            if (speed > minSpeed)
                speed -= baseAcceleration;
            if (speed < -minSpeed)
                speed += baseAcceleration;
        }

        // Burn rubber round the bends
        if ((speed != 0 || handbrake) && turn <= -(float) maxTurn * (11.0 / 12.0) && skid->getStatus() == sf::Sound::Stopped)
            skid->play();
    } else if (right) {
        if (speed != 0 || handbrake) {
            if (turn < maxTurn)
                turn += handling;
            else
                turn = maxTurn;
        } else {
            if (turn > 0) {
                turn -= baseHandling;
            } else {
                turn = 0;
                if (!throttle && !brake)
                    skid->stop();
            }
        }

        if (!handbrake) {
            if (speed > minSpeed)
                speed -= baseAcceleration;
            if (speed < -minSpeed)
                speed += baseAcceleration;
        }

        if ((speed != 0 || handbrake) && turn >= (float) maxTurn * (11.0 / 12.0) && skid->getStatus() == sf::Sound::Stopped)
            skid->play();
    } else {
        if (turn > 0)
            turn -= baseHandling;
        else
            turn += baseHandling;

        if (turn >= -baseHandling && turn <= baseHandling)
            turn = 0;

        if (!handbrake && !throttle && !brake)
            skid->stop();
    }

    rotation += turn * delta;
    x += lengthDirX(speed, rotation) * delta;
    y += lengthDirY(speed, rotation) * delta;

    if (speed > 0) {
        //float x = speed;
        //if ((x > 0 && x <= (float) maxSpeed / 6f) || (x > (float) maxSpeed / 3f && x <= (float) maxSpeed / 2f) || (x > (2f * (float) maxSpeed) / 3f && x <= (5f * (float) maxSpeed) / 6f))
        //	enginePitch = (float) sin(toRadians(90f * x)) / 2.0 + 0.7f;
        //else if ((x > (float) maxSpeed / 6f && x <= (float) maxSpeed / 3f) || (x > (float) maxSpeed / 2f && x <= (2f * (float) maxSpeed) / 3f) || (x > (5f * (float) maxSpeed) / 6f && x <= (float) maxSpeed))
        //	enginePitch = (float) cos(toRadians(90f * x)) / 2.0 + 0.7f;
        enginePitch = (float) (std::abs(speed * (5.0 / 6.0)) / (float) maxSpeed) + 0.2;
    } else {
        enginePitch = (float) (std::abs(speed * (5.0 / 6.0)) / (float) maxSpeed) + 0.2;
    }

    // If trying to accelerate but the car is not moving, create a revving effect
    if (throttle && speed < (maxSpeed / 4))
        enginePitch = 1;
    if (brake && speed > -(maxSpeed / 4))
        enginePitch = 1;

    engine->setPitch(enginePitch);
    engine->setVolume(enginePitch * 15.0);
    if (engineTimer > 0) {
        engineTimer -= 1.0 * delta;
    } else {
        engine->play();
        engineTimer = 1;
    }

    if (skid->getStatus() == sf::Sound::Playing) {
        skidMarks.add(std::make_shared<SkidMark>(x - lengthDirX(width / 1.5, rotation), y - lengthDirY(width / 1.5, rotation), rotation));
        skidMarks.add(std::make_shared<SkidMark>(x - lengthDirX(2.0, rotation), y - lengthDirY(2.0, rotation), rotation));
    }

    for (int i = 0; i < skidMarks.size(); i++) {
        SkidMark* s = skidMarks[i].get();
        s->update(delta);

        if (s->shouldClean())
            skidMarks.remove(i);
    }
}

void Player::handleCollisions(Car* other, float delta) {
    // We only want to begin checking collisions if cars get close to each other -
    // pointDistance is much faster than intersects
    bool near = (pointDistance2(x, y, other->getX(), other->getY()) <= sqr(TILE_SIZE / 2));

    if (near && intersects(getSprite(), getWidth(), getHeight(),
            other->getSprite(), other->getWidth(), other->getHeight())) {
        if (std::abs(speed) > 2) {
            x = prevX;
            y = prevY;
            speed /= 4;
        }

        rotation = prevRotation;
    }
}

void Player::handleCollisions(Tree* other, float delta) {
    bool near = (pointDistance2(x, y, other->getX(), other->getY()) <= sqr(TILE_SIZE / 2));

    if (near && intersects(getSprite(), getWidth(), getHeight(),
            other->getSprite(), other->getWidth(), other->getHeight(),
            0, 0, other->getOffsetX(), other->getOffsetY())) {
        x = prevX;
        y = prevY;
        x -= lengthDirX(speed, rotation) * delta;
        y -= lengthDirY(speed, rotation) * delta;
        rotation = prevRotation;

        //AssetLoader::crashSounds[randomInt(&random, NUM_CRASH_SOUNDS)].play();
    }
}

void Player::setInput(bool throttle, bool brake, bool handbrake, bool left, bool right) {
    this->throttle = throttle;
    this->brake = brake;
    this->handbrake = handbrake;
    this->left = left;
    this->right = right;
}

void Player::reset() {
    x = origX;
    y = origY;
    rotation = origRotation;
}

Player::~Player() {
    skidMarks.clear();
}
