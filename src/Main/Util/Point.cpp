/*
 * Point.cpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#include "Point.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(int x, int y) : x(x), y(y) {}

int Point::hashCode() const {
    long l = x * (long) 2654435761;
    return (int) l + (int) ((unsigned long) l >> 32) + y;
}

bool Point::equals(const Point& other) const {
    return (this->x == other.getX() && this->y == other.getY());
}

bool Point::operator==(const Point& other) const {
    return this->equals(other);
}
