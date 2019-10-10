#include "Coordinate.h"

Coordinate::Coordinate(float x, float y):_x(x),_y(y)
{

}
Coordinate::~Coordinate()
{

}
void Coordinate::changeCoordinate(float x, float y) 
{
	_x = x;
	_y = y;
}
int Coordinate::GetX()
{
	return _x;
}
int Coordinate::GetY()
{
	return _y;
}
