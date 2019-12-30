//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "../core/core.h"
#include "../core/types.h"
#include "../renderer/common/context.h"
#include <string>

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
		*/
		Window(Size size, const std::string& title);

		/**
		* @brief Get the title of the window
		*
		* @return Constant reference to the title displayed at the top of the window
		*/
		[[nodiscard]] const std::string& getTitle() const;

		/**
		* @brief Get the size of the window
		*
		* @return The size of the window on the screen
		*/
		[[nodiscard]] Size getSize() const;

		/**
		* @brief Get the OpenGL context
		*
		* @return Constant reference to the abstract Context class
		*/
		[[nodiscard]] const Context& getContext() const;

		/**
		* @brief Tell whether or not the window is open
		*
		* @return True if the window is open, false if it's not
		*/
		[[nodiscard]] bool isOpen() const;

		/**
		* @brief Set the title of the window
		*/
		void setTitle(const std::string& title);

		/**
		* @brief Set the size of the window
		*/
		void setSize(const Size& size);

		/**
		* @brief Needs to be called at every frame
		*/
		void update();

		/**
		* @brief Displays the window and swap the buffers
		*/
		void display() const;

		/**
		* @brief Creates a context. ContextType has to derive from wrench::Context
		*/
		template <class ContextType, class... Args>
		void initContext(Args... args)
		{
			m_context = new ContextType(m_window, args...);
		}

	private:
		std::string		m_title		{"invalid window"};
		Size			m_size		{300, 200};
		SDL_Window*		m_window	{nullptr};
		Context*		m_context	{nullptr};
		bool			m_isOpen	{false};

	};
}
