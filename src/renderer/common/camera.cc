//
// @authors {underdisk}
// License : LGPLv3
//

#include "camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

namespace wrench {

	void Camera::generate_perspective(float fov, float zNear, float zFar)
	{
		if(auto spt = m_renderer.lock())
		{
			Size viewportSize = spt->get_window().get_size();
			m_projectionMatrix = glm::perspective(fov, (float)viewportSize.width / (float)viewportSize.height, zNear, zFar);
			calculateFullMatrix();
		}
	}

	void Camera::generate_ortho(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		m_projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
		calculateFullMatrix();
	}

	void Camera::calculateFullMatrix()
	{

		m_direction = glm::rotateX(glm::vec3(0,0,-1), m_rotation.x);
		m_direction = glm::rotateY(m_direction, m_rotation.y);
		m_direction = glm::rotateZ(m_direction, m_rotation.z);

		m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, {0, 1, 0});

		m_cameraMatrix = m_projectionMatrix * m_viewMatrix;
	}

	glm::mat4 Camera::get_view_projection_matrix() const
	{
		return m_cameraMatrix;
	}

	void Camera::set_position(glm::vec3 position)
	{
		m_position = position;
		calculateFullMatrix();
	}

	void Camera::set_rotation(glm::vec3 rotation)
	{
		m_rotation = rotation;
		calculateFullMatrix();
	}

}
