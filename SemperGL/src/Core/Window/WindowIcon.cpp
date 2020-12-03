#include "WindowIcon.h"

#include <GLFW/glfw3.h>
#include <stb_image.h>

namespace SemperGL
{
	WindowIcon::WindowIcon(const std::string &filepath) : m_Filepath(filepath)
	{
		m_Image = new GLFWimage[1];
		stbi_set_flip_vertically_on_load(0);
		((GLFWimage*)m_Image)->pixels = stbi_load(filepath.c_str(), &((GLFWimage *) m_Image)->width, &((GLFWimage *) m_Image)->height, &m_BPP, 4);
	}

	WindowIcon::~WindowIcon()
	{
		if (((GLFWimage *) m_Image)->pixels)
			stbi_image_free(((GLFWimage *) m_Image)->pixels);
		else std::cout << "Failed to free Icon: " << m_Filepath << std::endl;
	}

	void *WindowIcon::GetIcon() const
	{
		return m_Image;
	}
}