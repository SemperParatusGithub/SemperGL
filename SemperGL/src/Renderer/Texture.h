#pragma once

#include <string>

namespace SemperGL
{

	class Texture
	{
	public:
		Texture(std::string filepath);

		void Bind(std::size_t slot) const;
		void UnBind() const;

		inline unsigned int GetID() const { return m_TextureID; }

	private:
		unsigned int m_TextureID;
		unsigned char *m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	};
}