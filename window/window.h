//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "../core/core.h"
#include "../core/types.h"
#include "../gl/gl_settings.h"
#include "../gl/gl.h"
#include <string>
#include <SDL2/SDL.h>

namespace wrench {

	/**
 	* @brief Window used for drawing. Contains an OpenGL context
 	*/
	class Window
	{
	public:
		/**
		* @brief Default constructor
		*/
		Window() = default;

		/**
		* @brief Default destructor
		*/
		~Window();

		/**
		* @brief Creates the window from a size and a title
		*/
		Window(Size size, const std::string& title, GLSettings settings = GLSettings());

		/**
		* @brief Get the title of the window
		*/
		[[nodiscard]] const std::string& getTitle() const;

		/**
		* @brief Get the size of the window
		*/
		[[nodiscard]] Size getSize() const;

		/**
		* @brief Get the OpenGL context settings
		*/
		[[nodiscard]] const GLSettings& getGLSettings() const;

		/**
		* @brief Get the OpenGL context
		*/
		[[nodiscard]] const SDL_GLContext& getGLContext() const;

		/**
		* @brief Tell whether or not the window is open
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

	private:
		std::string		m_title		{"invalid window"};
		Size			m_size		{300, 200};
		SDL_Window*		m_window	{nullptr};
		SDL_GLContext	m_context	{nullptr};
		GLSettings		m_settings	{};
		bool			m_isOpen	{false};

	};
}
