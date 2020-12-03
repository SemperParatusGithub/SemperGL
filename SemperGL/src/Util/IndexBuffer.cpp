#include "IndexBuffer.h"

#include <glad/glad.h>

namespace SemperGL
{
	IndexBuffer::IndexBuffer(unsigned int count, const void *data) : 
		m_Count(count)
	{
		glCreateBuffers(1, &m_IndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
	}
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferID);
	}
	unsigned int IndexBuffer::GetID()
	{
		return m_IndexBufferID;
	}
	unsigned int IndexBuffer::GetCount() const
	{
		return m_Count;
	}
	void IndexBuffer::Bind() const
	{
		glBindBuffer(1, m_IndexBufferID);
	}
	void IndexBuffer::UnBind() const
	{
		glBindBuffer(1, 0);
	}
}