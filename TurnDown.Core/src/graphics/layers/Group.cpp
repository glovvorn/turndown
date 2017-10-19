#include "Group.h"

namespace turndown {
	namespace graphics {

		Group::Group(const maths::matrix4& transform)
			: m_TransformationMatrix(transform)
		{
		}

		void Group::add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Group::submit(Renderer2D *renderer) const
		{
			renderer->push(m_TransformationMatrix);
			for (const Renderable2D* renderable : m_Renderables)
			{
				renderable->submit(renderer);
			}
			renderer->pop();
		}

	}
}