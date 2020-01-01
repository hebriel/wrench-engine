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

	class GLContext final : public Context
	{
	public:
		explicit GLContext(SDL_Window* windowHandle, const GLSettings& settings);

		void init() override;
		void swap_buffers() override;

	private:
		GLSettings		m_settings	{};
		void*			m_context	{nullptr};
	};
}



