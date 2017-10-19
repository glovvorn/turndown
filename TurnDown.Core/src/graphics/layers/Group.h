#pragma once

#include "../renderable2d.h"

namespace turndown {
	namespace graphics {

		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_Renderables;
			maths::matrix4 m_TransformationMatrix;
		public:
			Group(const maths::matrix4& transform);
			void add(Renderable2D* renderable);
			void submit(Renderer2D* renderer) const override;
		};

	}
}