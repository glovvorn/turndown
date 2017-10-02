#include <iostream>
#include "src/graphics/window.h"
#include "src/maths/maths.h"

int main()
{
	using namespace turndown;
	using namespace graphics;
	using namespace maths;

	Window window("Turn Down", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	Vector3 a(1, 7, 9);
	Vector3 b(0, 1, 0);

	Vector3 c = a + b;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;

	matrix4 position = matrix4::translation(Vector3(2, 3, 4));
	position *= matrix4::identity();

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

