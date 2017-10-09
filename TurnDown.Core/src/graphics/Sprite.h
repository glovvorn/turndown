#pragma once

#include "renderable2d.h"

namespace turndown {
	namespace graphics {
		
		class Sprite : public Renderable2D
		{
		private:

		public:
			Sprite(float x, float y, float width, float height, const maths::Vector4 &color);
		};

	}
}