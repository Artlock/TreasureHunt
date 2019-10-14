#include "OPTIONS.h"

#include "Device.h"
#include "SpriteSheet.h"
#include "Map.h"
#include "Player.h"
#include "Drawable.h"
#include "Zombie.h"
#include "Colliders.h"
#include "WindowManager.h"
#include "TreasureManager.h"

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
	_window = new sf::RenderWindow(sf::VideoMode(DEVICE_WIDTH, DEVICE_HEIGHT), title, sf::Style::None);

	// Limit framerate and set vsync
	//_window->setVerticalSyncEnabled(true);
	_window->setFramerateLimit(MAX_FRAMERATE);

	// Set window position
	_window->setPosition(sf::Vector2i(INITIAL_POS_WINDOW_WIDTH, INITIAL_POS_WINDOW_HEIGHT));

	// Create a clock for later
	_clock = new sf::Clock();

	// Our spritesheet
	_spriteSheet = new SpriteSheet(this, GetExePath() + "Assets/colored_transparent.png");

	// Our treasure
	_treasureManager = new TreasureManager(this, GetExePath() + "Assets/treasure.txt");

	// Our colliders
	_colliders = new Colliders(GetExePath() + "Assets/collider.txt");
	_colliders->MakeList(SC_TILE_SIZE_XY);

	// Our map
	_map = new Map(this, GetExePath() + "Assets/sample_fantasy.txt", GetExePath() + "Assets/roofs.txt", GetExePath() + "Assets/layer0.txt");

	// Our player
	_player = new Player(this, _colliders, GetExePath() + "Assets/player.txt");

	// Our Zombie
	_zombie = new Zombie(_player, this, GetExePath() + "Assets/zombie.txt");

	// Our WindowManager
	_windowManager = new WindowManager(_window, _player);

	// The list that will keep track of the drawing order
	_toRender = std::vector<Drawable*>(TO_RENDER);

	// Load the font
	bool loadResult = myFont.loadFromFile(GetExePath() + "Assets/DejaVuSans.ttf");
	if (!loadResult)
	{
		// Error
		sf::err();
	}
	//std::cout << GetExePath() + "Assets/DejaVuSans.ttf" << std::endl;

	// Initiate Start Text
	startText.setString("Find the diamond and avoid the ghost!");
	startText.setFont(myFont);
	startText.setCharacterSize(30);
	startText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	startText.setFillColor(sf::Color::Blue);

	// Initiate GameOver Text
	goText.setString("You Lose!");
	goText.setFont(myFont);
	goText.setCharacterSize(30);
	goText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	goText.setFillColor(sf::Color::Red);

	// Initiate Win Text
	winText.setString("You Win!");
	winText.setFont(myFont);
	winText.setCharacterSize(30);
	winText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	winText.setFillColor(sf::Color::Red);

	// Player Lifebar
	int horizontal = 0;
	int vertical = 0;
	GetDesktopResolution(horizontal, vertical);
	//std::cout << horizontal << " " << vertical << std::endl;
	lifeBar = new sf::RenderWindow(sf::VideoMode(_player->_pLife * 5, 50), "Lifebar", sf::Style::None);
	lifeBar->setPosition(sf::Vector2i(horizontal - 550, vertical - 100));
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
		_toRender[i]->Draw(_spriteSheet, _windowManager->GetOffSet());
	}
}

void Device::run()
{
	// State and timer for deltaTime
	_isRunning = true;
	_clock->restart();

	sf::Event event;

	// Play startup text
	sf::RenderWindow* startWindow = new sf::RenderWindow(sf::VideoMode(700, 80), "Welcome");
	startWindow->clear(sf::Color::White);
	startWindow->draw(startText);
	startWindow->display();

	// Game loop
	while (_isRunning)
	{
		// Save deltaTime for usage with player
		_deltaTime = _clock->restart().asSeconds();

		//std::cout << "Delta Time : " << _deltaTime << std::endl;

		if (startWindow != NULL)
		{
			timer_start += _deltaTime;
			if (timer_start >= START_OF_GAME_DELAY)
			{
				startWindow->close();
				startWindow = NULL;
			}
		}

		// Manage events
		while (_window->pollEvent(event))
		{
			// Close the window if needed
			if (event.type == sf::Event::Closed)
				quit();
		}

		if (_player->isDead() && !createWindow) {
			std::cout << "You're DEAD!\n";
			sf::RenderWindow* endWindow = new sf::RenderWindow(sf::VideoMode(200, 80), "The End");
			createWindow = true;
			endWindow->clear(sf::Color::White);
			endWindow->draw(goText);
			endWindow->display();
		}

		if (hasWin && !createWindow) {
			std::cout << "You've WON!\n";
			sf::RenderWindow* endWindow = new sf::RenderWindow(sf::VideoMode(200, 80), "The End");
			createWindow = true;
			endWindow->clear(sf::Color::White);
			endWindow->draw(winText);
			endWindow->display();
		}

		if (createWindow) {
			timer_end += _deltaTime;
			if (timer_end >= END_OF_GAME_DELAY)
				quit();
		}

		// Manage user inputs here
		if (!_player->isDead()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				_player->move(-1.0f, 0.0f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_player->move(1.0f, 0.0f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				_player->move(0.0f, -1.0f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				_player->move(0.0f, 1.0f);
		}

		// Move zombie on keyboard press
		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			_zombie->ZombieMove();
		*/

		// Clear the window with our background color
		_window->clear(sf::Color(71, 45, 60, 255));

		// Clear the list of items to draw
		clearDrawables();

		// Add map to list of objects to display
		_map->displayMap(SC_TILE_SIZE_XY);

		// Add treasure to list of objects to display
		_treasureManager->displayTreasure();

		// Add player to list of objects to display
		_player->displayPlayer();

		// Add zombie to list of objects to display after moving it towards the player
		_zombie->ZombieMove();
		_zombie->ZombieDraw();

		// Update window
		_windowManager->UpdateWindow();

		// Sort all there is to draw and draw it
		sortDrawables();
		drawAll();

		// Display the window's content
		_window->display();

		// Check finish
		if (_treasureManager->checkTreasure(_player->getPosX(), _player->getPosY()))
		{
			hasWin = true;
		}

		// Update lifebar
		lifeBar->clear(sf::Color::Red);
		lifeBar->display();
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

// Get the horizontal and vertical screen sizes in pixel
void Device::GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
