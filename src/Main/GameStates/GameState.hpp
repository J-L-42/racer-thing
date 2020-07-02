/*
 * GameState.hpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#ifndef MAIN_GAMESTATES_GAMESTATE_HPP_
#define MAIN_GAMESTATES_GAMESTATE_HPP_


#include "../Assets.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

class GameState {
public:
    virtual void init() = 0;
    virtual void render(sf::RenderWindow* window, float delta) = 0;
    virtual void update(sf::RenderWindow* window, float delta) = 0;
    virtual void enter() = 0;
    virtual void leave() = 0;

    virtual ~GameState();
};


#endif /* MAIN_GAMESTATES_GAMESTATE_HPP_ */
