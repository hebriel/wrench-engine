//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <string>
#include <glm/glm.hpp>

namespace wrench {

	/**
	* @brief Abstract representation for a Shader Program
	*
	* You might want to use implementations of this class such as GLShader
	*/
	class Shader
	{
	public:

		/**
		* @brief Default constructor
		*/
		Shader() = default;

		/**
		* @brief Default destructor
		*/
		virtual ~Shader() = default;

		/**
		* @brief Bind the shader program
		*/
		virtual void bind() const;

		/**
		* @brief Unbind any shader program
		*/
		virtual void unbind() const;

		/**
		* @brief Link the shader program
		*/
		virtual void link();

		/**
		* @brief Compile a vertex shader by providing a string
		*
		* @param str Constant reference to a vertex shader source
		*
		* @return Reference to the own object for chain calling
		*/
		virtual Shader& add_vertex_shader_by_string(const std::string& str);

		/**
		* @brief Compile a vertex shader by providing a file path
		*
		* @param path Constant reference to a vertex shader file path
		*
		* @return Reference to the own object for chain calling
		*/
		virtual Shader& add_vertex_shader_by_file(const std::string& path);

		/**
		* @brief Compile a fragment shader by providing a string
		*
		* @param str Constant reference to a fragment shader source
		*
		* @return Reference to the own object for chain calling
		*/
		virtual Shader& add_fragment_shader_by_string(const std::string& str);

		/**
		* @brief Compile a fragment shader by providing a file path
		*
		* @param path Constant reference to a fragment shader file path
		*
		* @return Reference to the own object for chain calling
		*/
		virtual Shader& add_fragment_shader_by_file(const std::string& path);

		/**
		* @brief Set a float uniform value
		*/
		virtual void set_uniform(const char* name, float value) = 0;

		/**
		* @brief Set a vec2 uniform value
		*/
		virtual void set_uniform(const char* name, const glm::vec2& value) = 0;

		/**
		* @brief Set a vec3 uniform value
		*/
		virtual void set_uniform(const char* name, const glm::vec3& value) = 0;

		/**
		* @brief Set a vec4 uniform value
		*/
		virtual void set_uniform(const char* name, const glm::vec4& value) = 0;

		/**
		* @brief Set an int uniform value
		*/
		virtual void set_uniform(const char* name, int value) = 0;

		/**
		* @brief Set a int vec2 uniform value
		*/
		virtual void set_uniform(const char* name, const glm::ivec2& value) = 0;

		/**
		* @brief Set an int vec3 uniform value
		*/
		virtual void set_uniform(const char* name, const glm::ivec3& value) = 0;

		/**
		* @brief Set an int vec4 uniform value
		*/
		virtual void set_uniform(const char* name, const glm::ivec4& value) = 0;

		/**
		* @brief Set a 4x4 matrix uniform value
		*/
		virtual void set_uniform(const char* name, const glm::mat4& value) = 0;

	protected:

		/**
		* @brief Reads the content of a file and puts the result in a buffer
		*
		* @param path Constant reference to a the path of the file to read
		* @param buf Reference to a string buffer to write to
		*/
		void readFile(const std::string& path, std::string& buf);
	};
}
