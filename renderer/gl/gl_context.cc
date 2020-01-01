//
// @authors {underdisk}
// License : LGPLv3
//

#include "gl_context.h"
#include "gl.h"
#include <stdexcept>
#include "../../core/SDL.h"

namespace wrench
{
	GLContext::GLContext(SDL_Window* windowHandle, const GLSettings& settings)
		: Context(windowHandle), m_settings(settings)
	{
		init();
	}

	void GLContext::init()
	{
		if (m_settings.useCore)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		}

		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_settings.majorVersion) < 0)
			throw std::runtime_error(SDL_GetError());
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_settings.minorVersion) < 0)
			throw std::runtime_error(SDL_GetError());
		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, m_settings.useDoubleBuffering) < 0)
			throw std::runtime_error(SDL_GetError());

		m_context = SDL_GL_CreateContext(p_window);
		if (m_context == nullptr)
			throw std::runtime_error(SDL_GetError());

		glewExperimental = GL_TRUE;
		int err = glewInit();
		if (err != GLEW_OK)
			throw std::runtime_error((char*)glewGetErrorString(err));
	}

	void GLContext::swap_buffers()
	{
		SDL_GL_SwapWindow(p_window);
	}
}