//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "../common/vertex_buffer.h"

namespace wrench::gl {

	/**
	* @brief OpenGL implementation of a VertexBuffer
	*/
	class GLVertexBuffer final : public VertexBuffer
	{
	public:

		/**
		* @brief Create an OpenGL VertexBuffer. Should be called by VertexBuffer::create()
		*/
		GLVertexBuffer(const float* vertices, uint32_t size);
		~GLVertexBuffer() override;

		void bind() const override;

		void unbind() const override;

		void setLayout(const Layout &layout) override;

		[[nodiscard]] const Layout& getLayout() const override;

	private:
		uint32_t	m_GLVertexBuffer	{};
		Layout		m_layout			{};
	};

}

