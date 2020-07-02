/*
 * Building.hpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_BUILDING_HPP_
#define MAIN_ENTITIES_BUILDING_HPP_


#include "../Util/Constants.hpp"
#include "../Util/Point.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

/* Represents buildings on the map */
class Building {
public:
    /* Type of building - skyscrapers/houses etc. */
    enum Type {
        SKY, HSE
    };
private:
    /* Position of building */
    int x, y;
    /* Size of building */
    int width, height;

    sf::Sprite sprite;
    sf::Texture* image;
    Type type;
public:
    Building(int x, int y, Type type);

    void render(sf::RenderWindow* window);
    void setImage(sf::Texture* image);
    inline int getX() const { return x; }
    inline int getY() const { return y; }
    Point* getPos() const { return new Point(x / TILE_SIZE, y / TILE_SIZE); }
    inline Type getType() const { return type; }
    inline sf::Transformable* getSprite() { return &sprite; }

    ~Building();
};


#endif /* MAIN_ENTITIES_BUILDING_HPP_ */
