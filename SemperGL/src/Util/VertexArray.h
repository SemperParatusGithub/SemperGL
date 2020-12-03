#pragma once

#include <iostream>
#include <glad/glad.h>

#include "Util/VertexBuffer.h"
#include "Util/IndexBuffer.h"

namespace SemperGL
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void AddVertexBuffer(const VertexBuffer &vb);
		void AddIndexBuffer(const IndexBuffer &ib);

		const VertexBuffer *GetVertexBuffer() const;
		const IndexBuffer *GetIndexBuffer() const;

		void AddAttribute(int index, unsigned int size, GLenum type, unsigned int stride, const void *data);
		unsigned int GetID() const;

		void Bind() const;
		void UnBind() const;

	private:
		unsigned int m_VertexArrayID;
		const VertexBuffer *m_VertexBuffer;
		const IndexBuffer *m_IndexBuffer;
	};
}
