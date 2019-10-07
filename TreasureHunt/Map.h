#pragma once

#include <string>
#include <vector>

#define MAP_TILE_SCALE 1

#define MAP_SIZE_W 48
#define MAP_SIZE_Y 24

class Device;

class Map
{
private:
	Device* _device = NULL;

	// Bit fields used by Tiled to flag rotations
	// https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#tile-flipping
	const unsigned long FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
	const unsigned long FLIPPED_VERTICALLY_FLAG = 0x40000000;
	const unsigned long FLIPPED_DIAGONALLY_FLAG = 0x20000000;

	unsigned long** _mapData = NULL;
	std::vector<unsigned long> _mapGroundData;

	bool isGround(int spriteIndex);

public:
	Map(Device* device, std::string path, std::string pathGround); // Constructor
	~Map(); // Destructor because ~

	void displayMap(int tileSize);
};