#include "Colliders.h"
#include "Coordinate.h"
#include <fstream>
#include <list>
#include <iostream>

Colliders::Colliders(std::string pathCollider) : _pathCollider(pathCollider)
{
	std::list<Coordinate> listCoord();

	Coord = new Coordinate(-1,-1);


	// Create 1rst dimension
	_ColliderData = new unsigned long* [MAP_SIZE_Y];
	memset(_ColliderData, 0, sizeof(unsigned long*) * MAP_SIZE_Y);

	// Create 2nd dimension
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		_ColliderData[i] = new unsigned long[MAP_SIZE_W];
		memset(_ColliderData[i], 0, sizeof(unsigned long) * MAP_SIZE_W);
	}

	// ifsteam/ofstream == IO read write streams, fstream does both
	// Open the file on the stream
	std::ifstream ColliderStream(_pathCollider);

	std::string line = "";
	std::string strTileIndex = "";

	size_t endPos = 0;

	int tileX = 0;
	int tileY = 0;

	while (std::getline(ColliderStream, line)) // Read line by line
	{
		// npos equals -1, which means the maximum value for its containing type, unsigned long long / unsigned __int64
		while (endPos != std::string::npos) // Npos means not found
		{
			endPos = line.find_first_of(","); // Returns npos if nothing is found
			strTileIndex = line.substr(0, endPos); // Substrings left of endPos (From some position for some amount of chars)

			if (strTileIndex.length() > 0) // Only proceed if there is a value to work on
			{
				line = line.substr(endPos + (size_t)1); // Substrings right from endPos (From some positon until the end)
				_ColliderData[tileY][tileX] = std::stoul(strTileIndex); // Assign left substring as unsigned long
				tileX++;
			}
			else if (endPos != std::string::npos)
			{
				// Avoid getting stuck if some middle value is empty instead of having a number
				// For instance if we have a ...1,2,,4,5... sequence, the ,, is problematic and would cause an infinite loop without this
				line = line.substr(endPos + (size_t)1);
				_ColliderData[tileY][tileX] = 0;
				tileX++;
			}
		}

		tileY++;
		tileX = 0;
		endPos = 0;
	}

	// Closing the stream
	ColliderStream.close();
}

Colliders::~Colliders() 
{
	
}

void Colliders::MakeList(int tileSize)
{
	unsigned long Index = 0;
	float x = 0.f;
	float y = 0.f;

	for (int i = 0; i < MAP_SIZE_Y; i++)
		for (int j = 0; j < MAP_SIZE_W; j++)
		{
			// Get raw sprite index with flags
			Index = _ColliderData[i][j];

			x = j * tileSize * MAP_TILE_SCALE; // Pixels on x, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			y = i * tileSize * MAP_TILE_SCALE; // Pixels on y, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			Coord->changeCoordinate(x, y);
			if (Index != 0) 
			{
				listCoord.push_back(*Coord);
			}
		}
}

bool Colliders::CompareMap(float x, float y)
{
	for (std::list<Coordinate>::iterator it = listCoord.begin(); it != listCoord.end(); ++it) 
	{
		for (float xBis = x; xBis <= x + TILE_SIZE; xBis += TILE_SIZE) 
		{
			for (float yBis = y; yBis <= y + TILE_SIZE; yBis += TILE_SIZE)
			{
				if (it->GetX()+3 <= xBis && it->GetX()+TILE_SIZE-3 >= xBis && it->GetY()+3 <= yBis && it->GetY()+TILE_SIZE-3 >= yBis)
				{
					return true;
				}
			}
		}

		for (float ITxBis = it->GetX()+3; ITxBis <= it->GetX() + TILE_SIZE-3; ITxBis += TILE_SIZE-2*3)
		{
			for (float ITyBis = it->GetY()+3; ITyBis <= it->GetY() + TILE_SIZE-3; ITyBis += TILE_SIZE-2*3)
			{
				if (ITxBis <= x + TILE_SIZE && ITxBis >= x && ITyBis <= y+TILE_SIZE && ITyBis >= y)
				{
					return true;
				}
			}
		}
	}
	return false;
}