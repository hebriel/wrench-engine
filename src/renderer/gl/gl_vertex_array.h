//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "../common/vertex_array.h"
#include <vector>

namespace wrench::gl {

	/**
	* @brief OpenGL implementation of a VertexArray
	*/
	class GLVertexArray final : public VertexArray
	{
	public:
		GLVertexArray();
		~GLVertexArray() override;

		void bind() const override;

		void unbind() const override;

		void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

		void set_index_buffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

	private:
		uint32_t m_GLVertexArray {};
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	};
}
