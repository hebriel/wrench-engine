//
// @authors {underdisk}
// License : LGPLv3
//

#include "gl_vertex_array.h"
#include "gl.h"

namespace wrench::gl {

	GLVertexArray::GLVertexArray()
	{
		glGenVertexArrays(1, &m_GLVertexArray);
	}

	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &m_GLVertexArray);
	}

	void GLVertexArray::bind() const
	{
		glBindVertexArray(m_GLVertexArray);
	}

	void GLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void GLVertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_GLVertexArray);
		vertexBuffer->bind();

		uint32_t index {0};
		const auto& layout = vertexBuffer->getLayout();
		for (auto& element : layout.getElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
								  element.getDimension(),
								  element.getGLType(),
								  GL_FALSE, //todo: make that an option
								  layout.getStride(),
								  element.offset);
			++index;
		}
		m_vertexBuffers.emplace_back(vertexBuffer);
	}

	void GLVertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_GLVertexArray);
		indexBuffer->bind();

		m_indexBuffer = indexBuffer;
	}
}