//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

class SDL_Window;

namespace wrench {

	class Context
	{
	public:
		explicit Context(SDL_Window* windowHandle);
		virtual ~Context() = default;

		virtual void init() = 0;
		virtual void swap_buffers() = 0;

	protected:
		SDL_Window*	p_window	{nullptr};
	};
}
