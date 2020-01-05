//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "../common/index_buffer.h"

namespace wrench::gl {

	/**
	* @brief OpenGL implementation of an IndexBuffer
	*/
	class GLIndexBuffer final : public IndexBuffer
	{
	public:

		/**
		* @brief Create an OpenGL IndexBuffer. Should be called by IndexBuffer::create()
		*/
		GLIndexBuffer(const uint32_t* indices, const uint32_t size);
		~GLIndexBuffer() override;

		void bind() const override;

		void unbind() const override;

	private:
		uint32_t m_GLElementBuffer {};
	};
}
