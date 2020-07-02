/*
 * Tile.hpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#ifndef MAIN_TILES_TILE_HPP_
#define MAIN_TILES_TILE_HPP_


#include "../Util/Constants.hpp"
#include "../Util/Point.hpp"
#include "../Util/ArrayList.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

class Car;

/* Tile making up the game map */
class Tile {
public:
    /* Type of tile - roads/pavement etc. */
    enum Type {
        EW, NE, NEWS, NS, NW, PLAZA, SE, SW, TE, TN, TS, TW
    };
private:
    /* Position of tile */
    int x, y;
    /* Size of tile */
    int width, height;
    /* Which sides are blocked off due to lack of road */
    bool wallLeft = false, wallRight = false, wallUp = false, wallDown = false;

    sf::Sprite sprite;
    sf::Texture* image;
    float friction = 0.2;
    Type type;

    /* List of cars that have been here */
    ArrayList<Car*> visited;

    void setWalls();
public:
    Tile(int x, int y, Type type);

    void render(sf::RenderWindow* window);
    void setImage(sf::Texture* image);
    void addVisited(Car* npc);
    void removeVisited(Car* npc);
    inline ArrayList<Car*>* getVisited() { return &visited; }
    inline int getX() const { return x; }
    inline int getY() const { return y; }
    Point* getPos() const { return new Point(x / TILE_SIZE, y / TILE_SIZE); }
    inline Type getType() const { return type; }
    inline float getFriction() const { return friction; }
    inline bool isWallLeft() const { return wallLeft; }
    inline bool isWallRight() const { return wallRight; }
    inline bool isWallUp() const { return wallUp; }
    inline bool isWallDown() const { return wallDown; }
    bool hasTurn() const { return !(type == EW || type == NS || type == PLAZA); }
    bool hasRoad() const { return !(type == PLAZA); }
    bool isEast() const { return (type == EW || type == NE || type == NEWS
                            || type == SE || type == TE || type == TN
                            || type == TS); }
    bool isWest() const { return (type == EW || type == NEWS || type == NW
                            || type == SW || type == TN || type == TS
                            || type == TW); }
    bool isNorth() const { return (type == NE || type == NEWS || type == NS
                            || type == NW || type == TE || type == TN
                            || type == TW); }
    bool isSouth() const { return (type == NEWS || type == NS || type == SE
                            || type == SW || type == TE || type == TS
                            || type == TW); }

    ~Tile();
};


#endif /* MAIN_TILES_TILE_HPP_ */
