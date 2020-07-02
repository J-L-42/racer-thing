#ifndef MAIN_UTIL_COLLISIONS_TRANSFORMEDBOUNDINGBOX_HPP_
#define MAIN_UTIL_COLLISIONS_TRANSFORMEDBOUNDINGBOX_HPP_


#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

struct TransformedBoundingBox {
    sf::Vector2f points[4];

    void initPoints(const sf::Transformable* object, int offsetX, int offsetY, int width, int height);
    void project(const sf::Vector2f& axis, float& min, float& max);
};

bool intersects(const sf::Transformable* self, int selfWidth, int selfHeight, const sf::Transformable* other,
        int otherWidth, int otherHeight, int selfOffsetX = 0, int selfOffsetY = 0, int otherOffsetX = 0, int otherOffsetY = 0);


#endif /* MAIN_UTIL_COLLISIONS_TRANSFORMEDBOUNDINGBOX_HPP_ */
