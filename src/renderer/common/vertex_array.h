//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <type_traits>
#include <cstdint>
#include <memory>
#include "vertex_buffer.h"
#include "index_buffer.h"

namespace wrench {

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		/**
		* @brief Bind the VertexArray
		*/
		virtual void bind() const = 0;

		/**
		* @brief Unbind any VertexArray
		*/
		virtual void unbind() const = 0;

		/**
		* @brief Add a VertexBuffer
		*/
		virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

		/**
		* @brief Add an IndexBuffer
		*/
		virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		/**
		* @brief Add an IndexBuffer
		*/
		[[nodiscard]] virtual const std::shared_ptr<IndexBuffer>& get_index_buffer() const = 0;

		/**
		* @brief Create a shared pointer to a VertexArray implementation (VertexArrayImpl)
		*
		* @return Shared pointer to a fresh implementation of a VertexArray
		*/
		template <class VertexArrayImpl>
		static std::shared_ptr<VertexArray> create()
		{
			static_assert(std::is_base_of_v<VertexArray, VertexArrayImpl>, "Template type parameter should inherit wrench::VertexArray");
			return std::make_shared<VertexArrayImpl>();
		}
	};
}
