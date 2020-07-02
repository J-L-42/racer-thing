/*
 * Camera.cpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#include "Camera.hpp"

Camera::Camera(float x, float y, int viewWidth, int viewHeight, float xBound, float yBound, Car* focus) : x(x),
                y(y), viewWidth(viewWidth), viewHeight(viewHeight), xBound(xBound), yBound(yBound), focus(focus) {}

void Camera::update(float delta) {
    if (focus->getX() < x - viewWidth / 2 + xBound || focus->getX() > x + viewWidth / 2 - xBound)
        x += lengthDirX(focus->getSpeed(), focus->getRotation()) * delta;
    if (focus->getY() < y - viewHeight / 2 + yBound || focus->getY() > y + viewHeight / 2 - yBound)
        y += lengthDirY(focus->getSpeed(), focus->getRotation()) * delta;
}

void Camera::setFocus(Car* focus) {
    this->focus = focus;
}

void Camera::setView(int viewWidth, int viewHeight) {
    this->viewWidth = viewWidth;
    this->viewHeight = viewHeight;
}

void Camera::setBounds(float xBound, float yBound) {
    this->xBound = xBound;
    this->yBound = yBound;
}

Camera::~Camera() {
    focus = nullptr;
}
