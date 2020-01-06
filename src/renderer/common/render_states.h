//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "shader.h"
#include "camera.h"
#include "transform.h"

namespace wrench {

	struct RenderStates
	{
		Shader* 	shader 		{nullptr};
		Camera* 	camera		{nullptr};
		Transform*	transform	{nullptr};
	};
}
