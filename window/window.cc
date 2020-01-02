//
// @authors {underdisk}
// License : LGPLv3
//

#include "window.h"
#include <SDL.h>
#include <stdexcept>

namespace wrench {

	Window::Window(Size size, const std::string& title)
		: m_size(size), m_title(title)
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
	}

	Window::~Window()
	{
		delete m_context;
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
		m_context->swap_buffers();
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

	const Context& Window::getContext() const
	{
		return *m_context;
	}
}
