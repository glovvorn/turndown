#pragma once

#include "../maths/maths.h"

#include "shader.h"
#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "Renderer2d.h"

namespace turndown {
	namespace graphics {

		struct VertexData
		{
			maths::Vector3 vertex;
			//maths::Vector4 color;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			maths::Vector3 m_Position;
			maths::Vector2 m_Size;
			maths::Vector4 m_Color;
		protected:
			Renderable2D() {}
		public:
			Renderable2D(maths::Vector3 position, maths::Vector2 size, maths::Vector4 color)
				: m_Position(position), m_Size(size), m_Color(color)
			{ }

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}
			
			inline const maths::Vector3 getPosition() const { return m_Position; }
			inline const maths::Vector2 getSize() const { return m_Size; }
			inline const maths::Vector4 getColor() const { return m_Color; }
		};
	}
}