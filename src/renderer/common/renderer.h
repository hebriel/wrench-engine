//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <type_traits>
#include <memory>
#include "vertex_array.h"
#include "../../window/window.h"
#include <glm/glm.hpp>

namespace wrench {

	class RenderStates;

	/**
	* @brief Object that dictates what and how to draw on the screen
	*/
	class Renderer
	{
	public:

		explicit Renderer(const Window& window)
			: p_window(window) {}

		virtual void change_clear_color(const glm::vec4& color) = 0;
		virtual void change_clear_color(const glm::ivec4& color) = 0;
		virtual void clear() = 0;
		virtual void draw_object(const std::weak_ptr<VertexArray>& vertexArray) const = 0;
		virtual void draw_object(const std::weak_ptr<VertexArray>& vertexArray, const RenderStates& states) const = 0;

		const Window& get_window() const {return p_window;}

		/**
		* @brief Create a shared pointer to a Renderer implementation (RendererImpl)
		*
		* @return Shared pointer to a fresh implementation of a Renderer
		*/
		template <class RendererImpl>
		static std::shared_ptr<Renderer> create(const Window& window)
		{
			static_assert(std::is_base_of_v<Renderer, RendererImpl>, "Template type parameter should inherit wrench::Renderer");
			return std::make_shared<RendererImpl>(window);
		}

	protected:
		const Window& p_window;
	};
}


