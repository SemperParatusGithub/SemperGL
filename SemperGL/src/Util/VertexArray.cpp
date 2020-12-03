#include "VertexArray.h"


namespace SemperGL
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::AddVertexBuffer(const VertexBuffer &vb)
	{
		m_VertexBuffer = &vb;
	}

	void VertexArray::AddIndexBuffer(const IndexBuffer &ib)
	{
		m_IndexBuffer = &ib;
	}

	const VertexBuffer *VertexArray::GetVertexBuffer() const
	{
		return m_VertexBuffer;
	}

	const IndexBuffer *VertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	void VertexArray::AddAttribute(int index, unsigned int size, GLenum type, unsigned int stride, const void *offset)
	{
		glBindVertexArray(m_VertexArrayID);
		glEnableVertexArrayAttrib(m_VertexArrayID, index);
		glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
	}

	unsigned int VertexArray::GetID() const
	{
		return m_VertexArrayID;
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
}