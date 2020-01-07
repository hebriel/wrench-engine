//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "../core/core.h"
#include "../core/types.h"
#include "../renderer/common/context.h"
#include "../core/time/clocktime.h"
#include <string>
#include <thread>

class SDL_Window;

namespace wrench {

	/**
 	* @brief Window used for drawing
 	*/
	class Window
	{
	public:

		/**
		* @brief Default destructor
		*/
		~Window();

		/**
		* @brief Creates the window from a size and a title
		*
		* @param size Size of the window
		* @param title Title of the window
		*/
		Window(Size size, const std::string& title);

		/**
		* @brief Get the title of the window
		*
		* @return Constant reference to the title displayed at the top of the window
		*/
		[[nodiscard]] const std::string& get_title() const;

		/**
		* @brief Set the maximum frames that can be rendered in one second
		*/
		void set_framerate_limit(unsigned limit);

		/**
		* @brief Get the size of the window
		*
		* @return The size of the window on the screen
		*/
		[[nodiscard]] Size get_size() const;

		/**
		* @brief Get the OpenGL context
		*
		* @return Constant reference to the abstract Context class
		*/
		[[nodiscard]] const Context& get_context() const;

		/**
		* @brief Tell whether or not the window is open
		*
		* @return True if the window is open, false if it's not
		*/
		[[nodiscard]] bool is_open() const;

		/**
		* @brief Tell the time between this frame and the frame before
		*
		* @return The time between this frame and the frame before
		*/
		[[nodiscard]] Time get_delta_time() const;

		/**
		* @brief Set the title of the window
		*
		* @param title New title of the window
		*/
		void set_title(const std::string& title);

		/**
		* @brief Set the size of the window
		*
		* @param size New size of the window
		*/
		void set_size(const Size& size);

		/**
		* @brief Needs to be called at every frame
		*
		* @return Whether or not the window updated its values (related to get_delta_time())
		*/
		bool update();

		/**
		* @brief Displays the window and swap the buffers
		*/
		void display();

		/**
		* @brief Creates a context. ContextType has to derive from wrench::Context
		*
		* @param args Put the elements used for the constructor of the context here
		*/
		template <class ContextImpl, class... Args>
		void initContext(Args... args)
		{
			static_assert(std::is_base_of_v<Context, ContextImpl>, "Template type parameter should inherit wrench::VertexBuffer");
			m_context = new ContextImpl(m_window, args...);
		}

	private:
		std::string		m_title		{"invalid window"};
		Size			m_size		{300, 200};
		SDL_Window*		m_window	{nullptr};
		Context*		m_context	{nullptr};
		bool			m_isOpen	{false};
		Time			m_dt		{};
		Clock			m_dc		{};
		Time			m_timeCap	{wrench::Time::microseconds(16667)};
	};
}
