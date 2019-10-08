void ChangeWindow(windowRenderer* window, int playerX, int playerY, int windowW, int windowH) 
{
	int WindowX = playerX - windowW / 2;
	int WindowY = playerY - windowH / 2;
	if (WindowX < 0) {
		WindowX = 0;
	}
	if (WindowY < 0) {
		WindowY = 0;
	}

	window.setPosition(sf::Vector2i(windowX, windowW));
}