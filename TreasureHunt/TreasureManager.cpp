#include "TreasureManager.h"
#include "Coordinate.h"
#include "Map.h"
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "Device.h"

TreasureManager::TreasureManager(Device* device, std::string treasurePath) : _device(device) , _treasurePath(treasurePath)
{
	_posTreasure = new Coordinate(-1, -1);
	_listPosTreasure = new std::vector<Coordinate>();

	// Create 1rst dimension
	_TreasureData = new unsigned long* [MAP_SIZE_H];
	memset(_TreasureData, 0, sizeof(unsigned long*) * MAP_SIZE_H);

	// Create 2nd dimension
	for (int i = 0; i < MAP_SIZE_H; i++)
	{
		_TreasureData[i] = new unsigned long[MAP_SIZE_W];
		memset(_TreasureData[i], 0, sizeof(unsigned long) * MAP_SIZE_W);
	}

	// ifsteam/ofstream == IO read write streams, fstream does both
	// Open the file on the stream
	std::ifstream TreasureStream(_treasurePath);

	std::string line = "";
	std::string strTileIndex = "";

	size_t endPos = 0;

	int tileX = 0;
	int tileY = 0;

	while (std::getline(TreasureStream, line)) // Read line by line
	{
		// npos equals -1, which means the maximum value for its containing type, unsigned long long / unsigned __int64
		while (endPos != std::string::npos) // Npos means not found
		{
			endPos = line.find_first_of(","); // Returns npos if nothing is found
			strTileIndex = line.substr(0, endPos); // Substrings left of endPos (From some position for some amount of chars)

			if (strTileIndex.length() > 0) // Only proceed if there is a value to work on
			{
				line = line.substr(endPos + (size_t)1); // Substrings right from endPos (From some positon until the end)
				_TreasureData[tileY][tileX] = std::stoul(strTileIndex); // Assign left substring as unsigned long
				tileX++;
			}
			else if (endPos != std::string::npos)
			{
				// Avoid getting stuck if some middle value is empty instead of having a number
				// For instance if we have a ...1,2,,4,5... sequence, the ,, is problematic and would cause an infinite loop without this
				line = line.substr(endPos + (size_t)1);
				_TreasureData[tileY][tileX] = 0;
				tileX++;
			}
		}

		tileY++;
		tileX = 0;
		endPos = 0;
	}

	// Closing the stream
	TreasureStream.close();

	// Make the vector
	unsigned long Index = 0;
	float x = 0.f;
	float y = 0.f;

	for (int i = 0; i < MAP_SIZE_H; i++)
		for (int j = 0; j < MAP_SIZE_W; j++)
		{
			// Get raw sprite index with flags
			Index = _TreasureData[i][j];

			x = j * TILE_SIZE * MAP_TILE_SCALE; // Pixels on x, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			y = i * TILE_SIZE * MAP_TILE_SCALE; // Pixels on y, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			if (Index != 0)
			{
				_posTreasure->changeCoordinate(x, y);
				_listPosTreasure->push_back(*_posTreasure);
			}
		}

	// initialize random seed
	srand(time(NULL));

	// generate number
	int number = rand() % _listPosTreasure->size();
	_posTreasure->changeCoordinate(((*_listPosTreasure)[number]).GetX(), ((*_listPosTreasure)[number]).GetY());
}
TreasureManager::~TreasureManager() 
{

}
bool TreasureManager::checkTreasure(float playerX, float playerY) 
{
	for (float xBis = playerX; xBis <= playerX + TILE_SIZE; xBis += TILE_SIZE)
	{
		for (float yBis = playerY; yBis <= playerY + TILE_SIZE; yBis += TILE_SIZE)
		{
			if (_posTreasure->GetX() + 3 <= xBis && _posTreasure->GetX() + TILE_SIZE - 3 >= xBis && _posTreasure->GetY() + 3 <= yBis && _posTreasure->GetY() + TILE_SIZE - 3 >= yBis)
			{
				return true;
			}
		}
	}

	for (float xBis = _posTreasure->GetX() + 3; xBis <= _posTreasure->GetX() + TILE_SIZE - 3; xBis += TILE_SIZE - 2 * 3)
	{
		for (float yBis = _posTreasure->GetY() + 3; yBis <= _posTreasure->GetY() + TILE_SIZE - 3; yBis += TILE_SIZE - 2 * 3)
		{
			if (xBis <= playerX + TILE_SIZE && xBis >= playerX && yBis <= playerY + TILE_SIZE && yBis >= playerY)
			{
				return true;
			}
		}
	}
	return false;
}
void TreasureManager::displayTreasure() 
{
	_device->addDrawable(152, _posTreasure->GetX(), _posTreasure->GetY(), MAP_TILE_SCALE, 2, 0, 0, 0);
}
