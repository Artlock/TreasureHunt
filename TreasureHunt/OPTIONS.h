#pragma once

// DEVICE

#define MAX_FRAMERATE 144

#define MAP_WIDTH 768 // 16 * 48 pixels (Equal to our map size)
#define MAP_HEIGHT 384 // 16 * 24 pixels (Equal to our map size)

#define TO_RENDER 1155 // 1152 (= 48 * 24 tiles) + 1 player + 1 enemy + 1 treasure

#define DEVICE_WIDTH 150 
#define DEVICE_HEIGHT 150 

#define INITIAL_POS_WINDOW_WIDTH DEVICE_WIDTH/2
#define INITIAL_POS_WINDOW_HEIGHT DEVICE_HEIGHT/2

#define START_OF_GAME_DELAY 4
#define END_OF_GAME_DELAY 4

// SCALE

#define MAP_SCALE 1
#define PLAYER_SCALE 1
#define ZOMBIE_SCALE 1

// SPRITE SHEET

#define SC_TILE_SIZE_XY 16 // Size of a single tile in both x and y
#define SC_TILE_NB_XY 32 // Spritesheet is 32*32
#define SC_TILE_GAP_XY 1 // Gap between tiles in sheet

// COLLIDERS

#define COLLIDERS_GAP 3

// MAP

#define MAP_SIZE_W 48
#define MAP_SIZE_H 24

// ANIMATOR

#define ANIMATOR_FRAMES 2 // 2 images per second
#define ANIMATOR_SPEED 2 // Timescale of the animation

// PLAYER

#define PLAYER_SPEED 100
#define PLAYER_LIFE 100

#define PLAYER_ANIMATION_FRAMES 2
#define PLAYER_IDLE_SPRITE 275

// ZOMBIE

#define ZOMBIE_SPEED 60
#define ZOMBIE_DAMAGE 30
#define ZOMBIE_DISTANCE 10

#define ZOMBIE_ANIMATION_FRAMES 2
#define ZOMBIE_IDLE_SPRITE 243
