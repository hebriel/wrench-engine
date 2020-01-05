//
// @authors {underdisk}
// License : LGPLv3
//

#include "gl_index_buffer.h"
#include "gl.h"

namespace wrench::gl {

	GLIndexBuffer::GLIndexBuffer(const uint32_t* indices, const uint32_t size)
	{
		glGenBuffers(1, &m_GLElementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLElementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); //todo: being able to change GL_STATIC_DRAW
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_GLElementBuffer);
	}

	void GLIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void GLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLElementBuffer);
	}
}