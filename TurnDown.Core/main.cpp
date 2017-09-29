#include <iostream>
#include "src/graphics/window.h"


int main()
{
	using namespace turndown;
	using namespace graphics;

	Window window("Turn Down", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	while (!window.closed())
	{
		window.Clear();
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.Update();
	}

	return 0;
}

