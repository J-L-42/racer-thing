/*
 * Game.cpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#include "Game.hpp"

Game::Game() : player(0, 0, &AssetLoader::playerImage),
    camera(Camera(0, 0, BASE_WIDTH, BASE_HEIGHT, BASE_WIDTH / 2.4, BASE_HEIGHT / 2.4, &player)) {}

void Game::init() {
    view.setCenter(camera.getX(), camera.getY());
    view.setSize(camera.getViewWidth(), camera.getViewHeight());

    player.init();

    fpsText.setFont(AssetLoader::main);
}

void Game::render(sf::RenderWindow* window, float delta) {
    view.setCenter(camera.getX(), camera.getY());
    view.setSize(camera.getViewWidth(), camera.getViewHeight());
    window->setView(view);

    for (std::pair<Point, std::shared_ptr<Tile>> pair : tiles) {
        Tile* t = pair.second.get();
        if (t->getX() < camera.getX() + camera.getViewWidth() / 2 + TILE_SIZE && t->getX() > camera.getX() - camera.getViewWidth() / 2 - TILE_SIZE
                && t->getY() < camera.getY() + camera.getViewHeight() / 2 + TILE_SIZE && t->getY() > camera.getY() - camera.getViewHeight() / 2 - TILE_SIZE)
            t->render(window);
    }

    ArrayList<std::shared_ptr<SkidMark>>* skidMarks = player.getSkidMarks();
    for (int i = 0; i < skidMarks->size(); i++) {
        std::shared_ptr<SkidMark> skid_shared = skidMarks->get(i);
        SkidMark* s = skid_shared.get();
        if (s->getX() < camera.getX() + camera.getViewWidth() / 2 + TILE_SIZE && s->getX() > camera.getX() - camera.getViewWidth() / 2 - TILE_SIZE
                && s->getY() < camera.getY() + camera.getViewHeight() / 2 + TILE_SIZE && s->getY() > camera.getY() - camera.getViewHeight() / 2 - TILE_SIZE)
            s->render(window);
    }

    for (int i = 0; i < npcs.size(); i++) {
        std::shared_ptr<Car> car_shared = npcs[i];
        Car* c = car_shared.get();
        if (c->getX() < camera.getX() + camera.getViewWidth() / 2 + TILE_SIZE && c->getX() > camera.getX() - camera.getViewWidth() / 2 - TILE_SIZE
                && c->getY() < camera.getY() + camera.getViewHeight() / 2 + TILE_SIZE && c->getY() > camera.getY() - camera.getViewHeight() / 2 - TILE_SIZE)
            c->render(window);
    }

    player.render(window);

    for (int i = 0; i < trees.size(); i++) {
        std::shared_ptr<Tree> tree_shared = trees[i];
        Tree* t = tree_shared.get();
        if (t->getX() < camera.getX() + camera.getViewWidth() / 2 + TILE_SIZE && t->getX() > camera.getX() - camera.getViewWidth() / 2 - TILE_SIZE
                && t->getY() < camera.getY() + camera.getViewHeight() / 2 + TILE_SIZE && t->getY() > camera.getY() - camera.getViewHeight() / 2 - TILE_SIZE)
            t->render(window);
    }

    for (int i = 0; i < buildings.size(); i++) {
        std::shared_ptr<Building> building_shared = buildings[i];
        Building* b = building_shared.get();
        if (b->getX() < camera.getX() + camera.getViewWidth() / 2 + TILE_SIZE && b->getX() > camera.getX() - camera.getViewWidth() / 2 - TILE_SIZE
                && b->getY() < camera.getY() + camera.getViewHeight() / 2 + TILE_SIZE && b->getY() > camera.getY() - camera.getViewHeight() / 2 - TILE_SIZE)
            b->render(window);
    }


    int fps = (int) (1.0 / fpsClock.restart().asSeconds());
    fpsText.setPosition(camera.getX() - camera.getViewWidth() / 2 + 10, camera.getY() - camera.getViewHeight() / 2 + 10);
    if (fpsCounter > 0) {
        fpsCounter -= 1.0 * delta;
    } else {
        fpsText.setString("FPS: " + std::to_string(fps));
        fpsCounter = 60;
    }
    window->draw(fpsText);
}

void Game::update(sf::RenderWindow* window, float delta) {
    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == keys[THROTTLE])
                throttle = true;
            if (event.key.code == keys[BRAKE])
                brake = true;
            if (event.key.code == keys[HANDBRAKE])
                handbrake = true;
            if (event.key.code == keys[LEFT])
                left = true;
            if (event.key.code == keys[RIGHT])
                right = true;
            if (event.key.code == sf::Keyboard::Escape)
                window->close();
            if (event.key.code == sf::Keyboard::P)
                pause = !pause;
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == keys[THROTTLE])
                throttle = false;
            if (event.key.code == keys[BRAKE])
                brake = false;
            if (event.key.code == keys[HANDBRAKE])
                handbrake = false;
            if (event.key.code == keys[LEFT])
                left = false;
            if (event.key.code == keys[RIGHT])
                right = false;
            break;
        }
    }

    if (pause) {

    } else {
        player.setInput(throttle, brake, handbrake, left, right);
        Point pPos((int) round(player.getX() / TILE_SIZE), (int) round(player.getY() / TILE_SIZE));
        Tile* pTile = tiles[pPos].get();
        player.update(delta, &pPos, pTile);

        // Car updates //
        for (int i = 0; i < npcs.size(); i++) {
            std::shared_ptr<Car> car_shared = npcs[i];
            Car* c = car_shared.get();
            if (c->getX() < camera.getX() + camera.getViewWidth() / 2 + TILE_SIZE
                    && c->getX() > camera.getX() - camera.getViewWidth() / 2 - TILE_SIZE
                    && c->getY() < camera.getY() + camera.getViewHeight() / 2 + TILE_SIZE
                    && c->getY() > camera.getY() - camera.getViewHeight() / 2 - TILE_SIZE) {
                Point cPos((int) round(c->getX() / TILE_SIZE), (int) round(c->getY() / TILE_SIZE));
                Tile* currentTile = tiles[cPos].get();

                c->update(delta, &cPos, currentTile);
                // Add crashed cars to a queue for ambulances
                if (c->isCrashed() && !c->isInCrashQueue()) {
                    crashed.add(c);
                    c->putInCrashQueue(true);
                }

                player.handleCollisions(c, delta);
                c->handleCollisions(&player, delta);

                // Police-specific code - set the police car's target to the player
                float baseDistance = 0;
                if (!c->isCrashed() && isType<Police, Car>(c)) {
                    Police* pol = (Police*) c;
                    pol->setTarget(&player);
                    pol->setNearest(nullptr);

                    baseDistance = 100000;

                    float distance = pointDistance2(pol->getX(), pol->getY(), player.getX(), player.getY());
                    if (!pol->isCrashed() && distance < baseDistance) {
                        pol->setNearest(&player);
                        baseDistance = distance;
                    }
                }
                // Ambulance-specific code - set the ambulance's target to a crashed car and
                // avoid the player if necessary
                if (isType<Ambulance, Car>(c)) {
                    Ambulance* amb = (Ambulance*) c;
                    if (amb->isCrashed()) {
                        if (amb->getTarget() != nullptr)
                            amb->getTarget()->putInCrashQueue(false);
                    } else {
                        if (!crashed.isEmpty() && amb->getTarget() == nullptr) {
                            amb->setTarget(crashed[0]);
                            crashed.remove((unsigned int) 0);
                        }
                        amb->setNearest(nullptr);

                        baseDistance = 100000;
                    }

                    if (!amb->isOnRoad()) {
                        float distance = pointDistance2(c->getX(), c->getY(), player.getX(), player.getY());
                        if (!amb->isCrashed() && distance < baseDistance) {
                            amb->setNearest(&player);
                            baseDistance = distance;
                        }
                    }
                }

                // Allow cars to interact
                for (int i = 0; i < npcs.size(); i++) {
                    std::shared_ptr<Car> other_shared = npcs[i];
                    Car* other = other_shared.get();
                    if (other->getX() < camera.getX() + camera.getViewWidth() / 2 + TILE_SIZE
                            && other->getX() > camera.getX() - camera.getViewWidth() / 2 - TILE_SIZE
                            && other->getY() < camera.getY() + camera.getViewHeight() / 2 + TILE_SIZE
                            && other->getY() > camera.getY() - camera.getViewHeight() / 2 - TILE_SIZE) {
                        // Handle collisions between cars
                        if (other != c && pointDistance2(c->getX(), c->getY(), other->getX(), other->getY()) <= sqr(TILE_SIZE / 2))
                            c->handleCollisions(other, delta);

                        // Tell police cars to avoid other cars
                        if (isType<Police, Car>(c)) {
                            Police* pol = (Police*) c;
                            float distance = pointDistance2(pol->getX(), pol->getY(), other->getX(), other->getY());
                            if (!pol->isCrashed() && distance < baseDistance && other != pol) {
                                pol->setNearest(other);
                                baseDistance = distance;
                            }
                        }
                        // Tell ambulances to avoid other cars
                        if (isType<Ambulance, Car>(c)) {
                            Ambulance* amb = (Ambulance*) c;
                            if (!amb->isOnRoad()) {
                                float distance = pointDistance2(amb->getX(), amb->getY(), other->getX(), other->getY());
                                if (!amb->isCrashed() && distance < baseDistance && other != amb) {
                                    amb->setNearest(other);
                                    baseDistance = distance;
                                }
                            }
                        }
                    }
                }

                if (!c->isCrashed() && isType<OnRoad, Car>(c)) {
                    OnRoad* onRoad = (OnRoad*) c;
                    // Update cars that follow roads when needed
                    if (onRoad->isOnRoad() && onRoad->shouldFindNode()) {
                        ArrayList<Tile*> nodeList;
                        // Get positions surrounding this npc
                        Point pL(cPos.getX() - 1, cPos.getY());
                        Point pR(cPos.getX() + 1, cPos.getY());
                        Point pU(cPos.getX(), cPos.getY() - 1);
                        Point pD(cPos.getX(), cPos.getY() + 1);
                        Tile* left = nullptr;
                        Tile* right = nullptr;
                        Tile* up = nullptr;
                        Tile* down = nullptr;
                        Tile* uturn = nullptr;
                        // Determine which position is valid to move to next
                        // by checking for whether the road continues this way (isWall)
                        // and ensuring no u-turns
                        tilemapiterator_t end = tiles.end();
                        tilemapiterator_t it = tiles.find(pL);
                        if (it != end) {
                            left = tiles[pL].get();
                            if (left->hasRoad() && !currentTile->isWallLeft() && !left->getVisited()->contains(onRoad))
                                nodeList.add(left);
                        }
                        it = tiles.find(pR);
                        if (it != end) {
                            right = tiles[pR].get();
                            if (right->hasRoad() && !currentTile->isWallRight() && !right->getVisited()->contains(onRoad))
                                nodeList.add(right);
                        }
                        it = tiles.find(pU);
                        if (it != end) {
                            up = tiles[pU].get();
                            if (up->hasRoad() && !currentTile->isWallUp() && !up->getVisited()->contains(onRoad))
                                nodeList.add(up);
                        }
                        it = tiles.find(pD);
                        if (it != end) {
                            down = tiles[pD].get();
                            if (down->hasRoad() && !currentTile->isWallDown() && !down->getVisited()->contains(onRoad))
                                nodeList.add(down);
                        }
                        // If we couldn't find somewhere to go, we may have encountered a loop
                        // Here we should allow the npc to go back on itself
                        if (nodeList.isEmpty()) {
                            // Work out which tile would cause a u-turn
                            int targetRotation = onRoad->getTargetRotation();
                            if (targetRotation >= 355 || targetRotation <= 5)
                                uturn = left;
                            if (targetRotation >= 175 && targetRotation <= 185)
                                uturn = right;
                            if (targetRotation >= 85 && targetRotation <= 95)
                                uturn = up;
                            if (targetRotation >= 265 && targetRotation <= 275)
                                uturn = down;

                            if (left != nullptr) {
                                if (left->hasRoad() && uturn != left && !currentTile->isWallLeft()) {
                                    left->removeVisited(onRoad);
                                    nodeList.add(left);
                                }
                            }
                            if (right != nullptr) {
                                if (right->hasRoad() && uturn != right && !currentTile->isWallRight()) {
                                    right->removeVisited(onRoad);
                                    nodeList.add(right);
                                }
                            }
                            if (up != nullptr) {
                                if (up->hasRoad() && uturn != up && !currentTile->isWallUp()) {
                                    up->removeVisited(onRoad);
                                    nodeList.add(up);
                                }
                            }
                            if (down != nullptr) {
                                if (down->hasRoad() && uturn != down && !currentTile->isWallDown()) {
                                    down->removeVisited(onRoad);
                                    nodeList.add(down);
                                }
                            }
                        }
                        onRoad->setNodes(nodeList);
                    }
                }
            }
        }
        // Car updates //

        // Tree updates
        for (int i = 0; i < trees.size(); i++) {
            std::shared_ptr<Tree> tree_shared = trees[i];
            Tree* t = tree_shared.get();
            t->update(delta);

            player.handleCollisions(t, delta);
        }

        camera.update(delta);

        bool left = false, right = false, up = false, down = false;
        if (pPos.getX() < -(genLeft - 6))
            left = true;
        if (pPos.getX() > genRight - 6)
            right = true;
        if (pPos.getY() < -(genUp - 6))
            up = true;
        if (pPos.getY() > (genDown - 6))
            down = true;

        addToMap(left, right, up, down);
    }
}

void Game::enter() {
    generateMap();
}

void Game::leave() {
    tiles.clear();
    npcs.clear();
    crashed.clear();

    width = 1;
    height = 1;
    genLeft = 0;
    genRight = 0;
    genUp = 0;
    genDown = 0;
    pause = false;

    player.reset();
}

void Game::addToMap(bool isLeft, bool isRight, bool isUp, bool isDown) {
    if (isLeft) {
        int x = -genLeft;
        for (int y = -genUp; y < genUp + genDown; y++) {
            addTile(x, y);
        }
        width++;
        genLeft++;
    }
    if (isRight) {
        int x = genRight;
        for (int y = -genUp; y < genUp + genDown; y++) {
            addTile(x, y);
        }
        width++;
        genRight++;
    }
    if (isUp) {
        int y = -genUp;
        for (int x = -genLeft; x < genLeft + genRight; x++) {
            addTile(x, y);
        }
        height++;
        genUp++;
    }
    if (isDown) {
        int y = genDown;
        for (int x = -genLeft; x < genLeft + genRight; x++) {
            addTile(x, y);
        }
        height++;
        genDown++;
    }
}

void Game::generateMap() {
    // Generate initial section of the map
    // Start by placing fixed starting roads then randomly generating the rest
    std::shared_ptr<Tile> start_shared = std::make_shared<Tile>(0 * TILE_SIZE, 0 * TILE_SIZE, Tile::Type::NS);
    Tile* start = start_shared.get();
    start->setImage(&AssetLoader::tileImages[(int) start->getType()]);
    tiles.emplace(Point(), start_shared);

    // Generate the rest of the map in a spiral pattern, ensuring
    // each tile has neighbours to match up roads
    int x = 1, y = 0;
    int dir = DIR_DOWN;
    int i = 0;
    while (i < 306) {
        if (addTile(x, y))
            i++;

        switch (dir) {
        case DIR_LEFT:
            if (x > -width / 2) {
                x--;
            } else {
                genDown++;
                height++;
                dir = DIR_UP;
            }
            break;
        case DIR_RIGHT:
            if (x < width / 2) {
                x++;
            } else {
                genUp++;
                height++;
                dir = DIR_DOWN;
            }
            break;
        case DIR_UP:
            if (y > -height / 2) {
                y--;
            } else {
                genLeft++;
                width++;
                dir = DIR_RIGHT;
            }
            break;
        case DIR_DOWN:
            if (y < height / 2) {
                y++;
            } else {
                genRight++;
                width++;
                dir = DIR_LEFT;
            }
            break;
        }
    }
}

bool Game::addTile(int x, int y) {
    Point current(x, y);

    tilemapiterator_t it = tiles.find(current);
    tilemapiterator_t end = tiles.end();
    if (it == tiles.end()) {
        Point pL(x - 1, y);
        Tile* left = nullptr;
        it = tiles.find(pL);
        if (it != end)
            left = tiles[pL].get();
        Point pR(x + 1, y);
        Tile* right = nullptr;
        it = tiles.find(pR);
        if (it != end)
            right = tiles[pR].get();
        Point pU(x, y - 1);
        Tile* up = nullptr;
        it = tiles.find(pU);
        if (it != end)
            up = tiles[pU].get();
        Point pD(x, y + 1);
        Tile* down = nullptr;
        it = tiles.find(pD);
        if (it != end)
            down = tiles[pD].get();

        // Decide which tiles can go here to maintain road connections
        ArrayList<Tile::Type> validTypes = getValidTypes(left, right, up, down);

        // When the array of valid types of tile has been generated, pick a random valid
        // tile and add it to the map (with a lower probability for cross roads)
        Tile::Type type = validTypes[randomInt(&generator, validTypes.size())];
        if (type == Tile::Type::NEWS)
            type = validTypes[randomInt(&generator, validTypes.size())];

        std::shared_ptr<Tile> tile_shared = std::make_shared<Tile>(x * TILE_SIZE, y * TILE_SIZE, type);
        Tile* tile = tile_shared.get();
        tile->setImage(&AssetLoader::tileImages[(int) tile->getType()]);
        tiles.insert(std::pair<Point, std::shared_ptr<Tile>>(current, tile_shared));

        if (tile->hasRoad()) {
            // Add nodes and npc cars
            if (randomInt(&generator, generateChance) == 0) {
                int id = randomInt(&generator, NUM_NPC_IMAGES);
                std::shared_ptr<NPC> npc_shared = std::make_shared<NPC>(x * TILE_SIZE, y * TILE_SIZE, &AssetLoader::npcImages[id], id);
                NPC* npc = npc_shared.get();
                npc->init();
                npc->setCurrentNode(tile);
                tile->addVisited(npc);
                npcs.add(npc_shared);
            }

            if (randomInt(&generator, generateChance * 8) == 0) {
                std::shared_ptr<Police> pol_shared = std::make_shared<Police>(x * TILE_SIZE, y * TILE_SIZE, &AssetLoader::policeImage, false);
                Police* pol = pol_shared.get();
                pol->init();
                pol->setTarget(&player);
                npcs.add(pol_shared);
            }

            if (randomInt(&generator, generateChance * 8) == 0) {
                std::shared_ptr<Ambulance> amb_shared = std::make_shared<Ambulance>(x * TILE_SIZE, y * TILE_SIZE, &AssetLoader::ambulanceImage);
                Ambulance* amb = amb_shared.get();
                amb->init();
                amb->setCurrentNode(tile);
                tile->addVisited(amb);
                npcs.add(amb_shared);
            }
        } else {
            if (randomInt(&generator, generateChance * 8) == 0) {
                // Add trees
                std::shared_ptr<Tree> tree_shared = std::make_shared<Tree>(x * TILE_SIZE, y * TILE_SIZE, &AssetLoader::treeImages[randomInt(&generator, NUM_TREE_IMAGES)]);
                Tree* tree = tree_shared.get();
                tree->init();
                trees.add(tree_shared);
            } else if (randomInt(&generator, 2) == 0) {
                // Add buildings
                std::shared_ptr<Building> building_shared = std::make_shared<Building>(x * TILE_SIZE, y * TILE_SIZE, Building::Type::SKY);
                Building* building = building_shared.get();
                building->setImage(&AssetLoader::buildingImages[(int) building->getType()]);
                buildings.add(building_shared);
            }
        }

        return true;
    }

    return false;
}

/* Method that takes the tiles surrounding the current tile being assessed
 * and returns a list of possible types the tile can be (for matching up roads) */
