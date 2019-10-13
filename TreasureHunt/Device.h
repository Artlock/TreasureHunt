#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>

class SpriteSheet;
class Map;
class Player;
class Drawable;
class Zombie;
class Colliders;
class WindowManager;
class TreasureManager;

class Device
{
public:
	Device(const char* const title);
	~Device();

	void run();
	void quit();

	void addDrawable(int sprite, int posX, int posY, int scale, int layer, int posDrawAfterY, int flipH = 0, int flipV = 0, int flipD = 0);

	void GetDesktopResolution(int& horizontal, int& vertical);

	bool hasWin = false;

	// Inline methods because short
	inline float getDeltaTime() { return _deltaTime; };
	inline sf::RenderWindow* getWindow() { return _window; };

	sf::RenderWindow* lifeBar = NULL;

private:
	sf::RenderWindow* _window = NULL;

	WindowManager* _windowManager = NULL;

	sf::Clock* _clock = NULL;

	sf::Font myFont;
	sf::Text startText;
	sf::Text goText;
	sf::Text winText;

	SpriteSheet* _spriteSheet = NULL;
	TreasureManager* _treasureManager = NULL;
	Colliders* _colliders = NULL;
	Map* _map = NULL;
	Player* _player = NULL;
	Zombie* _zombie = NULL;

	std::vector<Drawable*> _toRender;

	bool _isRunning = false;
	bool createWindow = false;


	float _deltaTime = 0.0f;

	float timer_start = 0.0f;
	float timer_end = 0.0f;

	void clearDrawables();
	void sortDrawables();
	void drawAll();
};
