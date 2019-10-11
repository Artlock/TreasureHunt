#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player;
class Coordinate;
class WindowManager
{
private:
	Player* _Player = NULL;
	sf::RenderWindow* _Window = NULL;
	Coordinate* _OffSet = NULL;
	sf::Vector2i* _OldPositionWindow = NULL;
	sf::Vector2i* _FirstPositionWindow = NULL;

public:
	WindowManager(sf::RenderWindow* Window, Player* Player);
	~WindowManager();
	void UpdateWindow();
	Coordinate* GetOffSet();
};

