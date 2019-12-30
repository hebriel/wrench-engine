//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

class SDL_Window;

namespace wrench {

	/**
	* @brief Context interface used internally by the Engine
	* @details You probably want to use implementations of this interface such as GLContext
	*/
	class Context
	{
	public:
		/**
		* @brief Main constructor
		*/
		explicit Context(SDL_Window* windowHandle);
		virtual ~Context() = default;

		/**
		* @brief Swap the rendering buffers
		*/
		virtual void swap_buffers() = 0;

	protected:
		virtual void init() = 0;

	protected:
		SDL_Window*	p_window	{nullptr};
	};
}
