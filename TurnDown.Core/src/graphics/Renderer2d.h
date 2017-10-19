#pragma once

#include <vector>
#include <GL/glew.h>
#include "../maths/maths.h"


namespace turndown {
	namespace graphics {

		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<maths::matrix4> m_TransformationStack;
			const maths::matrix4 *m_TransformationBack;
		protected:
			Renderer2D()
			{
				m_TransformationStack.push_back(maths::matrix4::identity());
				m_TransformationBack = &m_TransformationStack.back();
			}
		public:
			void push(const maths::matrix4& matrix, bool overrideStack = false)
			{
				if (overrideStack)
				{
					m_TransformationStack.push_back(matrix);
				}
				else
				{
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
				}
				m_TransformationBack = &m_TransformationStack.back();
			}
			void pop()
			{
				// TODO(greg): add logging
				if (m_TransformationStack.size() > 1)
				{
					m_TransformationStack.pop_back();
				}
				m_TransformationBack = &m_TransformationStack.back();
			}

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void end() {}
			virtual void flush() = 0;
		};

	}
}