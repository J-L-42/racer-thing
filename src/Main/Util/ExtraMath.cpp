/*
 * ExtraMath.cpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#include "ExtraMath.hpp"

float pointDirection(float x1, float y1, float x2, float y2) {
    double dx = x2 - x1;
    double dy = -(y2 - y1);

    double inRads = atan2(dy, dx);

    if (inRads < 0)
        inRads = std::abs(inRads);
    else
        inRads = 2 * PI - inRads;

    double inDegs = toDegrees(inRads);

    if (inDegs >= 360)
        inDegs -= 360;
    if (inDegs < 0)
        inDegs += 360;

    return (float) inDegs;
}

float pointDistance2(float x1, float y1, float x2, float y2) {
    return sqr(x2 - x1) + sqr(y2 - y1);
}

float lengthDirX(float length, float dir) {
    return (float) cos(toRadians(dir)) * length;
}

float lengthDirY(float length, float dir) {
    return (float) sin(toRadians(dir)) * length;
}

int randomInt(std::mt19937_64* device, int max) {
    int n = (int) floor(max * (float) ((float) (*device)() / (float) device->max()));
    return n >= max - 1 ? max - 1 : n;
}