ArrayList<Tile::Type> Game::getValidTypes(Tile* left, Tile* right, Tile* up, Tile* down) {
    ArrayList<Tile::Type> validTypes;

    // Case where only tiles to the left of this one exist
    if (left != nullptr && right == nullptr && up == nullptr && down == nullptr) {
        if (left->isEast()) {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TN);
            validTypes.add(Tile::Type::TS);
            validTypes.add(Tile::Type::TW);
        } else {
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::PLAZA);
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::TE);
        }
    }
    // Case where only tiles to the right of this one exist
    if (left == nullptr && right != nullptr && up == nullptr && down == nullptr) {
        if (right->isWest()) {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::TE);
            validTypes.add(Tile::Type::TN);
            validTypes.add(Tile::Type::TS);
        } else {
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::PLAZA);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TW);
        }
    }
    // Case where only tiles above this one exist
    if (left == nullptr && right == nullptr && up != nullptr && down == nullptr) {
        if (up->isSouth()) {
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::TE);
            validTypes.add(Tile::Type::TN);
            validTypes.add(Tile::Type::TW);
        } else {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::PLAZA);
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TS);
        }
    }
    // Case where only tiles below this one exist
    if (left == nullptr && right == nullptr && up == nullptr && down != nullptr) {
        if (down->isNorth()) {
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TE);
            validTypes.add(Tile::Type::TS);
            validTypes.add(Tile::Type::TW);
        } else {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::PLAZA);
            validTypes.add(Tile::Type::TN);
        }
    }
    // Case where only tiles to the right and left of this one exist
    if (left != nullptr && right != nullptr && up == nullptr && down == nullptr) {
        if (left->isEast() && right->isWest()) {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::TN);
            validTypes.add(Tile::Type::TS);
        }
        if (left->isEast() && !right->isWest()) {
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TW);
        }
        if (!left->isEast() && right->isWest()) {
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::TE);
        }
        if (!left->isEast() && !right->isWest()) {
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::PLAZA);
        }
    }
    // Case where only tiles to the left of and above this one exist
    if (left != nullptr && right == nullptr && up != nullptr && down == nullptr) {
        if (left->isEast() && up->isSouth()) {
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::TN);
            validTypes.add(Tile::Type::TW);
        }
        if (left->isEast() && !up->isSouth()) {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TS);
        }
        if (!left->isEast() && up->isSouth()) {
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::TE);
        }
        if (!left->isEast() && !up->isSouth()) {
            validTypes.add(Tile::Type::PLAZA);
            validTypes.add(Tile::Type::SE);
        }
    }
    // Case where only tiles to the left of and below this one exist
    if (left != nullptr && right == nullptr && up == nullptr && down != nullptr) {
        if (left->isEast() && down->isNorth()) {
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TS);
            validTypes.add(Tile::Type::TW);
        }
        if (left->isEast() && !down->isNorth()) {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::TN);
        }
        if (!left->isEast() && down->isNorth()) {
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::TE);
        }
        if (!left->isEast() && !down->isNorth()) {
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::PLAZA);
        }
    }
    // Case where only tiles to the right of and above this one exist
    if (left == nullptr && right != nullptr && up != nullptr && down == nullptr) {
        if (right->isWest() && up->isSouth()) {
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::TE);
            validTypes.add(Tile::Type::TN);
        }
        if (right->isWest() && !up->isSouth()) {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::TS);
        }
        if (!right->isWest() && up->isSouth()) {
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::TW);
        }
        if (!right->isWest() && !up->isSouth()) {
            validTypes.add(Tile::Type::PLAZA);
            validTypes.add(Tile::Type::SW);
        }
    }
    // Case where only tiles to the right of and below this one exist
    if (left == nullptr && right != nullptr && up == nullptr && down != nullptr) {
        if (right->isWest() && down->isNorth()) {
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::TE);
            validTypes.add(Tile::Type::TS);
        }
        if (right->isWest() && !down->isNorth()) {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::TN);
        }
        if (!right->isWest() && down->isNorth()) {
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TW);
        }
        if (!right->isWest() && !down->isNorth()) {
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::PLAZA);
        }
    }
    // Case where only tiles above and below this one exist
    if (left == nullptr && right == nullptr && up != nullptr && down != nullptr) {
        if (up->isSouth() && down->isNorth()) {
            validTypes.add(Tile::Type::NEWS);
            validTypes.add(Tile::Type::NS);
            validTypes.add(Tile::Type::TE);
            validTypes.add(Tile::Type::TW);
        }
        if (up->isSouth() && !down->isNorth()) {
            validTypes.add(Tile::Type::NE);
            validTypes.add(Tile::Type::NW);
            validTypes.add(Tile::Type::TN);
        }
        if (!up->isSouth() && down->isNorth()) {
            validTypes.add(Tile::Type::SE);
            validTypes.add(Tile::Type::SW);
            validTypes.add(Tile::Type::TS);
        }
        if (!up->isSouth() && !down->isNorth()) {
            validTypes.add(Tile::Type::EW);
            validTypes.add(Tile::Type::PLAZA);
        }
    }
    // Case where only tiles to the left of, right of and above this one exist
    if (left != nullptr && right != nullptr && up != nullptr && down == nullptr) {
        if (left->isEast() && right->isWest()) {
            if (up->isSouth()) {
                validTypes.add(Tile::Type::NEWS);
                validTypes.add(Tile::Type::TN);
            } else {
                validTypes.add(Tile::Type::EW);
                validTypes.add(Tile::Type::TS);
            }
        }
        if (left->isEast() && !right->isWest()) {
            if (up->isSouth()) {
                validTypes.add(Tile::Type::NW);
                validTypes.add(Tile::Type::TW);
            } else {
                validTypes.add(Tile::Type::SW);
            }
        }
        if (!left->isEast() && right->isWest()) {
            if (up->isSouth()) {
                validTypes.add(Tile::Type::NE);
                validTypes.add(Tile::Type::TE);
            } else {
                validTypes.add(Tile::Type::SE);
            }
        }
        if (!left->isEast() && !right->isWest()) {
            if (up->isSouth()) {
                validTypes.add(Tile::Type::NS);
            } else {
                validTypes.add(Tile::Type::PLAZA);
            }
        }
    }
    // Case where only tiles to the left of, right of and below this one exist
    if (left != nullptr && right != nullptr && up == nullptr && down != nullptr) {
        if (left->isEast() && right->isWest()) {
            if (down->isNorth()) {
                validTypes.add(Tile::Type::NEWS);
                validTypes.add(Tile::Type::TS);
            } else {
                validTypes.add(Tile::Type::EW);
                validTypes.add(Tile::Type::TN);
            }
        }
        if (left->isEast() && !right->isWest()) {
            if (down->isNorth()) {
                validTypes.add(Tile::Type::SW);
                validTypes.add(Tile::Type::TW);
            } else {
                validTypes.add(Tile::Type::NW);
            }
        }
        if (!left->isEast() && right->isWest()) {
            if (down->isNorth()) {
                validTypes.add(Tile::Type::SE);
                validTypes.add(Tile::Type::TE);
            } else {
                validTypes.add(Tile::Type::NE);
            }
        }
        if (!left->isEast() && !right->isWest()) {
            if (down->isNorth()) {
                validTypes.add(Tile::Type::NS);
            } else {
                validTypes.add(Tile::Type::PLAZA);
            }
        }
    }
    // Case where only tiles to the left of, above and below this one exist
    if (left != nullptr && right == nullptr && up != nullptr && down != nullptr) {
        if (up->isSouth() && down->isNorth()) {
            if (left->isEast()) {
                validTypes.add(Tile::Type::NEWS);
                validTypes.add(Tile::Type::TW);
            } else {
                validTypes.add(Tile::Type::NS);
                validTypes.add(Tile::Type::TE);
            }
        }
        if (up->isSouth() && !down->isNorth()) {
            if (left->isEast()) {
                validTypes.add(Tile::Type::NW);
                validTypes.add(Tile::Type::TN);
            } else {
                validTypes.add(Tile::Type::NE);
            }
        }
        if (!up->isSouth() && down->isNorth()) {
            if (left->isEast()) {
                validTypes.add(Tile::Type::SW);
                validTypes.add(Tile::Type::TS);
            } else {
                validTypes.add(Tile::Type::SE);
            }
        }
        if (!up->isSouth() && !down->isNorth()) {
            if (left->isEast()) {
                validTypes.add(Tile::Type::EW);
            } else {
                validTypes.add(Tile::Type::PLAZA);
            }
        }
    }
    // Case where only tiles to the right of, above and below this one exist
    if (left == nullptr && right != nullptr && up != nullptr && down != nullptr) {
        if (up->isSouth() && down->isNorth()) {
            if (right->isWest()) {
                validTypes.add(Tile::Type::NEWS);
                validTypes.add(Tile::Type::TE);
            } else {
                validTypes.add(Tile::Type::NS);
                validTypes.add(Tile::Type::TW);
            }
        }
        if (up->isSouth() && !down->isNorth()) {
            if (right->isWest()) {
                validTypes.add(Tile::Type::NE);
                validTypes.add(Tile::Type::TN);
            } else {
                validTypes.add(Tile::Type::NW);
            }
        }
        if (!up->isSouth() && down->isNorth()) {
            if (right->isWest()) {
                validTypes.add(Tile::Type::SE);
                validTypes.add(Tile::Type::TS);
            } else {
                validTypes.add(Tile::Type::SW);
            }
        }
        if (!up->isSouth() && !down->isNorth()) {
            if (right->isWest()) {
                validTypes.add(Tile::Type::EW);
            } else {
                validTypes.add(Tile::Type::PLAZA);
            }
        }
    }
    // Tiles all around this one should not happen, so throw an error
    if (left != nullptr && right != nullptr && up != nullptr && down != nullptr) {
        std::cout << "Invalid tile placement" << std::endl;
    }

    return validTypes;
}

Game::~Game() {
    tiles.clear();
    npcs.clear();
    crashed.clear();
}
