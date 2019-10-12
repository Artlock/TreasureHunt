#include "WindowManager.h"
#include "Coordinate.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

WindowManager::WindowManager(sf::RenderWindow* Window, Player* Player) : _Window(Window), _Player(Player)
{
	_OffSet = new Coordinate(0, 0);
	_OldPositionWindow = new sf::Vector2i(0, 0);
	_OldPositionWindow->x = _Window->getPosition().x;
	_OldPositionWindow->y = _Window->getPosition().y;
	_FirstPositionWindow = new sf::Vector2i(_Window->getPosition().x + _Player->getPosX() + PLAYER_SIZE_W/2 - _Window->getSize().x / 2, _Window->getPosition().y + _Player->getPosY() + PLAYER_SIZE_Y/2  - _Window->getSize().y / 2);
	_Window->setPosition(*_FirstPositionWindow);
	_OffSet->changeCoordinate(_Window->getPosition().x - _OldPositionWindow->x, _Window->getPosition().y - _OldPositionWindow->y);
}
WindowManager::~WindowManager()
{

}
void WindowManager::UpdateWindow()
{
	*_OldPositionWindow = _Window->getPosition();
	_Window->setPosition(sf::Vector2i(_FirstPositionWindow->x + _Player->getPosX(), _FirstPositionWindow->y + _Player->getPosY()));
	_OffSet->changeCoordinate(_OffSet->GetX() + (_Window->getPosition().x - _OldPositionWindow->x), _OffSet->GetY() + (_Window->getPosition().y - _OldPositionWindow->y));
}
Coordinate* WindowManager::GetOffSet()
{
	return _OffSet;
}