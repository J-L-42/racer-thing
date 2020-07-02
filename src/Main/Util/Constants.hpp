/*
 * Constants.hpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#ifndef MAIN_CONSTANTS_HPP_
#define MAIN_CONSTANTS_HPP_


#define TILE_SIZE 640
#define THROTTLE 0
#define BRAKE 1
#define LEFT 2
#define RIGHT 3
#define HANDBRAKE 4
#define BASE_WIDTH 3840
#define BASE_HEIGHT 2160
#define FPS 60

#define NUM_TILE_IMAGES 12
#define NUM_NPC_IMAGES 6
#define NUM_CAR_IMAGES 10
#define NUM_TREE_IMAGES 6
#define NUM_BUILDING_IMAGES 1
#define NUM_CRASH_SOUNDS 2
#define NUM_FONTS 1

#include <string>

extern std::string ART[29];
extern std::string SOUNDS[4];
extern std::string FONTS[1];


#endif /* MAIN_CONSTANTS_HPP_ */
