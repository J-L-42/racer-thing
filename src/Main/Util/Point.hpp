/*
 * Point.hpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#ifndef MAIN_UTIL_POINT_HPP_
#define MAIN_UTIL_POINT_HPP_


#include <cstdlib>

/* Simple class representing a point, hashes to the same value if 2 are equal */
class Point {
private:
    int x, y;
public:
    Point();
    Point(int x, int y);

    inline int getX() const { return x; }
    inline int getY() const { return y; }
    int hashCode() const;
    bool equals(const Point& other) const;
    bool operator==(const Point& other) const;
};

struct PointHash {
    std::size_t operator()(const Point& p) const {
        return (std::size_t) p.hashCode();
    }
};


#endif /* MAIN_UTIL_POINT_HPP_ */
