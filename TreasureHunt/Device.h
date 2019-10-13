#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>

#define DEVICE_WIDTH 150 
#define DEVICE_HEIGHT 150 

#define INITIAL_POS_WINDOW_WIDTH DEVICE_WIDTH/2
#define INITIAL_POS_WINDOW_HEIGHT DEVICE_HEIGHT/2

#define MAP_WIDTH 768 // 16 * 48 pixels 
#define MAP_HEIGHT 384 // 16 * 24 pixels

#define TILE_SIZE 16

#define TO_DISPLAY 1153 // 1152 (= 48 * 24 tiles) + 1 player

#define MAX_FRAMERATE 144

#define END_DELAY 5

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
	float timer = 0;

	void clearDrawables();
	void sortDrawables();
	void drawAll();
};
