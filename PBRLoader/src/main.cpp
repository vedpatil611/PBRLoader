#include "Window.h"

int main()
{
	Window* window = new Window();

	while (!window->shouldClose())
	{
		window->pollEvents();
		window->swapBuffer();
	}

	delete window;
	return 0;
}
