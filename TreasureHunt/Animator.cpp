#include "OPTIONS.h"

#include "Animator.h"
#include "FileToArray.h"

#include <fstream>

Animator::Animator(std::string path, int totalFrames) : _totalFrames(totalFrames)
{
	FileToArray<int>::ReadFileTo_Array_1D(path, totalFrames, _animationSprites);
}

Animator::~Animator()
{
	delete[] _animationSprites;
	_animationSprites = NULL;
}

void Animator::Step(float delta)
{
	_currentDelta += delta;

	float delayBetweenFrames = 1.0f / (float)(ANIMATOR_FRAMES * ANIMATOR_SPEED);
	while (_currentDelta > delayBetweenFrames)
	{
		_currentDelta -= delayBetweenFrames;

		_currentStep = ++_currentStep % _totalFrames;
	}

	// Autre methode: STEP = (FRAMERATE * TEMPS) % FRAMES
}

void Animator::Reset()
{
	_currentDelta = 0.0f;
	_currentStep = 0;
}