#pragma once

// OUR OPTIONS:



#define DEVICE_WIDTH 150 
#define DEVICE_HEIGHT 150 

#define INITIAL_POS_WINDOW_WIDTH DEVICE_WIDTH/2
#define INITIAL_POS_WINDOW_HEIGHT DEVICE_HEIGHT/2

#define MAP_WIDTH 768 // 16 * 48 pixels 
#define MAP_HEIGHT 384 // 16 * 24 pixels

#define TILE_SIZE 16

#define TO_DISPLAY 1153 // 1152 (= 48 * 24 tiles) + 1 player

#define MAX_FRAMERATE 144

#define END_DELAY 5



#define ANIMATOR_FRAMES 2 // 2 images per second
#define ANIMATOR_SPEED 2 // Timescale of the animation




#define TILE_SIZE 16
#define COLLISIONS_GAP 3


#define MAP_TILE_SCALE 1

#define MAP_SIZE_W 48
#define MAP_SIZE_H 24

// PLAYER

#define PLAYER_SIZE_W 16
#define PLAYER_SIZE_H 16

#define PLAYER_SPEED 100

#define PLAYER_SCALE 1

#define PLAYER_ANIMATION_FRAMES 2

#define PLAYER_IDLE_SPRITE 275

#define PLAYER_LIFE 100

// SPRITE SHEET

#define SC_TILE_NB_XY 32

#define SC_TILE_SIZE_XY 16
#define SC_TILE_GAP_XY 1

// Treasure

#define TILE_SIZE 16

// Zombie


#define Z_SPEED 60
#define Z_INDEX 243
#define Z_SCALE 1
#define Z_ANIMATION_FRAME 2

#define Z_DAMAGES 30
#define Z_DISTANCE 10

