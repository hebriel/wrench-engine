//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <glm/glm.hpp>

namespace wrench {

	struct Transform
	{
		glm::vec3 position	{0, 0, 0};
		glm::vec3 rotation 	{0, 0, 0};
		glm::vec3 scale		{1, 1, 1};
	};
}
