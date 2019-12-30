//
// @authors {underdisk}
// License : LGPLv3
//

#include "context.h"
#include <SDL2/SDL.h>

namespace wrench {

	Context::Context(SDL_Window* windowHandle)
		: p_window(windowHandle)
	{	}
}
