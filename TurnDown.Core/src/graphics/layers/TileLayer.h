#pragma once

#include "layer.h"
#include "../BatchRenderer2d.h"

namespace turndown {
	namespace graphics {
		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader *shader);
			virtual ~TileLayer();
		};
	}
}