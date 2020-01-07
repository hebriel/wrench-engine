//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <glm/glm.hpp>

namespace wrench {

	/**
	* @brief Description of an object position, rotation and scale in a 3D environment
	*/
	struct Transform
	{
		/**
		* @brief Position of the object
		*/
		glm::vec3 position	{0, 0, 0};

		/**
		* @brief Rotation of the object
		*/
		glm::vec3 rotation 	{0, 0, 0};

		/**
		* @brief Scale of the object
		*/
		glm::vec3 scale		{1, 1, 1};
	};
}
