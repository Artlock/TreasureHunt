#include "Map.h"
#include "Device.h"

#include <fstream>
#include <cstring>

#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end

Map::Map(Device* device, std::string path, std::string pathGround) : _device(device)
{
	// Initializing the two dimentional array that will contain our values

	// Create 1nd dimension
	_mapData = new unsigned long* [MAP_SIZE_H];
	memset(_mapData, 0, sizeof(unsigned long*) * MAP_SIZE_H);

	// Create 2nd dimension
	for (int i = 0; i < MAP_SIZE_H; i++)
	{
		_mapData[i] = new unsigned long[MAP_SIZE_W];
		memset(_mapData[i], 0, sizeof(unsigned long) * MAP_SIZE_W);
	}

	// ifsteam/ofstream == IO read write streams, fstream does both
	// Open the file on the stream
	std::ifstream mapStream(path);

	// Read the file containing the map's tile values

	std::string line = "";
	std::string strTileIndex = "";

	// size_t will work since we compare endPos to std::string::npos, which is a size_t type
	// size_t is actually a typedef for unsigned long long

	// npos is actually equal to -1, which when converted to size_t becomes the max value for that type

	// When comparing a signed type with an unsigned type, the signed type is converted to the unsigned type
	// This means instead of reading the 1st binary 1 as negative and adding the rest as positive, we read everything as positive

	// This is why using int works (Stored negative -1 becomes max value of unsigned long long)
	// Unsigned long long works too (Stored value is already max value since we tried to assign -1 to an unsigned type)

	// Meanwhile, a simple unsigned long will not work (Stored value is already max value... of long... and long is smaller than long long)

	size_t endPos = 0;

	int tileX = 0;
	int tileY = 0;

	while (std::getline(mapStream, line)) // Read line by line
	{
		// npos equals -1, which means the maximum value for its containing type, unsigned long long / unsigned __int64
		while (endPos != std::string::npos) // Npos means not found
		{
			endPos = line.find_first_of(","); // Returns npos if nothing is found
			strTileIndex = line.substr(0, endPos); // Substrings left of endPos (From some position for some amount of chars)

			if (strTileIndex.length() > 0) // Only proceed if there is a value to work on
			{
				line = line.substr(endPos + (size_t)1); // Substrings right from endPos (From some positon until the end)
				_mapData[tileY][tileX] = std::stoul(strTileIndex); // Assign left substring as unsigned long
				tileX++;
			}
			else if (endPos != std::string::npos)
			{
				// Avoid getting stuck if some middle value is empty instead of having a number
				// For instance if we have a ...1,2,,4,5... sequence, the ,, is problematic and would cause an infinite loop without this
				line = line.substr(endPos + (size_t)1);
				_mapData[tileY][tileX] = 0;
				tileX++;
			}
		}

		tileY++;
		tileX = 0;
		endPos = 0;
	}

	// Closing the stream
	mapStream.close();

	// _mapGroundData

	_mapGroundData = std::vector<unsigned long>(50);

	mapStream.open(pathGround);

	line = "";
	strTileIndex = "";

	endPos = 0;

	while (std::getline(mapStream, line)) // Read line by line
	{
		// npos equals -1, which means the maximum value for its containing type, unsigned long long / unsigned __int64
		while (endPos != std::string::npos) // Npos means not found
		{
			endPos = line.find_first_of(","); // Returns npos if nothing is found
			strTileIndex = line.substr(0, endPos); // Substrings left of endPos (From some position for some amount of chars)

			if (strTileIndex.length() > 0) // Only proceed if there is a value to work on
			{
				line = line.substr(endPos + (size_t)1); // Substrings right from endPos (From some positon until the end)
				_mapGroundData.push_back(std::stoul(strTileIndex)); // Assign left substring as unsigned long
			}
			else if (endPos != std::string::npos)
			{
				// Avoid getting stuck if some middle value is empty instead of having a number
				// For instance if we have a ...1,2,,4,5... sequence, the ,, is problematic and would cause an infinite loop without this
				line = line.substr(endPos + (size_t)1);
				_mapGroundData.push_back(0);
			}
		}

		endPos = 0;
	}

	mapStream.close();
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

			x = j * tileSize * MAP_TILE_SCALE; // Pixels on x, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			y = i * tileSize * MAP_TILE_SCALE; // Pixels on y, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)

			// Check if tile is a "roof/roof-base" (Means it's linked to another tile down below, and should be rendered after said tile)
			// If tile id = possible "roof/roof-base" id then check below and only display after the base one (Not the one directly below)

			// We're still based on tiled ids here, the spritesheet will -1 the id later
			int roofTileID = 417; // White wall, eventually replace with a list that contains all possible roof tiles
			int currentBaseY = y;

			if (spriteIndex == roofTileID)
				currentBaseY = checkHasBase(roofTileID, y, tileSize, i, j);

			if (!isGround(spriteIndex))
				_device->addDrawable(spriteIndex, x, y, MAP_TILE_SCALE, 1, currentBaseY, flipH, flipV, flipD);
			else
				_device->addDrawable(spriteIndex, x, y, MAP_TILE_SCALE, 0, currentBaseY, flipH, flipV, flipD);
		}
}

bool Map::isGround(int spriteIndex)
{
	// Uses lambda expression ([&] captures all symbols by reference)
	return std::any_of(std::begin(_mapGroundData), std::end(_mapGroundData), [&](int i) {
		return i == spriteIndex;
		});
}

int Map::checkHasBase(int roofTileID, int defaultY, int tileSize, int currentH, int currentW)
{
	// -1 because we need to have a tile below to check against

	if (currentH < MAP_SIZE_H - 1 && (_mapData[currentH + 1][currentW] & ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG)) == roofTileID)
		return (currentH + 1) * tileSize;
	else
		return defaultY;
}
