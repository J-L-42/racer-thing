/*
 * Assets.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ASSETS_HPP_
#define MAIN_ASSETS_HPP_


#include <string>

#include "Util/Constants.hpp"

#ifndef SFML_MAIN
#define SFML_MAIN

#include <iostream>

#include <SFML/Graphics.hpp>

#endif

#ifndef SFML_AUDIO
#define SFML_AUDIO

#include <SFML/Audio.hpp>

#endif

class AssetLoader {
public:
    static sf::Texture tileImages[NUM_TILE_IMAGES];
    static sf::Texture npcImages[NUM_NPC_IMAGES];
    static sf::Texture playerImage, policeImage, ambulanceImage, skidImage;
    static sf::Texture treeImages[NUM_TREE_IMAGES];
    static sf::Texture buildingImages[NUM_BUILDING_IMAGES];

    static sf::Sound engineSound, skidSound;
    static sf::Sound crashSounds[NUM_CRASH_SOUNDS];

    static sf::SoundBuffer engineSoundBuffer, skidSoundBuffer;
    static sf::SoundBuffer crashSoundBuffer[NUM_CRASH_SOUNDS];

    static sf::Font main;

    static void init(std::string* art, std::string* sounds, std::string* fonts);

    ~AssetLoader();
};


#endif /* MAIN_ASSETS_HPP_ */
