#pragma once

#include "../Renderer2d.h"
#include "../renderable2d.h"

namespace turndown {
	namespace graphics {
		class Layer {
		protected:
			Renderer2D *m_Renderer;
			std::vector<Renderable2D*> m_Renderables;
			Shader *m_Shader;
			maths::matrix4 m_ProjectionMatrix;
			//TODO(greg): add camera to layer
		protected:
			Layer(Renderer2D *renderer, Shader *shader, maths::matrix4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D *renderable);
			virtual void render();
		};
	}
}