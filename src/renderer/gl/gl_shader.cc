//
// @authors {underdisk}
// License : LGPLv3
//

#include <vector>
#include "gl_shader.h"
#include "gl.h"

namespace wrench
{
	GLShader::GLShader()
	{
		m_GLProgram = glCreateProgram();
	}

	GLShader::~GLShader()
	{
		glDeleteProgram(m_GLProgram);
	}

	void GLShader::bind()
	{
		glUseProgram(m_GLProgram);
	}

	void GLShader::unbind()
	{
		glUseProgram(0);
	}

	Shader &GLShader::add_vertex_shader_by_string(const std::string& str)
	{
		compileGLShader(str, GL_VERTEX_SHADER);
		return *this;
	}

	Shader &GLShader::add_vertex_shader_by_file(const std::string& path)
	{
		std::string str;
		readFile(path, str);
		add_vertex_shader_by_string(str);
		return *this;
	}

	Shader &GLShader::add_fragment_shader_by_string(const std::string& str)
	{
		compileGLShader(str, GL_FRAGMENT_SHADER);
		return *this;
	}

	Shader &GLShader::add_fragment_shader_by_file(const std::string& path)
	{
		std::string str;
		readFile(path, str);
		add_fragment_shader_by_string(str);
		return *this;
	}

	void GLShader::compileGLShader(const std::string& source, unsigned type)
	{
		if(m_shaderMap.count(type))
			glDeleteShader(m_shaderMap[type]);
		m_shaderMap[type] = glCreateShader(type);

		unsigned& shader = m_shaderMap[type];

		const auto* source_c = static_cast<const GLchar*>(source.c_str());
		glShaderSource(shader, 1, &source_c, nullptr);
		glCompileShader(shader);

		GLint compiled {0};
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			GLint maxLength {0};
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> info(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, info.data());
			glDeleteShader(shader);
			m_shaderMap.erase(shader);
			throw std::runtime_error(info.data());
		}
	}

	void GLShader::link()
	{
		for (auto& shader : m_shaderMap)
		{
			glAttachShader(m_GLProgram, shader.second);
		}

		glLinkProgram(m_GLProgram);

		GLint linked {0};
		glGetProgramiv(m_GLProgram, GL_LINK_STATUS, (int*)&linked);
		if (linked == GL_FALSE)
		{
			GLint maxLength {0};
			glGetProgramiv(m_GLProgram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> info(maxLength);
			glGetProgramInfoLog(m_GLProgram, maxLength, &maxLength, info.data());
			glDeleteProgram(m_GLProgram);
			throw std::runtime_error(info.data());
		}

		//Detach shaders after linking
		for (auto& shader : m_shaderMap)
			glDetachShader(m_GLProgram, shader.second);

		m_shaderMap.clear();
	}
}