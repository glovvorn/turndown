#include "Sprite.h"

namespace turndown {
	namespace graphics {

		Sprite::Sprite(float x, float y, float width, float height, const maths::Vector4 &color)
			: Renderable2D(maths::Vector3(x, y, 0), maths::Vector2(width, height), color)
		{

		}
	}
}