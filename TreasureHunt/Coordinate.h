#pragma once
class Coordinate
{
private:
	float _x = 0;
	float _y = 0;
public:
	Coordinate(float x, float y);
	~Coordinate();
	void changeCoordinate(float x, float y);
	int GetX();
	int GetY();
};

