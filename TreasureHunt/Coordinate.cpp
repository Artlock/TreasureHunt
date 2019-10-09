#include "Coordinate.h"

Coordinate::Coordinate(int x, int y):_x(x),_y(y)
{

}
Coordinate::~Coordinate()
{

}
void Coordinate::changeCoordinate(int x, int y) 
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
