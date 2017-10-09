#include <iostream>
#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/Renderer2d.h"
#include "src/graphics/simple2drenderer.h"

int main()
{
	using namespace turndown;
	using namespace graphics;
	using namespace maths;

	Window window("Turn Down", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	matrix4 ortho = matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", matrix4::translation(Vector3(4, 3, 0)));

	Renderable2D sprite(maths::Vector3(5, 5, 0), maths::Vector2(4, 4), maths::Vector4(1, 0, 1, 1), shader);
	Renderable2D sprite2(maths::Vector3(7, 1, 0), maths::Vector2(2, 3), maths::Vector4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;

	shader.setUniform2f("light_pos", Vector2(8.0f, 4.5f));
	shader.setUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.Clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Vector2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();

		window.Update();
	}

	return 0;
}

