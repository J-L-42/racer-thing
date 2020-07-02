/*
 * Tree.hpp
 *
 *  Created on: 26 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_TREE_HPP_
#define MAIN_ENTITIES_TREE_HPP_


#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

class Tree {
private:
    float x, y;
    int width = 48, height = 48, imageWidth, imageHeight;

    sf::Sprite sprite;
    sf::Texture* image;
public:
    Tree(float x, float y, sf::Texture* image);

    void init();
    void render(sf::RenderWindow* window);
    void update(float delta);
    inline float getX() const { return x; }
    inline float getY() const { return y; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline sf::Transformable* getSprite() { return &sprite; }
    inline int getOffsetX() const { return imageWidth / 2 - width / 2; }
    inline int getOffsetY() const { return imageHeight / 2 - height / 2; }

    ~Tree();
};


#endif /* MAIN_ENTITIES_TREE_HPP_ */
