/*
 * ExtraMath.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_UTIL_EXTRAMATH_HPP_
#define MAIN_UTIL_EXTRAMATH_HPP_


#define PI 3.14159265

#include <cmath>
#include <random>

/* Converts radians to degrees */
inline float toDegrees(float radians) { return radians * 180 / PI; }
/* Converts degrees to radians */
inline float toRadians(float degrees) { return degrees * PI / 180; }
/* Returns x^2 */
inline float sqr(float x) { return (float) pow(x, 2); }

/* Returns the angle between the 2 points */
float pointDirection(float x1, float y1, float x2, float y2);

/* Returns the square of the distance between the 2 points */
float pointDistance2(float x1, float y1, float x2, float y2);

/* Returns the x component of the vector of length {length} pointing in direction {dir} */
float lengthDirX(float length, float dir);

/* Returns the y component of the vector of length {length} pointing in direction {dir} */
float lengthDirY(float length, float dir);

/* Returns a random positive integer smaller than max */
int randomInt(std::mt19937_64* device, int max);


#endif /* MAIN_UTIL_EXTRAMATH_HPP_ */
