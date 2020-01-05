//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <cstdint>
#include <type_traits>
#include <memory>
#include "layout.h"

namespace wrench {

	/**
	* @brief Video Buffer Data used for drawing objects
	*/
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		/**
		* @brief Bind the buffer
		*/
		virtual void bind() const = 0;

		/**
		* @brief Unbind any IndexBuffer
		*/
		virtual void unbind() const = 0;

		/**
		* @brief Set the layout of the buffer
		*/
		virtual void setLayout(const Layout& layout) = 0;

		/**
		* @brief Get the Layout of the buffer
		*
		* @return Constant reference to the Layout of the buffer
		*/
		[[nodiscard]] virtual const Layout& getLayout() const = 0;

		/**
		* @brief Create a shared pointer to an VertexBuffer implementation (VertexBufferImpl)
		*
		* @return Shared pointer to a fresh implementation of a VertexBuffer
		*/
		template <class VertexBufferImpl>
		static std::shared_ptr<VertexBuffer> create(const float *vertices, const uint32_t size)
		{
			static_assert(std::is_base_of_v<VertexBuffer, VertexBufferImpl>, "Template type parameter should inherit wrench::VertexBuffer");
			return std::make_shared<VertexBufferImpl>(vertices, size);
		}

	};
}
