// TreasureHunt.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Device.h"

#include <iostream>

int main()
{
	// Create device
	Device* device = new Device("My Game");

	// Start game loop
	device->run();

	// Delete device once the game loop is over
	delete device;
	device = NULL;
}
