#include "TileLayer.h"

namespace turndown {
	namespace graphics {

		TileLayer::TileLayer(Shader *shader)
			: Layer(new BatchRenderer2d(), shader, maths::matrix4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
		{

		}

		TileLayer::~TileLayer()
		{

		}
	}
}