#include "Zombie.h"
#include "Device.h"
#include "Player.h"
#include "Animator.h"

Zombie::Zombie(Player* player, Device* device, std::string path)
	: _player(player), _device(device)
{
	_animator = new Animator(path, Z_ANIMATION_FRAME);
}


Zombie::~Zombie()
{
	if (_player != NULL) {
		delete _player;
	}
	_player = NULL;

	if (_animator != NULL) {
		delete _animator;
	}
	_animator = NULL;
}

void Zombie::ZombieMove()
{
	float _playerPosX = _player->getPosX();
	float _playerPosY = _player->getPosY();

	_playerPos = sf::Vector2f(_playerPosX, _playerPosY);
	zombiePosition = sf::Vector2f(xPos, yPos);

	direction = _playerPos - zombiePosition;
	normalizedDir = direction / sqrt((direction.x * direction.x) + (direction.y * direction.y));

	_isMoving = true;

	speed = Z_SPEED * _device->getDeltaTime();

	xPos = xPos + normalizedDir.x * speed;
	yPos = yPos + normalizedDir.y * speed;

	sf::Vector2f currentSpeed = normalizedDir * speed;
}

void Zombie::ZombieDraw() 
{
	int toDraw = 0;

	if (_isMoving) {
		_animator->Step(_device->getDeltaTime());
		toDraw = _animator->getCurrentSprite();
		_isMoving = false;
	}
	else {
		_animator->Reset();
		toDraw = Z_INDEX;
		_device->addDrawable(toDraw, xPos, yPos, Z_SCALE, 1, false, 0, 0);
	}
}


