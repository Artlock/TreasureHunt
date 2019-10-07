#include "Animator.h"

#include <fstream>

Animator::Animator(std::string path, int totalFrames) : _totalFrames(totalFrames)
{
	_animationSprites = new int[totalFrames];
	memset(_animationSprites, 0, sizeof(int) * totalFrames);

	// ifsteam/ofstream == IO read write streams, fstream does both
	// Open the file on the stream
	std::ifstream mapStream(path);

	// Read the file containing the animation's tile values

	std::string line = "";
	std::string strTileIndex = "";

	size_t endPos = 0;
	int tileX = 0;

	std::getline(mapStream, line);

	// npos equals -1, which means the maximum value for its containing type, unsigned long long / unsigned __int64
	while (endPos != std::string::npos) // Npos means not found
	{
		endPos = line.find_first_of(","); // Returns npos if nothing is found
		strTileIndex = line.substr(0, endPos); // Substrings left of endPos (From some position for some amount of chars)

		if (strTileIndex.length() > 0) // Only proceed if there is a value to work on
		{
			line = line.substr(endPos + (size_t)1); // Substrings right from endPos (From some positon until the end)
			_animationSprites[tileX] = std::stoul(strTileIndex); // Assign left substring as unsigned long
			tileX++;
		}
		else if (endPos != std::string::npos)
		{
			// Avoid getting stuck if some middle value is empty instead of having a number
			// For instance if we have a ...1,2,,4,5... sequence, the ,, is problematic and would cause an infinite loop without this
			line = line.substr(endPos + (size_t)1);
			_animationSprites[tileX] = 0;
			tileX++;
		}
	}
}

Animator::~Animator()
{
	delete[] _animationSprites;
	_animationSprites = NULL;
}

void Animator::Step(float delta)
{
	_currentDelta += delta;

	float delayBetweenFrames = 1.0f / (float) (ANIMATOR_FRAMES * ANIMATOR_SPEED);
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