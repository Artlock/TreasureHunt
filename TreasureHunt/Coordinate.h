#pragma once
class Coordinate
{
private:
	int _x = 0;
	int _y = 0;
public:
	Coordinate(int x, int y);
	~Coordinate();
	void changeCoordinate(int x, int y);
	int GetX();
	int GetY();
};

