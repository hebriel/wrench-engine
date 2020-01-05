//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <cstdint>
#include <type_traits>
#include <memory>

namespace wrench {

	/**
	* @brief Video Buffer used to limit the number of vertices stored in a VertexBuffer
	*/
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		/**
		* @brief Bind the buffer
		*/
		virtual void bind() const = 0;

		/**
		* @brief Unbind any IndexBuffer
		*/
		virtual void unbind() const = 0;

		/**
		* @brief Create a shared pointer to an IndexBuffer implementation (IndexBufferImpl)
		*
		* @return Shared pointer to a fresh implementation of an IndexBuffer
		*/
		template <class IndexBufferImpl>
		static std::shared_ptr<IndexBuffer> create(const uint32_t *indices, uint32_t size)
		{
			static_assert(std::is_base_of_v<IndexBuffer, IndexBufferImpl>, "Template type parameter should inherit wrench::IndexBuffer");
			return std::make_shared<IndexBufferImpl>(indices, size);
		}
	};
}
