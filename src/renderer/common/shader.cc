//
// @authors {underdisk}
// License : LGPLv3
//

#include "shader.h"
#include <fstream>
#include <string>

namespace wrench {

	void Shader::bind()
	{

	}

	void Shader::unbind()
	{

	}

	Shader &Shader::add_vertex_shader_by_string(const std::string &str)
	{
		return *this;
	}

	Shader &Shader::add_vertex_shader_by_file(const std::string &path)
	{
		return *this;
	}

	Shader &Shader::add_fragment_shader_by_string(const std::string &str)
	{
		return *this;
	}

	Shader &Shader::add_fragment_shader_by_file(const std::string &path)
	{
		return *this;
	}

	void Shader::readFile(const std::string& path, std::string& buf)
	{
		std::ifstream file(path);

		file.seekg(0, std::ios::end);
		buf.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		buf.assign((std::istreambuf_iterator<char>(file)),
				   std::istreambuf_iterator<char>());
	}

	void Shader::link()
	{

	}
}
