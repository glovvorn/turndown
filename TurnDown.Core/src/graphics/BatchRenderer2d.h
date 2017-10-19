#pragma once

#include "Renderer2d.h"
#include "buffers\vertexarray.h"
#include <cstddef>
#include "renderable2d.h"

namespace turndown {
	namespace graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICIES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX		0
#define SHADER_COLOR_INDEX		1

		class BatchRenderer2d : public Renderer2D
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLsizei m_indexCount;
			VertexData *m_Buffer;
		public:
			BatchRenderer2d();
			~BatchRenderer2d();
			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void end() override;
			void flush() override;
		private:
			void init();
		};

	}
}