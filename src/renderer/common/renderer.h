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

		/**
		* @brief Default constructor. Binds to a window with a context
		*/
		explicit Renderer(const Window& window)
			: p_window(window) {}

		/**
		* @brief Change the clear color using numbers from 0 to 1
		*/
		virtual void change_clear_color(const glm::vec4& color) = 0;

		/**
		* @brief Change the clear color using numbers from 0 to 255
		*/
		virtual void change_clear_color(const glm::ivec4& color) = 0;

		/**
		* @brief Clear the screen. See change_clear_color()
		*/
		virtual void clear() = 0;

		/**
		* @brief Draw a vertex array. A Shader needs to be bound
		*/
		virtual void draw_object(const std::weak_ptr<VertexArray>& vertexArray) const = 0;

		/**
		* @brief Draw a vertex array using the given render states
		*/
		virtual void draw_object(const std::weak_ptr<VertexArray>& vertexArray, const RenderStates& states) const = 0;

		/**
		* @brief Gets the window the renderer is bound to
		*
		* @return Constant reference to the window the renderer is bound to
		*/
		[[nodiscard]] const Window& get_window() const {return p_window;}

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

		/**
		* @brief Reference to the window the renderer is bound to
		*/
		const Window& p_window;
	};
}


