#pragma once

#include <iostream>

namespace SemperGL
{
	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int size, const void *data);
		~IndexBuffer();

		unsigned int GetID();

		unsigned int GetCount() const;

		void Bind() const;
		void UnBind() const;

	private:
		unsigned int m_IndexBufferID;
		unsigned int m_Count;
	};
}
