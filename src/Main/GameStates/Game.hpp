/*
 * Game.hpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#ifndef MAIN_GAMESTATES_GAME_HPP_
#define MAIN_GAMESTATES_GAME_HPP_


#define DIR_LEFT 0
#define DIR_RIGHT 1
#define DIR_UP 2
#define DIR_DOWN 3

#include <unordered_map>
#include <memory>

#include "../Util/Constants.hpp"
#include "GameState.hpp"
#include "../Util/Instanceof.hpp"
#include "../Util/Point.hpp"
#include "../Util/ExtraMath.hpp"
#include "../Util/ArrayList.hpp"
#include "../Entities/Camera.hpp"
#include "../Entities/Cars/Car.hpp"
#include "../Entities/Cars/OnRoad.hpp"
#include "../Entities/Cars/Player.hpp"
#include "../Entities/Cars/NPC.hpp"
#include "../Entities/Cars/Police.hpp"
#include "../Entities/Cars/Ambulance.hpp"
#include "../Entities/Cars/SkidMark.hpp"
#include "../Tiles/Tile.hpp"
#include "../Entities/Tree.hpp"
#include "../Entities/Building.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

#ifndef SFML_AUDIO
#define SFML_AUDIO

#include <SFML/Audio.hpp>

#endif

using tilemap_t = std::unordered_map<Point, std::shared_ptr<Tile>, PointHash>;
using tilemapiterator_t = std::unordered_map<Point, std::shared_ptr<Tile>, PointHash>::iterator;

class Game : public GameState {
private:
    /* Size of map in tiles */
    int width = 1, height = 1;
    /* Tiles generated in each direction */
    int genLeft = 0, genRight = 0, genUp = 0, genDown = 0;
    /* Hash map for tiles */
    tilemap_t tiles;

    Player player;
    bool throttle = false, brake = false, handbrake = false, left = false, right = false;

    int keys[5] { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space };

    sf::View view;
    Camera camera;

    bool pause = false;

    std::mt19937_64 generator;
    int generateChance = 3;

    ArrayList<std::shared_ptr<Car>> npcs;
    ArrayList<Car*> crashed;
    ArrayList<std::shared_ptr<Tree>> trees;
    ArrayList<std::shared_ptr<Building>> buildings;

    sf::Clock fpsClock;
    sf::Text fpsText;
    float fpsCounter = 60;

    void addToMap(bool isLeft, bool isRight, bool isUp, bool isDown);
    void generateMap();
    bool addTile(int x, int y);
    ArrayList<Tile::Type> getValidTypes(Tile* left, Tile* right, Tile* up, Tile* down);
public:
    Game();

    void init();
    void render(sf::RenderWindow* window, float delta);
    void update(sf::RenderWindow* window, float delta);
    void enter();
    void leave();

    ~Game();
};


#endif /* MAIN_GAMESTATES_GAME_HPP_ */
