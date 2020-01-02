//
// @authors {underdisk}
// License : LGPLv3
//

#include <SDL.h>
#include <stdexcept>

namespace wrench {

	void init()
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
			throw std::runtime_error(SDL_GetError());
	}

	void quit()
	{
		SDL_Quit();
	}
}
