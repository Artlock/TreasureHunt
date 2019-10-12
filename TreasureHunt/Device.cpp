#include "Device.h"
#include "SpriteSheet.h"
#include "Map.h"
#include "Player.h"
#include "Drawable.h"
#include "Zombie.h"
#include "Colliders.h"

#include <iostream>
#include <Windows.h>
#include <algorithm>

std::string GetExePath()
{
	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256); // Get path of .exe
	std::string exeFilePath = cExeFilePath; // Copy of string (By value, not reference)
	size_t exeNamePos = exeFilePath.find_last_of("\\/"); // Finds first of \ or /
	std::string exePath = exeFilePath.substr(0, exeNamePos + 1); // Get exe folder path from full exe path (+ 1 since position is - 1 relative to length)
	return exePath;
}

// Constructor
Device::Device(const char* const title)
{
	// Our window
	_window = new sf::RenderWindow(sf::VideoMode(DEVICE_WIDTH, DEVICE_HEIGHT), title);
	_window->setVerticalSyncEnabled(true);
	_window->setFramerateLimit(MAX_FRAMERATE);

	_clock = new sf::Clock();

	// Our spritesheet
	_spriteSheet = new SpriteSheet(this, GetExePath() + "Assets/colored.png");

	// Our colliders
	_colliders = new Colliders(GetExePath() + "Assets/collider.txt");
	_colliders->MakeList(SC_TILE_SIZE_XY);

	// Our map
	_map = new Map(this, GetExePath() + "Assets/sample_fantasy.txt", GetExePath() + "Assets/roofs.txt", GetExePath() + "Assets/layer0.txt");

	// Our player
	_player = new Player(this, _colliders, GetExePath() + "Assets/player.txt");

	// Our Zombie
	_zombie = new Zombie(_player, this, GetExePath() + "Assets/zombie.txt");

	// The list that will keep track of the drawing order
	_toRender = std::vector<Drawable*>(TO_DISPLAY);
}

// Destructor
Device::~Device()
{
	if (_window != NULL)
		delete _window;
	_window = NULL;

	if (_clock != NULL)
		delete _clock;
	_clock = NULL;

	if (_spriteSheet != NULL)
		delete _spriteSheet;
	_spriteSheet = NULL;

	if (_map != NULL)
		delete _map;
	_map = NULL;

	if (_player != NULL)
		delete _player;
	_player = NULL;

	if (_zombie != NULL) {
		delete _zombie;
	}
	_zombie = NULL;
}

void Device::clearDrawables()
{
	// Uses lambda expression ([] does not capture anything)
	std::for_each(_toRender.begin(), _toRender.end(), [](Drawable* drw)
		{
			delete drw;
		});
	// Equivalent to
	// for (Drawable* drw : _toRender) delete drw;

	_toRender.clear();
}

void Device::addDrawable(int sprite, int posX, int posY, int scale, int layer, int posDrawAfterY, int flipH, int flipV, int flipD)
{
	_toRender.push_back(new Drawable(sprite, posX, posY, scale, layer, posDrawAfterY, flipH, flipV, flipD));
}

void Device::sortDrawables()
{
	std::sort(_toRender.begin(), _toRender.end(), [&](Drawable* dr, Drawable* dr2)
		{
			if (dr->getLayer() != dr2->getLayer()) // Different layer
				return dr->getLayer() < dr2->getLayer(); // Smaller layer displays first
			else // Same layer
				return dr->getPosDrawAfterY() < dr2->getPosDrawAfterY();
		});
}

void Device::drawAll()
{
	for (int i = 0; i < _toRender.size(); i++)
	{
		_toRender[i]->Draw(_spriteSheet);
	}
}

void Device::run()
{
	// State and timer for deltaTime
	_isRunning = true;
	_clock->restart();

	sf::Event event;

	// Game loop
	while (_isRunning)
	{
		// Save deltaTime for usage with player
		_deltaTime = _clock->restart().asSeconds();

		//std::cout << "Delta Time : " << _deltaTime << std::endl;

		// Manage events
		while (_window->pollEvent(event))
		{
			// Close the window if needed
			if (event.type == sf::Event::Closed)
				quit();
		}

		// Manage user inputs here
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			_player->move(-1.0f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			_player->move(1.0f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			_player->move(0.0f, -1.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			_player->move(0.0f, 1.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			_zombie->ZombieMove();

		// Clear the window with black
		_window->clear(sf::Color::Black);

		// Clear the list of items to draw
		clearDrawables();

		// Add map to list of objects to display
		_map->displayMap(SC_TILE_SIZE_XY);

		/// Add player to list of objects to display
		_player->displayPlayer();

		// Add zombie to list of objects to display
		// _zombie->ZombieMove();
		_zombie->ZombieDraw();

		// Sort all there is to draw and draw it
		sortDrawables();
		drawAll();

		// Display the window's content
		_window->display();
	}

	// Close the window
	if (_window != NULL)
		_window->close();
}

// Quit the game loop
void Device::quit()
{
	_isRunning = false;
}
