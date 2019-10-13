#pragma once

#include <string>
#include <vector>

class Coordinate;
class Device;
class TreasureManager
{
private:
	std::string _treasurePath = "";
	Coordinate* _posTreasure = NULL;
	unsigned long** _TreasureData = NULL;
	std::vector<Coordinate>* _listPosTreasure = NULL;
	Device* _device = NULL;
public:
	TreasureManager(Device* device, std::string treasurePath);
	~TreasureManager();
	bool checkTreasure(float playerX, float playerY);
	void displayTreasure();

};
