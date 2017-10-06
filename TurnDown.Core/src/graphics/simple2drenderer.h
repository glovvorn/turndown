#pragma once

#include <deque>
#include "Renderer2d.h"

namespace turndown {
	namespace graphics {

		class Simple2DRenderer: public Renderer2D
		{
		private:
			std::deque<const Renderable2D&> m_RenderQueue;
		public:
			void submit(const Renderable2D& renderable) override;
			void flush() override;
		};

	}
}