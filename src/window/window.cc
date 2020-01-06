//
// @authors {underdisk}
// License : LGPLv3
//

#include "window.h"
#include <SDL.h>
#include <stdexcept>
#include <iostream>

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

	const std::string& Window::get_title() const
	{
		return m_title;
	}

	Size Window::get_size() const
	{
		return m_size;
	}

	void Window::set_title(const std::string& title)
	{
		m_title = title;
		SDL_SetWindowTitle(m_window, title.c_str());
	}

	void Window::set_size(const Size& size)
	{
		m_size = size;
	}

	void Window::display()
	{
		m_context->swap_buffers();
	}

	bool Window::update()
	{
		if (m_dc.get_elapsed_time().as_nanoseconds() >= m_timeCap.as_nanoseconds())
		{
			m_dt = m_dc.restart();
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
			return true;
		}
		return false;
	}

	bool Window::is_open() const
	{
		return m_isOpen;
	}

	const Context& Window::get_context() const
	{
		return *m_context;
	}

	Time Window::get_delta_time() const
	{
		return m_dt;
	}

	void Window::set_framerate_limit(unsigned limit)
	{
		m_timeCap = wrench::Time::seconds(1.0/(double)limit);
	}
}
