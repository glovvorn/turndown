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

#include "src/graphics/layers/TileLayer.h"

#include <time.h>

int main()
{
	using namespace turndown;
	using namespace graphics;
	using namespace maths;

	const int WINDOW_WIDTH = 960;
	const int WINDOW_HEIGHT = 540;

	Window window("Turn Down", WINDOW_WIDTH, WINDOW_HEIGHT);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Shader *s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	Shader *s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader2 = *s2;
	shader2.enable();
	
	shader.setUniform2f("light_pos", Vector2(8.0f, 4.5f));
	
	TileLayer layer(&shader);
	
	for (float y = -9.0f; y < 9.0f; y += 0.1f)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1f)
		{
			layer.add(new Sprite(x, y, 0.08f, 0.08f, maths::Vector4(rand() % 1000 / 1000.0f, 1.0f, 1.0f, 1.0f)));
		}
	}
	
	TileLayer layer2(&shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, maths::Vector4(0, 0, 1, 1.0f)));

	Timer timer;
	float time = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.Clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", Vector2((float)(x * 32.0f / (float)window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / (float)window.getHeight())));
		shader2.enable();
		shader2.setUniform2f("light_pos", Vector2((float)(x * 32.0f / (float)window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / (float)window.getHeight())));
		
		layer.render();
		layer2.render();

		window.Update();
		
		frames++;
		if (timer.elapsed() - time > 1.0f)
		{
			time += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	return 0;
}

