//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <glm/glm.hpp>
#include "renderer.h"

namespace wrench {

	/**
	* @brief Camera that tells the renderer how to see the world
	*/
	class Camera
	{
	public:

		/**
		* @brief Main constructor. Binds to a renderer
		*/
		explicit Camera(const std::weak_ptr<Renderer>& renderer)
			: m_renderer(renderer) {}

		/**
		* @brief Set the camera to an orthographic projection setting. See glm::ortho() for arguments
		*/
		void generate_ortho(float left, float right, float bottom, float top, float zNear, float zFar);

		/**
		* @brief Set the camera to an perspective projection setting. See glm::perspective() for arguments
		*/
		void generate_perspective(float fov, float zNear, float zFar);

		/**
		* @brief Change the camera's position in the world
		*/
		void set_position(glm::vec3 position);

		/**
		* @brief Change the camera's rotation in the world
		*/
		void set_rotation(glm::vec3 rotation);

		/**
		* @brief Get the view projection matrix. Ready to be multiplied to the model matrix
		*/
		[[nodiscard]] glm::mat4 get_view_projection_matrix() const;

	private:
		glm::mat4	m_projectionMatrix	{glm::mat4(1.0f)};
		glm::mat4	m_viewMatrix		{glm::mat4(1.0f)};
		glm::mat4	m_cameraMatrix		{glm::mat4(1.0f)};
		glm::vec3	m_position			{glm::vec3(0, 0, 0)};
		glm::vec3	m_rotation			{glm::vec3(0, 0, 0)};
		glm::vec3	m_direction			{glm::vec3({0, 0, -1})};

		void calculateFullMatrix();
		const std::weak_ptr<Renderer>& m_renderer;
	};
}
