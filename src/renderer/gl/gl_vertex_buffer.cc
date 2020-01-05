//
// @authors {underdisk}
// License : LGPLv3
//

#include "gl_vertex_buffer.h"
#include "gl.h"

namespace wrench::gl {

	GLVertexBuffer::GLVertexBuffer(const float* vertices, const uint32_t size)
	{
		glGenBuffers(1, &m_GLVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_GLVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //todo: being able to change GL_STATIC_DRAW
	}

	void GLVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_GLVertexBuffer);
	}

	void GLVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_GLVertexBuffer);
	}

	void GLVertexBuffer::setLayout(const Layout& layout)
	{
		m_layout = layout;
	}

	const Layout& GLVertexBuffer::getLayout() const
	{
		return m_layout;
	}
}