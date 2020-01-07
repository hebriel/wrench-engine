//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "shader.h"
#include "camera.h"
#include "transform.h"

namespace wrench {

	/**
	* @brief Defines a shader, a transform and a camera for an object to be rendered with
	*/
	struct RenderStates
	{
		/**
		* @brief Shader for the object to be drawn with
		*/
		Shader* 	shader 		{nullptr};

		/**
		* @brief Camera to use for drawing
		*/
		Camera* 	camera		{nullptr};

		/**
		* @brief Transform of the object
		*/
		Transform*	transform	{nullptr};
	};
}
