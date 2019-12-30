//
// @authors {underdisk}
// License : LGPLv3
//

#include <GL/glew.h>
#include <stdexcept>
#include "window.h"

namespace wrench {

	Window::Window(Size size, const std::string& title, GLSettings settings)
		: m_size(size), m_title(title), m_settings(settings)
	{
		m_window = SDL_CreateWindow(
				title.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				size.width,
				size.height,
				SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

		SDL_ShowWindow(m_window);
		m_isOpen = true;

		if (settings.useCore)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		}

		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.majorVersion) < 0)
			throw std::runtime_error(SDL_GetError());
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.minorVersion) < 0)
			throw std::runtime_error(SDL_GetError());
		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, settings.useDoubleBuffering) < 0)
			throw std::runtime_error(SDL_GetError());

		m_context = SDL_GL_CreateContext(m_window);
		if (m_context == nullptr)
			throw std::runtime_error(SDL_GetError());

		glewExperimental = GL_TRUE;
		int err = glewInit();
		if (err != GLEW_OK)
			throw std::runtime_error((char*)glewGetErrorString(err));
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_window);
	}

	const std::string& Window::getTitle() const
	{
		return m_title;
	}

	Size Window::getSize() const
	{
		return m_size;
	}

	void Window::setTitle(const std::string& title)
	{
		m_title = title;
	}

	void Window::setSize(const Size& size)
	{
		m_size = size;
	}

	void Window::display() const
	{
		SDL_GL_SwapWindow(m_window);
	}

	void Window::update()
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYUP:
					if(event.key.keysym.sym == SDLK_ESCAPE)
						m_isOpen = false;
					break;
				case SDL_QUIT:
					m_isOpen = false;
					break;
			}
		}
	}

	bool Window::isOpen() const
	{
		return m_isOpen;
	}

	const GLSettings& Window::getGLSettings() const
	{
		return m_settings;
	}

	const SDL_GLContext& Window::getGLContext() const
	{
		return m_context;
	}
}
