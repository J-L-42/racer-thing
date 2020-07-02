/*
 * Assets.cpp
 *
 *  Created on: 18 Apr 2017
 *      Author: james
 */

#include "Assets.hpp"

sf::Texture AssetLoader::tileImages[NUM_TILE_IMAGES];
sf::Texture AssetLoader::npcImages[NUM_NPC_IMAGES];
sf::Texture AssetLoader::playerImage, AssetLoader::policeImage,
            AssetLoader::ambulanceImage, AssetLoader::skidImage;
sf::Texture AssetLoader::treeImages[NUM_TREE_IMAGES];
sf::Texture AssetLoader::buildingImages[NUM_BUILDING_IMAGES];

sf::Sound AssetLoader::engineSound, AssetLoader::skidSound;
sf::Sound AssetLoader::crashSounds[NUM_CRASH_SOUNDS];

sf::SoundBuffer AssetLoader::engineSoundBuffer, AssetLoader::skidSoundBuffer;
sf::SoundBuffer AssetLoader::crashSoundBuffer[NUM_CRASH_SOUNDS];

sf::Font AssetLoader::main;

void AssetLoader::init(std::string* art, std::string* sounds, std::string* fonts) {
    // Images //
    for (int i = 0; i < NUM_TILE_IMAGES; i++) {
        if (!tileImages[i].loadFromFile(art[i]))
            std::cout << "Unable to load texture for tile " << (i + 1) << std::endl;
    }

    for (int i = 0; i < NUM_NPC_IMAGES; i++) {
        if (!npcImages[i].loadFromFile(art[NUM_TILE_IMAGES + i + 1]))
            std::cout << "Unable to load texture for car " << (i + 1) << std::endl;
    }

    if (!playerImage.loadFromFile(art[NUM_TILE_IMAGES]))
        std::cout << "Unable to load texture for player" << std::endl;

    if (!skidImage.loadFromFile(art[NUM_TILE_IMAGES + NUM_NPC_IMAGES + 1]))
        std::cout << "Unable to load texture for skid mark" << std::endl;

    if (!policeImage.loadFromFile(art[NUM_TILE_IMAGES + NUM_NPC_IMAGES + 2]))
        std::cout << "Unable to load texture for police" << std::endl;

    if (!ambulanceImage.loadFromFile(art[NUM_TILE_IMAGES + NUM_NPC_IMAGES + 3]))
        std::cout << "Unable to load texture for police" << std::endl;

    for (int i = 0; i < NUM_TREE_IMAGES; i++) {
        if (!treeImages[i].loadFromFile(art[NUM_TILE_IMAGES + NUM_CAR_IMAGES + i]))
            std::cout << "Unable to load texture for tree " << (i + 1) << std::endl;
    }

    for (int i = 0; i < NUM_BUILDING_IMAGES; i++) {
        if (!buildingImages[i].loadFromFile(art[NUM_TILE_IMAGES + NUM_CAR_IMAGES + NUM_TREE_IMAGES + i]))
            std::cout << "Unable to load texture for building " << (i + 1) << std::endl;
    }
    // Images //

    // Sounds //
    if (engineSoundBuffer.loadFromFile(sounds[0]))
        engineSound.setBuffer(engineSoundBuffer);
    else
        std::cout << "Unable to load engine sound" << std::endl;

    if (skidSoundBuffer.loadFromFile(sounds[1]))
        skidSound.setBuffer(skidSoundBuffer);
    else
        std::cout << "Unable to load skid sound" << std::endl;

    for (int i = 0; i < NUM_CRASH_SOUNDS; i++) {
        if (crashSoundBuffer[i].loadFromFile(sounds[i + 2]))
            crashSounds[i].setBuffer(crashSoundBuffer[i]);
        else
            std::cout << "Unable to load crash sound " << (i + 1) << std::endl;
    }
    // Sounds //

    // Fonts //
    if (!main.loadFromFile(fonts[0]))
        std::cout << "Unable to load main font" << std::endl;
    // Fonts //
}
