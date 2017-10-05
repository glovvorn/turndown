#include "shader.h"

namespace turndown {
	namespace graphics {

		Shader::Shader(const char* vertPath, const char* fragPath)
			: m_vertPath(vertPath), m_fragPath(fragPath)
		{
			m_ShaderID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::setUniform1f(const GLchar* name, float value)
		{
			return glUniform1f(getUniformLocation(name), value);
		}
		void Shader::setUniform1i(const GLchar* name, int value)
		{
			return glUniform1i(getUniformLocation(name), value);
		}
		void Shader::setUniform2f(const GLchar* name, const maths::Vector2& vector)
		{
			return glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}
		void Shader::setUniform3f(const GLchar* name, const maths::Vector3& vector)
		{
			return glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}
		void Shader::setUniform4f(const GLchar* name, const maths::Vector4& vector)
		{
			return glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}
		void Shader::setUniformMat4(const GLchar* name, const maths::matrix4& matrix)
		{
			return glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		GLuint Shader::load()
		{
			//TODO(greg): better error handling around shaders not compiling

			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
			
			std::string vertSourceString = FileUtils::read_file(m_vertPath);
			std::string fragSourceString = FileUtils::read_file(m_fragPath);

			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				//TODO(greg): proper logging
				std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				//TODO(greg): proper logging
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		void Shader::enable() const
		{
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}
	}
}