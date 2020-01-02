//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "../common/context.h"
#include "gl_settings.h"
#include "gl.h"

class SDL_Window;

namespace wrench {

	struct GLSettings;

	/**
 	* @brief Context used for OpenGL rendering.
 	*/
	class GLContext final : public Context
	{
	public:
		/**
		* @brief Default constructor
		*
		* @details This constructor is meant to be called by the Window class. See Window::initContext
		*/
		explicit GLContext(SDL_Window* windowHandle, const GLSettings& settings);

		/**
		* @brief Swap the rendering buffers
		*/
		void swap_buffers() override;

	private:
		GLSettings		m_settings	{};
		void*			m_context	{nullptr};

		/**
		* @brief Initialization method separated from the constructor
		*/
		void init() override;
	};
}



