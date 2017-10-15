#include "BatchRenderer2d.h"

namespace turndown {
	namespace graphics {

		BatchRenderer2d::BatchRenderer2d()
		{
			init();
		}

		BatchRenderer2d::~BatchRenderer2d()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2d::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint *indicies = new GLuint[RENDERER_INDICIES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICIES_SIZE; i+= 6)
			{
				indicies[ i ] = offset + 0;
				indicies[i+1] = offset + 1;
				indicies[i+2] = offset + 2;
				
				indicies[i+3] = offset + 2;
				indicies[i+4] = offset + 3;
				indicies[i+5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indicies, RENDERER_INDICIES_SIZE);

			glBindVertexArray(0);
		}

		void BatchRenderer2d::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2d::submit(const Renderable2D* renderable)
		{
			const maths::Vector3& position = renderable->getPosition();
			const maths::Vector2& size = renderable->getSize();
			const maths::Vector4& color = renderable->getColor();

			int r = (int)(color.x * 255.0f);
			int g = (int)(color.y * 255.0f);
			int b = (int)(color.z * 255.0f);
			int a = (int)(color.w * 255.0f);

			unsigned int c = a << 24 | b << 16 | g << 8 | r << 0;

			m_Buffer->vertex = position;
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::Vector3(position.x, position.y + size.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::Vector3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::Vector3(position.x + size.x, position.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_indexCount += 6;
		}

		void BatchRenderer2d::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2d::flush()
		{
			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_indexCount = 0;
		}

	}
}