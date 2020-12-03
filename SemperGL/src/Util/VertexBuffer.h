#pragma once

#include <iostream>

namespace SemperGL
{
	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size, const void *data);
		~VertexBuffer();

		unsigned int GetID() const;

		void Bind() const;
		void UnBind() const;

	private:
		unsigned int m_VertexBufferID;
	};
}
