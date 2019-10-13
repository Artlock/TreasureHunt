#include "OPTIONS.h"

#include "TreasureManager.h"
#include "Coordinate.h"
#include "Device.h"
#include "FileToArray.h"

#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <vector>

TreasureManager::TreasureManager(Device* device, std::string treasurePath) : _device(device), _treasurePath(treasurePath)
{
	_posTreasure = new Coordinate(-1, -1);
	_listPosTreasure = new std::vector<Coordinate>();

	FileToArray<unsigned long>::ReadFileTo_Array_2D(treasurePath, MAP_SIZE_H, MAP_SIZE_W, _TreasureData);

	// Make the vector
	unsigned long Index = 0;
	float x = 0.f;
	float y = 0.f;

	for (int i = 0; i < MAP_SIZE_H; i++)
	{
		for (int j = 0; j < MAP_SIZE_W; j++)
		{
			// Get raw sprite index with flags
			Index = _TreasureData[i][j];

			x = j * SC_TILE_SIZE_XY * MAP_SCALE; // Pixels on x, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			y = i * SC_TILE_SIZE_XY * MAP_SCALE; // Pixels on y, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			if (Index != 0)
			{
				_posTreasure->changeCoordinate(x, y);
				_listPosTreasure->push_back(*_posTreasure);
			}
		}
	}

	// Initialize random seed
	srand(time(NULL));

	// Generate number
	int number = rand() % _listPosTreasure->size();
	_posTreasure->changeCoordinate(((*_listPosTreasure)[number]).GetX(), ((*_listPosTreasure)[number]).GetY());
}

TreasureManager::~TreasureManager()
{

}

bool TreasureManager::checkTreasure(float playerX, float playerY)
{
	for (float xBis = playerX; xBis <= playerX + SC_TILE_SIZE_XY * PLAYER_SCALE; xBis += SC_TILE_SIZE_XY * PLAYER_SCALE)
	{
		for (float yBis = playerY; yBis <= playerY + SC_TILE_SIZE_XY * PLAYER_SCALE; yBis += SC_TILE_SIZE_XY * PLAYER_SCALE)
		{
			if (_posTreasure->GetX() + 3 <= xBis && _posTreasure->GetX() + SC_TILE_SIZE_XY * MAP_SCALE - 3 >= xBis && _posTreasure->GetY() + 3 <= yBis && _posTreasure->GetY() + SC_TILE_SIZE_XY * MAP_SCALE - 3 >= yBis)
			{
				return true;
			}
		}
	}

	for (float xBis = _posTreasure->GetX() + 3; xBis <= _posTreasure->GetX() + SC_TILE_SIZE_XY * MAP_SCALE - 3; xBis += SC_TILE_SIZE_XY * MAP_SCALE - (3 * 2))
	{
		for (float yBis = _posTreasure->GetY() + 3; yBis <= _posTreasure->GetY() + SC_TILE_SIZE_XY * MAP_SCALE - 3; yBis += SC_TILE_SIZE_XY * MAP_SCALE - (3 * 2))
		{
			if (xBis <= playerX + SC_TILE_SIZE_XY * PLAYER_SCALE && xBis >= playerX && yBis <= playerY + SC_TILE_SIZE_XY * PLAYER_SCALE && yBis >= playerY)
			{
				return true;
			}
		}
	}
	return false;
}

void TreasureManager::displayTreasure()
{
	_device->addDrawable(152, _posTreasure->GetX(), _posTreasure->GetY(), MAP_SCALE, 2, 0, 0, 0);
}
