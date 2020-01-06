//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <glm/glm.hpp>
#include "renderer.h"

namespace wrench {

	class Camera
	{
	public:
		explicit Camera(const std::weak_ptr<Renderer>& renderer)
			: m_renderer(renderer) {}

		void generate_ortho(float left, float right, float bottom, float top, float zNear, float zFar);

		void generate_perspective(float fov, float zNear, float zFar);

		void set_position(glm::vec3 position);

		void set_rotation(glm::vec3 rotation);

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
