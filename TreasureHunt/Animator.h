#pragma once

#include <string>

#define ANIMATOR_FRAMES 2 // 2 images per second
#define ANIMATOR_SPEED 2 // Timescale of the animation

class SpriteSheet;

class Animator
{
public:
	Animator(std::string path, int totalFrames);
	~Animator();

	inline int getCurrentSprite() { return _animationSprites[_currentStep]; }

	void Step(float delta);
	void Reset();

private:
	int* _animationSprites = NULL;

	int _totalFrames = 0;

	float _currentDelta = 0;
	int _currentStep = 0;
};
