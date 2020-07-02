/*
 * Main.cpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#include "Main.hpp"

/* Render the current game state to the window */
void render(GameState* current, sf::RenderWindow* window, float delta) {
    while (window->isOpen()) {
        window->clear();
        current->render(window, delta);
        window->display();
    }
}

int main(int argc, char** argv) {
    // Enable threading for X
    //XInitThreads();

    sf::Clock clock;
    // Get the desktop resolution
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    // Create the window
    sf::RenderWindow window(mode, "Racer");
    //window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);

    // Load assets
    AssetLoader::init(ART, SOUNDS, FONTS);

    // Pointer to the current game state
    GameState* current;
    // Create the main game state
    Game game;
    game.init();
    current = &game;
    current->enter();

    //window.setActive(false);

    // Create and start the thread for rendering on
    //sf::Thread renderingThread(std::bind(&render, current, &window));
    //renderingThread.launch();
    //std::thread renderingThread(&render, current, &window);

    while (window.isOpen()) {
        // Get the delta time in seconds
        sf::Time elapsed = clock.restart();
        float delta = elapsed.asSeconds() * FPS;

        // Update the current game state
        current->update(&window, delta);

        window.clear();
        current->render(&window, delta);
        window.display();
    }

    // Detach the rendering thread
    //renderingThread.detach();

    return 0;
}
