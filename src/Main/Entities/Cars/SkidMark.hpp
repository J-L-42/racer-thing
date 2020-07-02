/*
 * SkidMark.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_CARS_SKIDMARK_HPP_
#define MAIN_ENTITIES_CARS_SKIDMARK_HPP_


#include "../../Assets.hpp"

class SkidMark {
private:
    float x, y;
    int width, height;
    float rotation;

    sf::Sprite sprite;
    sf::Texture* image;

    float life = 3600;
public:
    SkidMark(float x, float y, float rotation);

    void render(sf::RenderWindow* window);
    void update(float delta);
    inline float getX() const { return x; }
    inline float getY() const { return y; }
    inline bool shouldClean() const { return (life <= 0); }

    ~SkidMark();
};


#endif /* MAIN_ENTITIES_CARS_SKIDMARK_HPP_ */
