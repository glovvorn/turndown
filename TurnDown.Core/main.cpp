#include <iostream>
#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

//#include "src/graphics/buffers/buffer.h"
//#include "src/graphics/buffers/indexbuffer.h"
//#include "src/graphics/buffers/vertexarray.h"

//#include "src/graphics/Renderer2d.h"
//#include "src/graphics/simple2drenderer.h"
#include "src/graphics/BatchRenderer2d.h"

#include "src/graphics/Sprite.h"
#include "src/graphics/StaticSprite.h"
#include "src/utils/timer.h"

#include <time.h>

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

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));

	Sprite sprite(5, 5, 4, 4, maths::Vector4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, maths::Vector4(0.2f, 0, 1, 1));
	BatchRenderer2d renderer;

	for (float y = 0; y < 9.0f; y+= 0.05f)
	{
		for (float x = 0; x < 16.0f; x+= 0.05f)
		{
			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, maths::Vector4(rand() % 1000 / 1000.0f, 1, 1, 1)));
		}
	}

	shader.setUniform2f("light_pos", Vector2(8.0f, 4.5f));
	shader.setUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	Timer timer;
	float time = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.Clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Vector2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		renderer.begin();

		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}

		renderer.end();
		renderer.flush();
		window.Update();
		
		frames++;
		if (timer.elapsed() - time > 1.0f)
		{
			time += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
		//printf("%f ms\n", timer.elapsed() * 1000.0f);
	}

	return 0;
}

