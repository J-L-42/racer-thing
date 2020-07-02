/*
 * NPC.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_CARS_NPC_HPP_
#define MAIN_ENTITIES_CARS_NPC_HPP_


#include "OnRoad.hpp"

class NPC : public OnRoad {
private:
    int id;
public:
    NPC(float x, float y, sf::Texture* image, int id);

    void init();
    void render(sf::RenderWindow* window);
    void update(float delta, const Point* pos, const Tile* currentTile);
    void handleCollisions(Car* other, float delta);
    void handleCollisions(Tree* other, float delta);
    inline int getID() const { return id; }

    ~NPC();
};


#endif /* MAIN_ENTITIES_CARS_NPC_HPP_ */
