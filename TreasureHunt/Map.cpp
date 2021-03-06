#include "OPTIONS.h"

#include "Map.h"
#include "Device.h"
#include "FileToArray.h"

#include <fstream>
#include <cstring>

#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end

Map::Map(Device* device, std::string path, std::string pathRoofs, std::string pathGround) : _device(device)
{
	FileToArray<unsigned long>::ReadFileTo_Array_2D(path, MAP_SIZE_H, MAP_SIZE_W, _mapData);
	FileToArray<unsigned long>::ReadFileTo_Vector_1D(pathGround, _mapGroundData);
	FileToArray<unsigned long>::ReadFileTo_Vector_1D(pathRoofs, _mapRoofData);
}

Map::~Map() // Destructor because ~
{
	// Deallocate the array from the heap
	for (int i = 0; i < MAP_SIZE_H; i++) {
		delete[] _mapData[i];
	}

	delete[] _mapData;
	_mapData = NULL;

	_device = NULL;
}

void Map::displayMap(int tileSize)
{
	unsigned long spriteIndex = 0;
	unsigned long rawSpriteIndex = 0;
	int x = 0;
	int y = 0;
	int flipH = 0;
	int flipV = 0;
	int flipD = 0;

	for (int i = 0; i < MAP_SIZE_H; i++)
		for (int j = 0; j < MAP_SIZE_W; j++)
		{
			// Get raw sprite index with flags
			rawSpriteIndex = _mapData[i][j];

			// Get actual sprite index without flags
			spriteIndex = rawSpriteIndex & ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
			// & (AND) because we want to remove anything added by | (OR) when the flags were added
			// ~ (REVERT) because we need to reverse the added flags before doing so
			// | (OR) because we want to sum all flags

			// Meaning
			// RAW_BITS | FLAGS to add flags
			// FLAGGED_BITS  & ~(FLAGS) to remove them

			// Check if flag is applied
			flipH = (rawSpriteIndex & FLIPPED_HORIZONTALLY_FLAG) == FLIPPED_HORIZONTALLY_FLAG;
			flipV = (rawSpriteIndex & FLIPPED_VERTICALLY_FLAG) == FLIPPED_VERTICALLY_FLAG;
			flipD = (rawSpriteIndex & FLIPPED_DIAGONALLY_FLAG) == FLIPPED_DIAGONALLY_FLAG;

			x = j * tileSize * MAP_SCALE; // Pixels on x, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			y = i * tileSize * MAP_SCALE; // Pixels on y, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)

			// Check if tile is a "roof/roof-base" (Means it's linked to another tile down below, and should be rendered after said tile)
			// If tile id = possible "roof/roof-base" id then check below and only display after the base one (Not the one directly below)

			bool ground = isGround(spriteIndex);
			int currentBaseY = y; // Current Y pos
			if (i < MAP_SIZE_H - 1 && isRoof(spriteIndex)) // If there is a tile below and it's also a roof
				currentBaseY = y + (tileSize * MAP_SCALE); // Next Y pos

			_device->addDrawable(spriteIndex, x, y, MAP_SCALE, ground ? 0 : 1, currentBaseY, flipH, flipV, flipD);
		}
}

bool Map::isGround(int spriteIndex)
{
	// Uses lambda expression ([&] captures all symbols by reference)
	return std::any_of(std::begin(_mapGroundData), std::end(_mapGroundData), [&](int i) {
		return i == spriteIndex;
		});
}

bool Map::isRoof(int spriteIndex)
{
	// Uses lambda expression ([&] captures all symbols by reference)
	return std::any_of(std::begin(_mapRoofData), std::end(_mapRoofData), [&](int i) {
		return i == spriteIndex;
		});
}
