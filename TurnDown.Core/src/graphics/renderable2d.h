#pragma once

#include "../maths/maths.h"

#include "shader.h"
#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

namespace turndown {
	namespace graphics {

		class Renderable2D
		{
		protected:
			maths::Vector3 m_Position;
			maths::Vector2 m_Size;
			maths::Vector4 m_Color;

			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			Shader& m_Shader;
		public:
			Renderable2D(maths::Vector3 position, maths::Vector2 size, maths::Vector4 color, Shader& shader)
				: m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
			{
				m_VertexArray = new VertexArray();
				GLfloat vertices[] =
				{
					0, 0, 0,
					0, size.y, 0,
					size.x, size.y, 0,
					size.x, 0, 0
				};

				GLfloat colors[] =
				{
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w
				};

				m_VertexArray->addBuffer(new Buffer(vertices, 3 * 4, 3), 0);
				m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLushort indicies[] = { 0, 1, 2, 2, 3, 0 };
				m_IndexBuffer = new IndexBuffer(indicies, 6);
			}

			~Renderable2D()
			{
				delete m_VertexArray;
				delete m_IndexBuffer;
			}
			
			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }

			inline Shader& getShader() const { return m_Shader; }

			inline const maths::Vector3 getPosition() const { return m_Position; }
			inline const maths::Vector2 getSize() const { return m_Size; }
			inline const maths::Vector4 getColor() const { return m_Color; }
		};
	}
}