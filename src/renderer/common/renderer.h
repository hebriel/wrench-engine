//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <type_traits>
#include <memory>

namespace wrench {

	/**
	* @brief Object that dictates what and how to draw on the screen
	*/
	class Renderer
	{
	public:

		void draw_object

		/**
		* @brief Create a shared pointer to a Renderer implementation (RendererImpl)
		*
		* @return Shared pointer to a fresh implementation of a Renderer
		*/
		template <class RendererImpl>
		std::shared_ptr<Renderer> create()
		{
			static_assert(std::is_base_of_v<Renderer, RendererImpl>, "Template type parameter should inherit wrench::Renderer");
			return std::make_shared<RendererImpl>();
		}
	};
}


