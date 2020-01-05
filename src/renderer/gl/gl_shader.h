//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <unordered_map>
#include "../common/shader.h"

namespace wrench::gl {

	/**
	* @brief Implementation of a Shader for the OpenGL Shading Language (GLSL)
	*/
	class GLShader final : public Shader
	{
	public:
		GLShader();

		~GLShader() override ;

		void bind() const override;

		void unbind() const override;

		void link() override;

		Shader& add_vertex_shader_by_string(const std::string& str) override;

		Shader& add_vertex_shader_by_file(const std::string& path) override;

		Shader& add_fragment_shader_by_string(const std::string& str) override;

		Shader& add_fragment_shader_by_file(const std::string& path) override;

	private:
		unsigned m_GLProgram;
		std::unordered_map<unsigned, unsigned> m_shaderMap;

		void compileGLShader(const std::string& source, unsigned type);
	};
}