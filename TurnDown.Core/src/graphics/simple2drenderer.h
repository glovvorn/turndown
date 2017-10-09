#pragma once

#include <deque>
#include "Renderer2d.h"
#include "StaticSprite.h"

namespace turndown {
	namespace graphics {

		class Simple2DRenderer: public Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_RenderQueue;
		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};

	}
}