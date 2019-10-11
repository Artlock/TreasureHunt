#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>

#define DEVICE_WIDTH 768 // 16 * 48 pixels
#define DEVICE_HEIGHT 384 // 16 * 24 pixels

#define TO_DISPLAY 1153 // 1152 (= 48 * 24 tiles) + 1 player

#define END_DELAY 5

class SpriteSheet;
class Map;
class Player;
class Drawable;
class Zombie;

class Device
{
public:
	Device(const char* const title);
	~Device();

	void run();
	void quit();
	void addDrawable(int sprite, int posX, int posY, int scale, int layer, int flipH = 0, int flipV = 0, int flipD = 0);
	void GetDesktopResolution(int& horizontal, int& vertical);

	bool hasWin = false;

	// Inline methods because short
	inline float getDeltaTime() { return _deltaTime; };
	inline sf::RenderWindow* getWindow() { return _window; };

	sf::RenderWindow* lifeBar = NULL;

private:
	sf::RenderWindow* _window = NULL;


	sf::Clock* _clock = NULL;

	sf::Font myFont;

	sf::Text goText;
	sf::Text winText;

	SpriteSheet* _spriteSheet = NULL;

	Map* _map = NULL;

	Player* _player = NULL;

	Zombie* _zombie = NULL;

	std::vector<Drawable*> _toRender;

	bool _isRunning = false;
	bool createWindow = false;


	float _deltaTime = 0.0f;
	float timer = 0;

	void clearDrawables();
	void sortDrawables();
	void drawAll();
};
