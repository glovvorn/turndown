#pragma once

#include <GL/glew.h>
#include <vector>
#include "../utils/fileutils.h"
#include "../maths/maths.h"

#include <iostream>

namespace turndown {
	namespace graphics {

		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char *m_vertPath;
			const char *m_fragPath;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const maths::Vector2& vector);
			void setUniform3f(const GLchar* name, const maths::Vector3& vector);
			void setUniform4f(const GLchar* name, const maths::Vector4& vector);
			void setUniformMat4(const GLchar* name, const maths::matrix4& matrix);

			void enable() const;
			void disable() const;
		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};
	}
}