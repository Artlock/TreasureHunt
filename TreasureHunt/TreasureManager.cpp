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

			x = j * TILE_SIZE * MAP_TILE_SCALE; // Pixels on x, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			y = i * TILE_SIZE * MAP_TILE_SCALE; // Pixels on y, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
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
	for (float xBis = playerX; xBis <= playerX + TILE_SIZE * PLAYER_SCALE; xBis += TILE_SIZE * PLAYER_SCALE)
	{
		for (float yBis = playerY; yBis <= playerY + TILE_SIZE * PLAYER_SCALE; yBis += TILE_SIZE * PLAYER_SCALE)
		{
			if (_posTreasure->GetX() + 3 <= xBis && _posTreasure->GetX() + TILE_SIZE * MAP_TILE_SCALE - 3 >= xBis && _posTreasure->GetY() + 3 <= yBis && _posTreasure->GetY() + TILE_SIZE * MAP_TILE_SCALE - 3 >= yBis)
			{
				return true;
			}
		}
	}

	for (float xBis = _posTreasure->GetX() + 3; xBis <= _posTreasure->GetX() + TILE_SIZE * MAP_TILE_SCALE - 3; xBis += TILE_SIZE * MAP_TILE_SCALE - (3 * 2))
	{
		for (float yBis = _posTreasure->GetY() + 3; yBis <= _posTreasure->GetY() + TILE_SIZE * MAP_TILE_SCALE - 3; yBis += TILE_SIZE * MAP_TILE_SCALE - (3 * 2))
		{
			if (xBis <= playerX + TILE_SIZE * PLAYER_SCALE && xBis >= playerX && yBis <= playerY + TILE_SIZE * PLAYER_SCALE && yBis >= playerY)
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
